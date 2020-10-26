/*------------------------------------------------------------------------
����ҵ��
emmӦ�ñȽϼ�
------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>   //��һ���string
#include <iomanip>  //�����ʽ����ͷ�ļ�
#include <conio.h>  //_getche
using namespace std;

/*------------------------------------------------------------------------
���е�ʵ��
------------------------------------------------------------------------*/
#if 1
//����������������洢�ռ�
const int MaxSize=50;
//���巵��ֵ
typedef int Status;
#define YES 1
#define NO 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1 
#define INFEASIBLE -2
#define TRUE 1
#define FALSE 0

//�ڵ�
template<class T>
struct Node{        
    T element;  //Ԫ�� ֻҪ�ض�����=�����;Ϳ���ʹ��
    Node<T>* Next;  //ָ�� ָ����һ��Node
    Node(Node<T>* ptr=NULL){this->Next=ptr;}    //�ճ�ʼ���ʹ�һ�γ�ʼ��
    Node(const T& item,Node<T>* ptr=NULL){this->element=item;this->Next=ptr;}   //һ�γ�ʼ�������γ�ʼ��
};

//����
template<class T>
class LinkedQueue{
protected:
    Node<T>* head;
    Node<T>* end;
public:
    LinkedQueue();
    ~LinkedQueue(){makeEmpty();}
    void makeEmpty();           //��ն���
    Status EnQueue(const T& x); //Ԫ��x�������
    Status DeQueue(T& x);     //��ͷԪ�س�����
    Status GetFront(T& x);    //��ȡ��ͷԪ�ص�ֵ
    Status IsEmpty()const;    //�ж϶����Ƿ�Ϊ��
    int GetSize()const;        //�����Ԫ�ظ���
};

//ʵ��
template<class T>
LinkedQueue<T>::LinkedQueue()
{
    Node<T> *s=new Node<T>;  //����ͷ��� nextΪnull
    if(s==NULL)exit(LOVERFLOW); //������벻�ɹ����˳�
    this->head=s;   //ͷָ��ָ��s
    this->end=s;    //βָ��ָ��s
}
template<class T>
void LinkedQueue<T>::makeEmpty()
{
    Node<T>* p=this->head,*q;
    while(p!=NULL)
    {
        q=p;
        p=p->Next;
        delete q;
    }
}
template<class T>
Status LinkedQueue<T>::EnQueue(const T& x)
{
    //���뵽β���֮��
    Node<T>* s=new Node<T>(x); //����һ���½ڵ�,ֵΪx��nextΪnull
    if(s==NULL)exit(LOVERFLOW); //������벻�ɹ����˳�
    this->end->Next=s;
    this->end=s;
    return OK;
}
template<class T>
Status LinkedQueue<T>::DeQueue(T& x)
{
    if(this->IsEmpty()==YES)return ERROR;
    //����ǿ� ɾ����һ���ڵ�
    Node<T> *p=this->head,*q=p->Next;
    x=q->element;
    p->Next=q->Next;
    delete q;
}
template<class T>
Status LinkedQueue<T>::GetFront(T& x)
{
    if(this->IsEmpty()==YES)return ERROR;
    //�ǿ� ���ص�һ���ڵ��ֵ
    x=this->head->Next->element;
    return OK;
}
template<class T>
Status LinkedQueue<T>::IsEmpty()const
{
    if(this->head->Next==NULL)return YES;
    else {return NO;}
}
template<class T>
int LinkedQueue<T>::GetSize()const
{
    Node<T> *p=this->head->Next;
    int cnt=0;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt;
}

#endif

/*------------------------------------------------------------------------
��������
------------------------------------------------------------------------*/
//��ȷ����һ���Ǹ�����
void safe_cin_positive_integer(int& x, const char* tips,int toplimit=0x7fffffff)    //Ĭ������Ϊint���ֵ
{
    cout << tips;
    while (1)    //����һ���������������
    {
        if (scanf("%d", &x) != 1)
        {
            cout << "�����������������" << endl;
            getchar();
            while (getchar() != '\n');
        }
        else if (x <= 0)
        {
            cout << "�����������������" << endl;
        }
        else if(x>toplimit)
        {
            cout<<"���볬������("<<toplimit<<")����������"<<endl;
        }
        else
        {
            break;
        }
        cout << tips;
    }
}

/*------------------------------------------------------------------------
����ҵ��ϵͳ��ʵ��
------------------------------------------------------------------------*/
//�����ջ����
const int output_A=2;
const int output_B=1;
const int priority_AB=1;   //1����A 2����B

//����������
const int input_length_max=1024;

//����
class BankService{
protected:
    LinkedQueue<int> A;
    LinkedQueue<int> B;
    int n;
    void solve();
public:
    BankService();
    ~BankService(){}
};

//ʵ��
BankService::BankService()
{
    safe_cin_positive_integer(this->n,"������˿�����(<=1000)",1000);
    for(int i=1;i<=n;i++)
    {
        char question[input_length_max];
        int no_clint;
        sprintf(question,"�������%d���˿͵ı��",i);
        safe_cin_positive_integer(no_clint,question,1000);
        if(no_clint%2==1)
        {
            //���Ϊ���� �����A
            A.EnQueue(no_clint);
        }
        else
        {
            //���Ϊż�� �����B
            B.EnQueue(no_clint);
        }
    }
    //������� ��ʼ����
    this->solve();
}
void BankService::solve()
{
    int top;
    cout<<"����Ĺ˿ͱ����:"<<endl;
    while(A.IsEmpty()==NO&&B.IsEmpty()==NO)
    {
        //�������ж���Ϊ�յ�ʱ��ʼִ�в���
        if(priority_AB==1)
        {
            //�����A
            for (int i = 0; A.IsEmpty()==NO&&i < output_A; i++)
            {
                A.DeQueue(top);
                cout<<top<<" ";
            }
            for (int i = 0; B.IsEmpty()==NO&&i < output_B; i++)
            {
                B.DeQueue(top);
                cout<<top<<" ";
            }
        }
        else
        {
            //�����B
            for (int i = 0; B.IsEmpty()==NO&&i < output_B; i++)
            {
                B.DeQueue(top);
                cout<<top<<" ";
            }
            for (int i = 0; A.IsEmpty()==NO&&i < output_A; i++)
            {
                A.DeQueue(top);
                cout<<top<<" ";
            }
        }
        
        
    }
    while(A.IsEmpty()==NO)
    {
        //A��Ϊ�� ������
        A.DeQueue(top);
        cout<<top<<" ";
    }
    while(B.IsEmpty()==NO)
    {
        //B��Ϊ�� ������
        B.DeQueue(top);
        cout<<top<<" ";
    }
    cout<<endl;
    return;
}


int main()
{
    BankService BS;
    return 0;
}

