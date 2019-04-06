import crc8
import crcmod
import binascii
import crccheck


class CRCError(Exception):
    pass

def SSCDecodeFrame(frame: bytes):
    Checksum=(crccheck.crc.Crc8Maxim.calc(frame[0:22]))
    print("Check Frame",(frame))

    if( Checksum != int(frame[-2:],16) ):
        print("CRC Check Error!",(Checksum),(frame[-2:]))
        return 

    payload = {
        'RFID':(frame[0:8]),
        'CartID':(frame[8:14]),
        'op':(frame[14:16]),
        'opData':(frame[16:22])
    }

    print(payload)
