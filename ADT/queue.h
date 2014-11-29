//
//  queue.h   队列接口
//  ADT
//
//  Created by Ludwig on 11/22/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#pragma c9x on
#ifndef _queue_h
#define _queue_h

#include <stdbool.h>

//在此处插入Item的定义

typedef struct item
{
    long arrive;
    int processtime;
}Item;

#define MAXQUEUE 10

typedef struct node
{
    Item item;
    struct node * next;
}Node;

typedef struct queue
{
    Node * front;
    Node *rear;
    int items;
}Queue;

//操作：初始化duilie
//操作前：pq指向一个队列
//操作后：该队列被初始化为空队列
void  InitializeQueue(Queue * pq);

bool QueueIsFull(const Queue * pq);

bool QueueIsEmpty(const Queue * pq);

int QueueItemCount(const Queue * pq);

//向队尾添加项目
bool EnQueue(Item item, Queue * pq);

//从队列首段删除项目
bool DeQueue(Item *pitem, Queue * pq);

//操作：清空队列
//操作前：pq指向一个先前已初始化过的队列
//操作后：队列被清空
void EmptyTheQueue(Queue * pq);

#endif













