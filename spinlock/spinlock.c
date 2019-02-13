#include <pthread.h>
#include <stdio.h>
pthread_spinlock_t lock;
int count = 0;
void * thread_func_one(void *arg)
{
   int i;
   for(i=0;i<10000;i++){
     pthread_spin_lock( &lock);
     count++;
     printf("thread one count value is %d\n",count);
     pthread_spin_unlock(&lock);
   }
   return NULL;
}
void * thread_func_two(void *arg)
{
   int i;
   for(i=0;i<10000;i++){
     pthread_spin_lock( &lock);
     count++;
     printf("thread two count value is %d\n",count);
     pthread_spin_unlock(&lock);
   }
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
