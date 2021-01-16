#include"MedianHolder.h"

int Vector::judgeLimit() {
    if(pos >= length * 3 / 4) {
        return 1;
    }
    return 0;
}

int Vector::resize() {
    int *oldData = Data;
    length <<= 1;
    Data = (int*)malloc(length * sizeof(int));
    if(!Data) {
        cout<<"分配内存失败\n";
        return 0;
    }

    for(int i = 0; i < pos; i++) {
        Data[i] = oldData[i];
    }

    free(oldData);
    oldData = NULL;

}

int Vector::push_back(int val) {
    if(judgeLimit()) {
        if(!resize()) return 0;
    }
    Data[pos++] = val;
    return 1;
}

Node* MedianHolder::insert(Node* head,int& x) {
    if(head == NULL) {
        Node *temp = new Node(x);
        return temp;
    }

    //找到对应位置
    if(x <= head->val) head->left = insert(head->left,x);
    
    else if(x > head->val) head->right = insert(head->right,x);

    //更新数据
    head->height = 1 +max(getheight(head->right),getheight(head->left));

    //调整平衡
    head = balance(head,x);
    return head;
}

Node* MedianHolder::remove(Node* head,int& x) {
    if(!head) return NULL;
    if(x < head->val) {
        head->left = remove(head->left,x);
    }else if(x > head->val) {
        head->right = remove(head->right,x);
    }else {//找到此节点
        Node* right = head->right;

        if(head->right == NULL) {
            Node* left = head->left;
            delete (head);
            head = left;
        }else if(head->left == NULL) {
            delete (head);
            head = right;
        }else {
            right = findMin(right);
            head->val = right->val;
            head->right = remove(head->right,right->val);
        }
    }
    if(!head) {
        cout<<"final remove"<<endl;
        return head;
    }
    
    head->height = 1 +max(getheight(head->right),getheight(head->left));

    //调整平衡
    head = balance(head,x);
    return head;
}

Node* MedianHolder::balance(Node* head,int &x) {
    int bal = getheight(head->left) - getheight(head->right);
    if(bal > 1) {   //左子树高度大于右子树
        if(x <= head->left->val) {  //直左型
            return rightRotation(head);
        }else {  //左右型
            head->left = leftRotation(head->left);
            return rightRotation(head);
        }
    }else if(bal <  -1) {
        if(x > head->right->val) {  //右直型
            return leftRotation(head);
        }else {  //右左型
            head->right = rightRotation(head->right);
            return leftRotation(head);
        }
    }
    return head;    
}

Node* MedianHolder::leftRotation(Node* head) {//左旋
    Node *newhead = head->right;
    if(newhead == NULL) return head;
    head->right = newhead->left;
    newhead->left = head;

    //更新高度
    head->height = 1 + max(getheight(head->left),getheight(head->right));
    newhead->height = 1 +max(getheight(newhead->left),getheight(newhead->right));

    return newhead;
}

Node* MedianHolder::rightRotation(Node* head) {//右旋
    Node* newhead = head->left;
    if(newhead == NULL) return head;
    head->left = newhead->right;
    newhead->right = head;

    //更新高度
    head->height = 1 + max(getheight(head->left),getheight(head->right));
    newhead->height = 1 + max(getheight(newhead->left),getheight(newhead->right));

    return newhead;
}

Node* MedianHolder::findMax(Node* root) {
    Node* node = root;
    while(node && node->right) node = node->right;
    return node;
}

Node* MedianHolder::findMin(Node* root) {
    Node* node = root;
    while(node && node->left) node = node->left;
    return node;
}

void MedianHolder::Print(Node* root,int level) {
    if(!root) return;
    Print(root->right,level+1);
    if(level > 1) {
        for(int i = 0; i < 4*level-1; i++) cout<<'.';
        if(!root->left && !root->right) cout<<"|-"<<root->val<<endl;
        else cout<<"|-"<<root->val<<"-|"<<endl;
    }else {
        cout<<root->val<<"-|"<<endl;
    }
    Print(root->left,level+1);   

}

void MedianHolder::setDataVector(Node* root,Vector &data) {
    if(!root) return;
    setDataVector(root->left,data);
    data.push_back(root->val);
    setDataVector(root->right,data);
}

void MedianHolder::setMidnum() {

    setDataVector(root,data);
    int half = total_num / 2;
    if(total_num % 2 != 0) median = data[half];
    else median = 1.0*(data[half] + data[half-1]) / 2;
}

