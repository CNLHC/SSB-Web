from tornado.tcpserver import TCPServer
from tornado.iostream import StreamClosedError,IOStream
from tornado.concurrent import futures
from tornado.ioloop import IOLoop
import functools
import SSCDecoder
import signal

class SSCServer(TCPServer):
    async def handle_stream(self,stream:IOStream,address):
        print("connect from {0:s}:{1:d}".format(address[0],address[1]))
        loop = IOLoop.current() #type: IOLoop
        while True:
            try:
                data = await stream.read_bytes(12)
                loop.run_in_executor(None,functools.partial(SSCDecoder.SSCDecodeFrame,data))
                await stream.write(data)
                
            except StreamClosedError:
                print("connection closed from {0:s}:{1:d}".format(address[0],address[1]))
                break


loop = IOLoop.current()#type: IOLoop
loop.set_default_executor(futures.ThreadPoolExecutor(max_workers=10))
server=SSCServer()
server.listen('8888')
loop.start()

