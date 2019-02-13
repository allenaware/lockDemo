#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int a = 0;
int b = 0;
pthread_mutex_t mutexa;
pthread_mutex_t mutexb;

void* another(void* arg){
    pthread_mutex_lock(&mutexb);
    printf("in child thread, got mutex b, waitiing for mutex a\n");
    sleep(5);
    ++b;
    pthread_mutex_lock(&mutexa);
    b += a++;
    pthread_mutex_unlock(&mutexa);
    pthread_mutex_unlock(&mutexb);
    pthread_exit(NULL);
}

int main ( int argc, char **argv)
{
   pthread_t id;
   pthread_mutex_init(&mutexa, NULL);
   pthread_mutex_init(&mutexb, NULL);
   pthread_create( &id, NULL, another,NULL);
   pthread_mutex_lock(&mutexa);
   printf("in parent thread, got mutex a, waiting for b\n");
   sleep(5);
   ++a;
   pthread_mutex_lock(&mutexb);
   a += b++;
   pthread_mutex_unlock(&mutexb);
   pthread_mutex_unlock(&mutexa);
   pthread_join(id, NULL);
   pthread_mutex_destroy(&mutexa);
   pthread_mutex_destroy(&mutexb);
   return 0;
}
