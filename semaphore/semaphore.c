#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM 5
pthread_mutex_t m1, m2;
sem_t blank_num, product_num;
int goods,k;
void *producer(void *argv)
{
	while (1)
	{
		sem_wait(&blank_num);
		pthread_mutex_lock(&m1);
		goods++;
		printf("produce %d\n", goods);
		pthread_mutex_unlock(&m1);
		sem_post(&product_num);
		sleep(rand() % 2);
	}
}
void *comsumer(void *argv)
{
	while (1)
	{
		sem_wait(&product_num);
		pthread_mutex_lock(&m2);
		goods--;
		printf("comsume %d \n", goods);
		pthread_mutex_unlock(&m2);
		sem_post(&blank_num);
		sleep(rand() % 2);
	}
}
int main(void)
{
	goods = k = 0;
	//初始化信号量及互斥量
	sem_init(&blank_num, 0, NUM);
	sem_init(&product_num, 0, 0);
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_t pro[2], com[3];
	for (k = 0; k < 3; k++)
		pthread_create(&com[k], NULL, producer, NULL);
	for (k = 0; k < 2; k++)
		pthread_create(&pro[k], NULL, comsumer, NULL);
	for (k = 0; k < 3; k++)
		pthread_join(com[k], NULL);
	for (k = 0; k < 2; k++)
		pthread_join(pro[k], NULL);
	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	sem_destroy(&blank_num);
	sem_destroy(&product_num);
	return 0;
}
