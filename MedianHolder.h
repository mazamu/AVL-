#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
struct Node {
    Node() {
        val = 0;
        left = right = NULL;
        height = 1;
    }
    Node(int x) {
        val = x;
        left = right = NULL;
        height = 1;
    }

    int val;//值
    Node *left;
    Node *right;
    int height;//高度
};

class Vector {
public :
    Vector(){
        pos = 0;
        length = 1;
        Data = (int*)malloc(sizeof(int));
    }
    Vector(int num){
        pos = 0;
        length = num;
        Data = (int*)malloc(sizeof(int) * num);
    }
    ~Vector() {free(Data);}
    int judgeLimit();//当pos达到length的3/4时进行扩容
    int resize();//扩容
    int push_back(int val);
    void clear(){ pos = 1;}
    int operator[](int x) { return Data[x];}
private :
    int pos;//将要存数据的位置
    int *Data;
    int length;//总容量
};

class MedianHolder{
public :
    MedianHolder() {
        root = NULL;
        median = total_num = 0;
    }
    ~MedianHolder() { destroy(root);}
    Node* insert(Node* head,int& x);//插入
    Node* remove(Node* head,int& x);//删除
    void insert(int& val) { root = insert(root,val);total_num++;}
    void remove(int& val) { root = remove(root,val);total_num--;}

    Node* leftRotation(Node* head);//左旋 
    Node* rightRotation(Node* head);//右旋
    Node* balance(Node* head,int &x);//平衡调整

    Node* findMax(Node* root);//找到root最右边的节点
    Node* findMin(Node* root);//找到root最左边的节点

    
    void setMidnum();//找中位数
    void setDataVector(Node* root,Vector &data);//存数据
    double getMidnum(){return median;}

    //中序遍历
    void inOrderPrint(){ inOrderPrint(root); }
    void inOrderPrint(Node* root){
        if(!root) return;
        inOrderPrint(root->left);
        cout << root->val << " ";
        inOrderPrint(root->right);
    }
    void Print() {
        int level = 1;
        Print(root,level);
        cout<<"--------------------------------"<<endl;
    }
    void Print(Node* root,int level);

private :

    void destroy(Node*  node) {
        if(node != NULL) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    static int getheight(Node* node){
        if(node == NULL) return 0;
        return node->height;
    }

    Node *root;
    int total_num;//节点总数
    double median;//中位数
    Vector data;//空间足够的情况下，利用 总数/2得到中位数
};