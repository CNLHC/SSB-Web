import crc8

def SSCFrameEncoder(RFID: bytes, CartID: bytes,op: bytes=bytes([0]), opData: bytes=bytes([0, 0, 0, 0])):
    hash = crc8.crc8()
    assert(len(RFID)==4)
    assert(len(CartID)==3)
    assert(len(op)==1)
    assert(len(opData)==3)
    base = RFID+CartID+op+opData
    hash.update(base)
    return base + hash.digest()




    


