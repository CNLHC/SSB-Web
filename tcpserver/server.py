from tornado.iostream import StreamClosedError,IOStream
from tornado.util import TimeoutError
from tornado.tcpserver import TCPServer
from tornado.concurrent import futures
from tornado.ioloop import IOLoop
from tornado import gen
from queue import Queue
from datetime import timedelta
from functools import partial
import SSCDecoder

class SSCServer(TCPServer):
    DECODE_SUC = 1
    DECODE_CRC_ERROR =2

    def wrappedDecode(self,frame,queue:Queue):
        try:
            SSCDecoder.SSCDecodeFrame(frame)
            queue.put(self.DECODE_SUC)
        except SSCDecoder.CRCError:
            print("Frame CRC8 checksum error!")
            queue.put(self.DECODE_CRC_ERROR)

    async def handle_stream(self,stream:IOStream,address):
        print("connect from {0:s}:{1:d}".format(address[0],address[1]))
        loop = IOLoop.current() #type: IOLoop
        frameBuffer=b''
        Q=Queue(maxsize=10)
        while True:
            try:
                if not stream.reading():
                    dataFuture = stream.read_bytes(12,partial=True) #type:futures.Future
                frameBuffer=frameBuffer + await gen.with_timeout(timedelta(seconds=3),dataFuture) 
                if len(frameBuffer)<12:
                    continue
                loop.run_in_executor(None,partial(self.wrappedDecode,frameBuffer,Q))

                status = Q.get()
                frameBuffer=b''
                if status==self.DECODE_SUC:
                    await stream.write(bytes([0x3e]))
                else:
                    await stream.write(bytes([0x6c]))

            except StreamClosedError:
                print("connection closed from {0:s}:{1:d}".format(address[0],address[1]))
                break

            except gen.TimeoutError:
                frameBuffer=b''
                print("No response in 3 seconds {0:s}:{1:d}".format(address[0],address[1]))


loop = IOLoop.current()#type: IOLoop
loop.set_default_executor(futures.ThreadPoolExecutor(max_workers=10))
server=SSCServer()
server.listen('8888')
loop.start()

