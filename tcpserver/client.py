import tornado
import functools
import argparse
from  tornado.tcpclient import TCPClient
from tornado.ioloop import IOLoop
from tornado.iostream import StreamClosedError
from tornado import gen
import SSCEncoder
import random
from tornado.queues import Queue



Q=Queue(maxsize=20)
parser = argparse.ArgumentParser()
parser.add_argument('host',type=str)
parser.add_argument('port',type=str)
args = parser.parse_args()
clientObj = TCPClient()
RFID= bytes([random.randint(0,255) for i in range(0,4) ])
CartID= bytes([random.randint(0,255) for i in range(0,3) ])
op = bytes([0])
opData = bytes([0,0,0])


async def client(loop:IOLoop):
    try:
        print("try to connect {0:s}:{1:s}".format(args.host,args.port))
        stream = await clientObj.connect(args.host,args.port) #type:tornado.concurrent.futures.Future
        stream.set_nodelay(True)
        async def send():
            async for _ in Q:
                msg =SSCEncoder.SSCFrameEncoder(RFID,CartID,op,opData)
                await  stream.write(msg)

        def waitKey():
            while True:
                Q.put(input('>'))

        loop.run_in_executor(None,waitKey)
        loop.add_callback(send)

    except StreamClosedError :
        print("error connecting, try in 5 sec")
        await gen.sleep(5)
        loop.add_callback(functools.partial(client,loop))

loop = IOLoop.current() #type:IOLoop
loop.set_default_executor(tornado.concurrent.futures.ThreadPoolExecutor(max_workers=10))
loop.add_callback(functools.partial(client,loop))
loop.start()

