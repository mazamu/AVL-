#include"MedianHolder.cpp"
#include<time.h>
int main()
{
    srand((unsigned)time(NULL)); 
    MedianHolder *t = new MedianHolder;
    int a;
    for(int i = 0; i < 10; i++) {
        a = (rand()%100);
        t->insert(a);
    }
    int num;
    t->Print();
    while(1) {
        cout<<"insert : ";
        cin>>num;
        if(num == -1) break;

        t->insert(num);
        cout<<endl;
        t->Print();
    }
    // while(1) {
    //     cout<<"remove: "<<endl;
    //     cin>>num;
    //     if(num == -1) break;
    //     t->remove(num);
    //     cout<<endl;
    //     t->Print();
    // }
    t->setMidnum();
    t->inOrderPrint();
    cout<<endl<<"结果:"<<endl;;
    t->Print();
    double mid_num = t->getMidnum();
    cout<<"the midnum is : "<<mid_num<<endl;

    return 0;
}