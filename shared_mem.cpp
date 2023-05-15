/*
Creator: Tony Do
Copyright: vanhuong.do@asicland.com
Date: 2023.05.12
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string> 
#include <iostream>

using namespace std;

class CSharedMemroy
{ 
private :    
    int m_shmid;   
    key_t m_key;
    char *m_shared_memory;
    char *read_data;
 
public : 
    void read_data_in_mem();
    void setShmId( int key );
    int getShmId();
    void setKey( key_t key ); 
    void setupSharedMemory( int size );
    void attachSharedMemory();
    void copyToSharedMemroy( string str );
    void readDataSharedMemory(int m_shmid);
    void close();
};
  
void CSharedMemroy::setShmId( int id )
{
    m_shmid = id;
}
  
void CSharedMemroy::setKey( key_t key )
{
    m_key = key;
}
 
void CSharedMemroy::setupSharedMemory( int size )
{
    // Setup shared memory, 11 is the size 
   if ( ( m_shmid = shmget(m_key, size , IPC_CREAT | 0666)) < 0 )
   {
      printf("Error getting shared memory id");
      exit( 1 );
   }
}
  
void CSharedMemroy::attachSharedMemory()
{
   // Attached shared memory
   if ( ( m_shared_memory = (char*)(shmat( m_shmid , NULL , 0 ))) == (char *)-1)
   {
      printf("Error attaching shared memory id");
      exit(1);
   }
}
  
void CSharedMemroy::copyToSharedMemroy( string str )
{
   // copy string to shared memory
   memcpy( m_shared_memory, str.c_str() , str.size() );
   sleep(2);
}

void CSharedMemroy::readDataSharedMemory(int m_shmid)
{
    int shmid = shmget(m_shmid, sizeof(char), 0666);
    // attach to the shared memory segment
    char* data_ = (char*)shmat(shmid, NULL, 0);
    // read the data from the shared memory
    char data_got[1024];
    memcpy(data_got, data_, 1024);
    cout << "I got:  " << data_got << std::endl ;
    shmdt(data_);
    void* shmdt( void *shmid );
    shmctl( shmid , IPC_RMID, NULL );
    
}
 
void CSharedMemroy::close()
{
   sleep(3); 
   // Detach and remove shared memory
   void* shmdt( void *m_shmid );
   shmctl( m_shmid , IPC_RMID, NULL ); 
}

int main(int argc, const char **argv)
{
    int i = 0;
    while (true)
    {  
        i++; 
        string cpp_send = "Cpp sent " + std::to_string(i);
        cout << "\nI sent: " << cpp_send << endl;
        const char* cpp_ = cpp_send.c_str();
        CSharedMemroy m, n; 
        m.setKey(777);
        m.setupSharedMemory(12);
        m.attachSharedMemory(); 
        m.copyToSharedMemroy((char*)(cpp_));
        m.close();

        // get the shared memory ID
        int id_read = 1234;
        n.setKey(id_read);
        n.readDataSharedMemory(id_read);
    }
}