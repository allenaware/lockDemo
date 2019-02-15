#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM 5 
#define PRODUCER_NUM 3 
#define CONSUMER_NUM 3 
pthread_mutex_t m1,m2;
sem_t sem_con, sem_pro;
int goods =0;
void *producer(void *argv)
{
	while (1)
	{
		sem_wait(&sem_pro);
		pthread_mutex_lock(&m1);
		goods++;
        int sem_number;
        sem_getvalue(&sem_pro,&sem_number);
		printf("producer thread id: %lu goods number: %d sem number: %d\n",pthread_self(),goods,sem_number);
		pthread_mutex_unlock(&m1);
		sem_post(&sem_con);
		sleep(rand()%5+1);
	}
}
void *consumer(void *argv)
{
	while (1)
	{
		sem_wait(&sem_con);
		pthread_mutex_lock(&m2);
		goods--;
        int sem_number;
        sem_getvalue(&sem_con,&sem_number);
		printf("consumer thread id: %lu goods number: %d sem number: %d\n",pthread_self(),goods,sem_number);
		pthread_mutex_unlock(&m2);
		sem_post(&sem_pro);
		sleep(rand()%5+1);
	}
}
int main(void)
{
	//初始化信号量及互斥量
	sem_init(&sem_pro, 0, NUM);
	sem_init(&sem_con, 0, 0);
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_t pro[PRODUCER_NUM];
	for (int k = 0; k < PRODUCER_NUM; k++)
		pthread_create(&pro[k], NULL, producer, NULL);
    pthread_t con[CONSUMER_NUM];
	for (int k = 0; k < CONSUMER_NUM; k++)
		pthread_create(&con[k], NULL, consumer, NULL);
	for (int k = 0; k < PRODUCER_NUM; k++)
		pthread_join(pro[k], NULL);
	for (int k = 0; k < CONSUMER_NUM; k++)
		pthread_join(con[k], NULL);
	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	sem_destroy(&sem_pro);
	sem_destroy(&sem_con);
	return 0;
}
