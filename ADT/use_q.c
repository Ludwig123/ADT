//
//  use_q.c  测试Queue的接口驱动程序
//  compile with queue.c
//  ADT
//
//  Created by Ludwig on 11/28/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#include <stdio.h>
#include "queue.h"


int main(void)
{
    Queue line;
    Item temp;
    char ch;
    
    InitializeQueue(&line);
    puts("testing the queue interface. type a to  a value");
    puts("type d to delete a value, and type q tp quit.");
    while ((ch = getchar()) != 'q')
    {
        while (ch != 'a' && ch != 'd')
            continue;
        if (ch == 'a')
        {
            printf("integer to add: ");
            scanf("%d",&temp);
            if (!QueueIsFull(&line)) //添加前确认一下队列
            {
                printf("putting %d into queue\n", temp); //重复输入的内容，确认一遍
                EnQueue(temp, &line);
            }
        }
        else
        {
            if (QueueIsEmpty(&line))
                puts("nothing to delete!");
            else
            {
                DeQueue(&temp, &line);
                printf("removing %d from queue\n",temp);
            }
        }
        printf("%d item in queue\n",QueueItemCount(&line));
        puts("type a to add, d to delete, q to quit: ");
    }
    EmptyTheQueue(&line);
    puts("bye!");
    
    return 0;
}