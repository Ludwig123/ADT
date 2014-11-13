//
//  filems2.c
//  ADT
//
//  Created by Ludwig on 11/13/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 45
struct film {
    char title[TSIZE];
    int rating;
    struct film *next;
};

int main(void)
{
    struct film * head = NULL;
    struct film * prev, * current;
    char input[TSIZE];
    
    //收集并存储信息
    puts("enter first movie title: ");
    while (gets(input) != NULL && input[0] != '\0')
    {
        current = (struct film *)malloc(sizeof(struct film));
        if (head == NULL)
            head = current;
        else
            prev -> next = current;
        current -> next = NULL;
        strcpy(current -> title, input);
        puts("enter you rating <0-10>");
        scanf("%d",&current->rating);
        while (getchar() != '\n')
            continue;
        puts("enter you movie title(empty line to stop)");
        prev = current;
    }
    
    //给出电影的列表
    if (head == NULL)
        printf("no data entered");
    else
        puts("here is the movie list :\n");
    current = head ;
    while (current != NULL)
    {
        printf("movie: %s rating: %d\n",current->title,current->rating);
        current = current -> next;
    }
    
    //任务已经完成，因此释放所有的内存
    current = head;
    while (current != NULL)
    {
        free(current);
        current = current->next;
    }
    printf("bye!\n");

    return 0;
}

int *p[TSIZE],a=10;
