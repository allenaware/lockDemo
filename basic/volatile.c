#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
bool stop = false;
void * thread_func_one(void *arg)
{
   while(!stop)
   {
       sleep(1);
       printf("thread one sleeping\n");
   }
   printf("thread one sleep end\n");
   return NULL;
}
void * thread_func_two(void *arg)
{
    stop =true;
   return NULL;
}
int main ( int argc, char **argv)
{
   pthread_t thread_one, thread_two;
   if( 0!=pthread_create( &thread_one, NULL, thread_func_one,NULL)){
      printf("pthread create failed!\n");
      return -1;
   }
   if( 0!=pthread_create( &thread_two, NULL, thread_func_two,NULL)){
      printf("pthread create failed!\n");
      return -1;
   }
   pthread_join(thread_one, NULL);
   pthread_join(thread_two,NULL);
   return 0;
}
