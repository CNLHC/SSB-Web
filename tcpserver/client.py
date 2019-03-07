import tornado
import functools
import argparse
from  tornado.tcpclient import TCPClient
from tornado.ioloop import IOLoop
from tornado.iostream import StreamClosedError
from tornado import gen
import binascii
import SSCEncoder
import random
import queue
import prettytable

Q=queue.Queue(maxsize=20)
parser = argparse.ArgumentParser()
parser.add_argument('host',type=str)
parser.add_argument('port',type=str)
parser.add_argument('file',type=argparse.FileType('r'))
args = parser.parse_args()
clientObj = TCPClient()

CartID= bytes([random.randint(0,255) for i in range(0,3) ])
op = bytes([0])
opData = bytes([0,0,0])

import csv
goodsList = list(csv.reader(args.file))
goodsTable = prettytable.PrettyTable()
goodsTable.field_names = ["商品编号","商品RFID", "商品名","价格"]
[goodsTable.add_row([v,]+i) for v,i in enumerate(goodsList)]

async def client(loop:IOLoop):
    try:
        print("try to connect {0:s}:{1:s}".format(args.host,args.port))
        stream = await clientObj.connect(args.host,args.port) #type:tornado.concurrent.futures.Future
        stream.set_nodelay(True)
        async def handle():
            while True:
                command=Q.get().split(' ')
                act=command[0]
                if act=='p':
                    print(goodsTable)
                elif act=='s':
                    good=goodsList[int(command[1])]
                    RFID = bytes.fromhex(good[0])
                    msg =SSCEncoder.SSCFrameEncoder(RFID,CartID,op,opData)
                    await  stream.write(msg)
                elif act=='d':
                    msg = command[1].encode()
                    await  stream.write(msg)

        def waitKey():
            while True:
                Q.put_nowait(input('>'))
                

        loop.add_callback(handle)
        loop.run_in_executor(None,waitKey)

    except StreamClosedError :
        print("error connecting, try in 5 sec")
        await gen.sleep(5)
        loop.add_callback(functools.partial(client,loop))

loop = IOLoop.current() #type:IOLoop
loop.set_default_executor(tornado.concurrent.futures.ThreadPoolExecutor(max_workers=10))
loop.add_callback(functools.partial(client,loop))
loop.start()
