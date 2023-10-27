#include<iostream>
#include<cstdlib>
using namespace std;

//đề bài: Nhập vào cây nhị phân các số nguyên. Xuất ra màng hình các phần tử cây nhị phân

//khai báo cấu trúc 1 cái node
struct node{
    int data;
    struct node *pLeft;
    struct node *pRight;
};
typedef struct node NODE;
typedef NODE* TREE;

// Khởi tạo cây
void KhoiTaoCay(TREE &t){
    t = NULL; //cây rỗng 
}

int main(){ 
    
}
