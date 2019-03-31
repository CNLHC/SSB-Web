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
        raise CRCError

    payload = {
        'RFID':(frame[0:4]),
        'CartID':(frame[4:7]),
        'op':(frame[7:8]),
        'opData':(frame[8:11])
    }

    print(payload)
