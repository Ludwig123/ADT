//
//  mall.c  使用Queue接口
//  ADT  与 queue.c一起编译
//
//  Created by Ludwig on 11/29/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#define MIN_PER_HR 60.0

bool newcustomer(double x);    //有新顾客到来吗？
Item customertime(long when);  //设置顾客参量

int main(void)
{
    Queue line;
    Item temp;   //关于顾客的数据
    int hours;   //模拟的小时数
    int perhours;  //每小时的平均顾客数
    long cycle, cyclelimit; //循环计数器，计数器的上界
    long turnaways = 0;  //因队列已满而被拒绝的顾客数量
    long customers = 0;  //被加入队列的顾客数
    long served = 0;
    long sum_line = 0;  //累计的队列长度
    long wait_time = 0;  //从当前到Sigmund空闲所需的时间
    double min_per_cust;
    long line_wait = 0;
    
    InitializeQueue(&line);
    srand(time(0));
    puts("case study: sigmund lander's advice booth");
    puts("enter the number of simulation hours: ");
    scanf("%d",&hours);
    cyclelimit = MIN_PER_HR * hours;
    puts("enter the average number of customers per hour: ");
    scanf("%d",&perhours);
    min_per_cust = MIN_PER_HR / perhours;
    
    for (cycle = 0; cycle < cyclelimit; cycle++)
    {
        if (newcustomer(min_per_cust))
        {
         if (QueueIsFull(&line))  //如果队列是满的
            turnaways++;
            else  //如果队列不是满的
            {
                customers++;
                temp = customertime(cycle);
                EnQueue(temp, &line);
            }
        }
        
        if (wait_time <= 0 && !QueueIsEmpty(&line)) //如果不需要等待，且队列不是空的；意味着只有一个人！
        {
            DeQueue(&temp, &line);
            wait_time = temp.processtime;
            line_wait += cycle - temp.arrive;
            served++;
        }
        if (wait_time > 0)
            wait_time--;
        sum_line += QueueItemCount(&line);
    }
    
    if (customers > 0)
    {
        printf("customer acccepted: %ld\n",customers);
        printf("customer served:%ld\n",served);
        printf(   "turnaways: %ld\n",turnaways);
        printf("average queue size: %.2f\n",(double)sum_line / cyclelimit);
        printf(" average wait time: %.2f minutes\n",(double)line_wait / served);
    }
    else
        puts("no customer!");
    EmptyTheQueue(&line);
    puts("BYE!");
    
    return 0;
}

//x是顾客到来的平均间隔时间（以秒计）
//如果这1分钟内有顾客到来，则返回true
bool newcustomer(double x)
{
    if (rand() * x / RAND_MAX < 1)
        return true;
    else
        return false;
}

//when是顾客到来的时间
//函数返回一个Item结构，该结构的顾客到来时间设置为when
//需要的咨询时间设置为一个范围在1到3之间的随机值
Item customertime(long when)
{
    Item cust;
    
    cust.processtime = rand() % 3 + 1;
    cust.arrive = when;
    
    return cust;
}

