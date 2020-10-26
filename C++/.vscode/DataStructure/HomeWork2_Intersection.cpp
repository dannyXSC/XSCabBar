#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>   //��һ���string
#include <iomanip>  //�����ʽ����ͷ�ļ�
#include <conio.h>  //_getche
using namespace std;

typedef struct Node{
    int ele;
    Node* next;
}*NodePointer;

class List{
private:
    NodePointer head;
    NodePointer end;
    int ele_num;
    void add_append(int x); //β�����
public:
    List();
    ~List();
    friend istream& operator>>(istream& in,List& l);        //��Ҫ���� ����ʱ��֤�������ظ�Ԫ�� ������������
    friend ostream& operator<<(ostream& out,const List& l);
    void intersection(const List& l);   //ʵ�ֽ��� �ѱ���
};

List::List()
{
    //ͷ
    this->head=new Node;
    if(this->head==NULL)
    {
        exit(-1);
    }
    this->head->next=NULL;
    //β
    this->end=this->head;
    this->ele_num=0;
}
List::~List()
{
    NodePointer p=this->head,q;
    while(p!=NULL)
    {
        q=p;
        p=p->next;
        delete q;
    }
}
void List::add_append(int x)
{
    NodePointer s=new Node;
    if(s==NULL)exit(-1);
    s->ele=x;
    s->next=NULL;
    this->end->next=s;
    this->end=s;
    this->ele_num++;
}
istream& operator>>(istream& in,List& l)
{
    int t,old_t=-1;
    while(scanf("%d",&t)==1&&t!=-1)
    {
        if(t!=old_t)
        {
            l.add_append(t);
            old_t=t;
        }
    }
    return in;
}
ostream& operator<<(ostream& out,const List& l)
{
    NodePointer p=l.head->next;
    if(p==NULL)
    {
        out<<"NULL"<<endl;
        return out;
    }
    while(p!=NULL)
    {
        out<<p->ele<<" ";
        p=p->next;
    }
    out<<endl;
    return out;
}
void List::intersection(const List& l)
{
    //��֪���������Ƿǵݼ������ظ�
    NodePointer p=this->head,q=l.head->next,t;    //pָ���������ϱȽϽڵ��ǰһ���ڵ� qָ��Ƚ������ϵı��ڵ�
    l.head->next=NULL;  //�ر��������
    while(!(p->next==NULL||q==NULL))
    {
        if(p->next->ele==q->ele)
        {
            //˵��p����һ���ڵ��ǽ���֮��Ľڵ�
            p=p->next;  //����������ڵ�
            //ɾ��q�ڵ�
            t=q;
            q=q->next;
            delete t;
        }
        else if(p->next->ele<q->ele)
        {
            //p->next�еĽڵ���Ч
            //ɾ��p->next
            t=p->next;
            p->next=t->next;
            delete t;
            //q�ڵ㲻�ö�
        }
        else
        {
            //q�нڵ���Ч
            t=q;
            q=q->next;
            delete t;
        }
    }
    if(p->next!=NULL)
    {
        t=p;
        p=p->next;
        t->next=NULL;
        while(p)
        {
            t=p;
            p=p->next;
            delete t;
        }
    }
    else
    {
        while(q)
        {
            t=q;
            q=q->next;
            delete t;
        }
    }
    
}


int main()
{
    List l1,l2;
    cout<<"�������һ������(�ǵݼ������ظ�):"<<endl;
    cin>>l1;
    cout<<"������ڶ�������(�ǵݼ������ظ�):"<<endl;
    cin>>l2;
    l1.intersection(l2);
    cout<<"ȡ�����ļ�����"<<endl;
    cout<<l1;
    return 0;
}