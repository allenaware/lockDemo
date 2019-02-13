#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void* another(void* arg){
    printf("in child thread, lock the mutex\n");
    pthread_mutex_lock(&mutex);
    sleep(5);
    pthread_mutex_unlock(&mutex);
}

int main ( int argc, char **argv)
{
   pthread_t id;

   pthread_mutex_init(&mutex, NULL);
   pthread_create( &id, NULL, another,NULL);
   /*父进程中的主线程暂停1s，以确保在执行fork操作之前，子线程已经开始运行并获得了互斥变量mutex*/
   sleep(1);
   int pid = fork();
   if( pid < 0 ){
       pthread_join( id, NULL );
       pthread_mutex_destroy( &mutex );
       return 1;
   }
   else if( pid == 0 ){
       printf("i am in the child,want to get the lock\n");
       /*子进程从父进程继承了互斥锁的状态，该互斥锁处于锁住的状态，这是由父进程中的子线程执行pthread_mutex_lock引起的，因此，下面这句加锁操作会一直阻塞，因为fork出来的子进程拷贝一份主进程的内存，但是主进程和子进程是两份不同的内存，即使主进程中的子线程释放了锁，也不会对子进程中的锁造成任何影响*/
       pthread_mutex_lock( &mutex );
       printf( "i can not run t here, opp..." );
       pthread_mutex_unlock( &mutex );
       exit(0);
   }
   else{
       sleep(10);
   }
   pthread_join( id, NULL );
   pthread_mutex_destroy( &mutex );
   return 0;
}
