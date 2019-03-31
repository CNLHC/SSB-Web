import crc8
import binascii


class CRCError(Exception):
    pass

def SSCDecodeFrame(frame: bytes):
    hash = crc8.crc8()


    hash.update(frame[0:11])

    print("Check Frame",(frame))

    if(hash.digest() != frame[-1:]):
        print("CRC Check Error!",(hash.digest()),(frame[-1:]))
        raise CRCError

    payload = {
        'RFID':(frame[0:4]),
        'CartID':(frame[4:7]),
        'op':(frame[7:8]),
        'opData':(frame[8:11])
    }

    print(payload)
