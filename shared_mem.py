__author__ = "Tony Do"
__copyright__ = "vanhuong.do@asicland.com"
__date__ = "2023.05.12"

import sysv_ipc, time
  
class CShmReader : 
    def __init__( self ) : 
        pass
 
    def doReadShm( self , key, size ) : 
        memory = sysv_ipc.SharedMemory( key=key)
        memory_value = memory.read()
        print ("I got:  ",memory_value.decode())

    def doWriteShm(self,key,size):
        shm = sysv_ipc.SharedMemory(key=key, flags=sysv_ipc.IPC_CREAT, mode=0o666, size=size)
        text = "Python reply " + str(i)
        shm.write(text.encode())
        shm.detach()
        print("I sent: ", text,"\n")

 
if __name__ == '__main__':
    i = 0
    print("\n")
    while True:
        i = i +1
        key_read = 777
        size_read = 1024
        s = CShmReader()
        s.doReadShm( key_read, size_read )
        time.sleep(1)
        key_write = 1234
        size_write = 1024
        w = CShmReader()
        w.doWriteShm(key_write, size_write)
        time.sleep(4)
