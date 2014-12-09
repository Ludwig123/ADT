//
//  tree.c 树类型的支持函数
//  ADT
//
//  Created by Ludwig on 12/6/14.
//  Copyright (c) 2014 Ludwig123. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//局部数据类型  --只在本文件内使用的
typedef struct pair
{
    struct node * parent;
    Node * child;
}Pair;

//局部函数原型
static Node * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Node * new_node, Node * root);
static void InOrder(const Node * root, void (*pfun)(Item item));//Traverse的内部函数
static Pair SeekItem(const Item * pi, const Tree * ptree);
static void DeleteNode(Node ** ptr);
static void DeleteAllNodes(Node * ptr);

//function define
void IntializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
}

bool TreeIsFull(const Tree * ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

bool AddItem(const Item * pi,Tree * ptree) //要排除的异常情况比正常情况还多
{
    Node * new_node;
    
    if(TreeIsFull(ptree)) //树是不是满的
    {
        fprintf(stderr, "there is full\n");
        return false;
    }
    if (SeekItem(pi, ptree).child != NULL)//树中有没有相同项目
    {
        fprintf(stderr, "attempted to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi); //是否可以成功制作为Node
    if (new_node == NULL)
    {
        fprintf(stderr, "couldn't creat node\n");
        return false;
    }
    
    //成功创造了一个节点
    (*ptree).size++;
    
    if(ptree->root == NULL)
        ptree->root = new_node;
    else
        AddNode(new_node, ptree->root);
    return true;
}

bool InTree(const Item * pi, const Tree * ptree)
{
    return (SeekItem(pi, ptree).child == NULL) ? false : true;
}

bool DeleteItem(const Item * pi, Tree * ptree)
{
    Pair look;
    look = SeekItem(pi, ptree);
    if (look.child == NULL)  //如果没有找到
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;
    
    return true;
    
}

void Traverse(const Tree * ptree, void (*pfun)(Item item))
{
    if(ptree != NULL)
        InOrder(ptree->root, pfun);
    else
        puts("ptree is empty,traverse false!");
    //我觉得找个地方失败后最好返回点东西
}

void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);//为什么这里还要单独写个函数出来
    ptree->root = NULL;
    ptree->size = 0;
}

//局部函数

static void InOrder(const Node * root, void (*pfun)(Item item))
{
    if(root != NULL)
    {
        InOrder(root->left,pfun);//向左散开，递归调用
        (*pfun)(root->item);    //pfun实际作用的步骤
        InOrder(root->right, pfun);//向右散开，递归调用
    }
}

static void DeleteAllNodes(Node * root)
{
    Node * pright;
    
    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);//递归调用
        free(root);                //释放内存
        DeleteAllNodes(pright);    //把右边的当root，递归调用下去
    }
}

static void AddNode(Node * new_node, Node * root)//toleft和toright分开，有利于程序的可读性！
{
    if (ToLeft(&new_node->item, &root->item)) //判断是不是该放在左边
    {
        if (root->left == NULL)
            root->left = new_node;
        else
            AddNode(new_node, root->left);//递归调用
    }
    else if(ToRight(&new_node->item, &root->item))
    {
        if(root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else
    {
        fprintf(stderr, "location error in AddNode()\n");
        exit(1);
    }
}


static bool ToLeft(const Item * i1, const Item * i2)
{
    int comp1;
    
    if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
        return true;
    else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
        return true;
    else
        return false;
}


static bool ToRight(const Item * i1, const Item * i2)
{
    int comp1;
    
    if ((comp1 = strcmp(i1->petname, i2->petname)) > 0)
        return true;
    else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
        return true;
    else
        return false;
}



static Node * MakeNode(const Item * pi)//把item生成一个Node
{
    Node * new_node;
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}


static Pair SeekItem(const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;
    
    if (look.child == NULL)  //树是空的
        return look;
    while (look.child != NULL)//一直要找到为空的位置为止
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if(ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else
            break;
    }
    return look;
}


static void DeleteNode(Node **ptr)
//ptr是指向目标节点的父节点指针成员的地址
{
    Node * temp;
    puts((*ptr)->item.petname);//输出要删除的宠物名字
    if((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;//如果右侧也为NULL的话
        free(temp);
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else //该节点左右都有子节点
    {
        for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}