import crc8
import binascii


def SSCDecodeFrame(frame: bytes):
    hash = crc8.crc8()
    hash.update(frame[0:11])
    if(hash.digest() != frame[-1:]):
        print("CRC Check Error!", binascii.b2a_hex(
            hash.digest()), binascii.b2a_hex(frame[-1:]))

    payload = {
        'RFID': binascii.b2a_hex(frame[0:4]),
        'CartID':binascii.b2a_hex(frame[4:7]),
        'op':binascii.b2a_hex(frame[7:8]),
        'opData':binascii.b2a_hex(frame[8:11])
    }

    print(payload)
    print(frame)
