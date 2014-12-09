//
//  tree.h
//  ADT
//
//  Created by Ludwig on 12/2/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#ifndef ADT_tree_h
#define ADT_tree_h

#include <stdbool.h>

typedef struct item
{
    char petname[20];
    char petkind[20];
}Item;

#define MAXITEMS 10

typedef struct node
{
    Item item;
    struct node * left;
    struct node * right;
}Node;


typedef struct tree
{
    Node * root;  //指向树根的指针
    int size;  //树中项目的个数
}Tree;

void InitializeTree(Tree * ptree);


bool TreeIsEmpty(const Tree * ptree);


bool TreeIsFull(const Tree * ptree);


int TreeItemCount(const Tree * ptree);


bool AddItem(const Item * pi, Tree * ptree);


bool InTree(const Item * pi, const Tree * ptree);

bool DeleteItem(const Item * pi, Tree * ptree);

void Traverse(const Tree * ptree, void (*pfun)(Item));

void DeleteAll(Tree * ptree);


#endif
