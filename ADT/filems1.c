//
//  main.c
//  ADT
//
//  Created by Ludwig on 11/11/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

/* filems1.c -- 使用结构数组*/
#include <stdio.h>
#define TSIZE 45 //存放片名的数组的大小
#define FMAX 5 //最多的影片数

struct film{
    char title[TSIZE];
    int rating;
};


int main_1(int argc, const char * argv[]) {
 
    struct film movies[FMAX];
    int i = 0;
    int j;
    
    puts ("enter first moive title");
    while (i < FMAX && gets (movies[i].title) != NULL && movies[i].title[0] != '\0')
    {
        puts("Enter your rating <0-10>: ");
        scanf("%d",&movies[i++].rating);
        while (getchar() != '\n')
            continue;
        puts("enter next movie title (empty line to stop): ");
    }
    if (i == 0)
        printf("no date entered. ");
        else printf("here is the the movie list: \n");
    
    for (j=0; j < i; j++) {
        printf("movie: %s rating:%d\n",movies[j].title,movies[j].rating);
    }
    printf("bye\n");
    return 0;
}
