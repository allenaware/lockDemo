#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_rwlock_t rwlock;
long int gval;
void *pth_wr(void *arg)
{
    int i = (int)arg;
    while (gval <= 100)
    {
        pthread_rwlock_wrlock(&rwlock);//请求写锁
        printf("write 全局变量gval = %ld, 我是%d号线程。\n", gval += 10, i + 1);
        pthread_rwlock_unlock(&rwlock);//解锁
        sleep(1);
    }
    return NULL;
}
void *pth_rd(void *arg)
{
    int i = (int)arg;
    while (gval <= 100)
    {
        pthread_rwlock_rdlock(&rwlock);//请求读锁
        printf("read 全局变量gval = %ld, 我是%d号线程。\n", gval, i + 1);
        pthread_rwlock_unlock(&rwlock);//解锁
        sleep(1);
    }
    return NULL;
}
int main(void)
{
    pthread_t pth[10];
    int i;
    pthread_rwlock_init(&rwlock, NULL);

    for (i = 0; i != 5; i++)//写
    {
        pthread_create(&pth[i], NULL, pth_wr, (void *)i);
    }
    for (i = 0; i != 5; i++)//读
    {
        pthread_create(&pth[5 + i], NULL, pth_rd, (void *)i);
    }
    while (1)
    {
        if (gval >= 100)
        {
            for (int j = 0; j != 10; j++)
            {
                pthread_cancel(pth[j]);//杀死线程
                pthread_join(pth[j], NULL);//回收线程
            }
            break;
        }
    }
    return 0;
}
