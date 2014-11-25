//
//  queue.c
//  ADT
//
//  Created by Ludwig on 11/22/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//局部函数
static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node *pn, Item * pi);

void InitializeQueue(Queue * pq)
{
    pq->front = NULL; //第一个置为空值
    pq->items = 0; //计数
}

bool QueueIsFull(const Queue * pq)
{
    return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
    return pq->items == 0;
}

int QueueItemCount(const Queue *pq)
{
    return pq->items;
}

bool EnQueue(Item item,Queue * pq)
{
    Node * pnew;
    
    if(QueueIsFull(pq))
        return false;
    pnew = (Node *)malloc(sizeof(Node));
    if (pnew == NULL)
    {
        fprintf(stderr, "unable to allocate memoru!\n");
        exit(1);
    }
    CopyToNode(item, pnew);
    pnew->next = NULL;
}