import unittest
from tcpserver.SSCDecoder import SSCDecodeFrame

class testDecode(unittest.TestCase):
    def testHelloWorld(self):
        case1=b'E1D48E1E0000000000000188'
        print(SSCDecodeFrame(case1))

        

