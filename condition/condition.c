#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct node{
     struct node* next;
     int number;
}; 
 
pthread_cond_t hasNode = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
struct node* head = NULL;
void* get(void *arg)
{
 struct node *node;
 while(1) 
 {  	
   pthread_mutex_lock(&lock); 
   if(head == NULL)
  {        
    printf("has no data...\n");
     pthread_cond_wait(&hasNode,&lock);
   }
   node = head;
   head = node->next;
   printf("get the head node number:%d\n",node->number);
   pthread_mutex_unlock(&lock);
   free(node); //移除获取到的节点
   sleep(rand()%5);
   }
}
 
 
void* put(void *p) 
{
 struct node* node; 
  while(1)
 {     
  node = malloc(sizeof(struct node));
  node->number = rand()%1000 +1;
  printf("put the head node number:%d\n",node->number);    
  pthread_mutex_lock(&lock);
  node->next = head;
  head = node;
  pthread_mutex_unlock(&lock);
  pthread_cond_signal(&hasNode);
  sleep(rand()%5);   	
}
 
}
 
 
int main(){
pthread_t pid,cid;
srand(time(NULL));
pthread_create(&pid,NULL,get,NULL);
pthread_create(&cid,NULL,put,NULL);
pthread_join(pid,NULL);
pthread_join(cid,NULL);
return 0;
}
