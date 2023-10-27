#include<stdio.h>
//setting queue
struct Node{
    int data;
    struct node *pLink;
};
typedef struct Node NODE;
struct{
    NODE *pHead;
    NODE *pTail;
};



