#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>   //��һ���string
#include <iomanip>  //�����ʽ����ͷ�ļ�
#include <conio.h>  //_getche
using namespace std;

//�ѵ�����ݻ�
const int maxn=10005;
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

/*С����*/
template<class T>
class MinHeap{
protected:
    T *heap;
    int volumn;
    int maxsize;
    void filterUp(int start);
    void siftDown(int start,int end);
public:
    MinHeap(int V=maxn);
    MinHeap(T arr[],int n);
    ~MinHeap();
    Status push(const T &x);    //����һ��
    Status pop(T &x);           //�Ѷ�����
    Status top(T &x);           //ȡ�Ѷ�
    Status is_empty();
};

/*ʵ��*/
template<class T>
MinHeap<T>::MinHeap(int V)
{
    heap=new T[V];
    if(heap==NULL)exit(-1);
    this->maxsize=V;
    this->volumn=0;
}
template<class T>
MinHeap<T>::MinHeap(T arr[],int n)
{
    this->maxsize=maxn<n?n:maxn;
    this->volumn=n;
    this->heap=new T[maxsize];
    if(this->heap==NULL)exit(-1);    //�˳�
    for(int i=0;i<n;i++)heap[i]=arr[i]; //��ֵ
    //��������
    int curpos=(n-2)/2; //�ҵ���һ��������ĸ��׽ڵ�
    while(curpos>=0)
    {
        siftDown(curpos,n-1);   //����
        curpos--;       //��ǰһ���ڵ�
    }
    
}
template<class T>
MinHeap<T>::~MinHeap()
{
    //����
    delete []this->heap;
}
template<class T>
void MinHeap<T>::siftDown(int start,int end)
{
    int i=start,j=2*i+1;
    T temp=heap[i];
    while(j<=end)
    {
        if(j<end&&heap[j]>heap[j+1])j++;
        if(temp<=heap[j])break; //����
        else
        {
            //����
            heap[i]=heap[j];
            i=j;
            j=i*2+1;
        }
    }
    heap[i]=temp;   //�Ż�
}
template<class T>
void MinHeap<T>::filterUp(int start)
{
    //��current��ʼ��0����
    //��ĩβ���룬ֱ�����׽ڵ�С�������ߵ����ڵ�
    int j=start,i=(j-1)/2;
    T temp=heap[j];
    while(j>0)
    {
        if(heap[i]<=temp)break;
        else
        {
            heap[j]=heap[i];
            j=i;
            i=(j-1)/2;
        }
    }
    heap[j]=temp;
}
template<class T>
Status MinHeap<T>::push(const T &x)
{
    if(this->volumn==maxsize)return LOVERFLOW;
    heap[volumn]=x;
    this->filterUp(volumn);
    volumn++;
    return OK;
}
template<class T>
Status MinHeap<T>::pop(T &x)
{
    if(volumn==0)return ERROR;
    x=heap[0];heap[0]=heap[volumn-1];
    volumn--;
    siftDown(0,volumn-1);
    return OK;
}
template<class T>
Status MinHeap<T>::top(T &x)
{
    if(volumn==0)return ERROR;
    x=heap[0];
    return OK;
}
template<class T>
Status MinHeap<T>::is_empty()
{
    if(this->volumn==0)return YES;
    else return NO;
}


/*------------------------------------------------------------------------
������  :safe_cin_positive_integer
����    :��ȫ����һ��������
����    :x ��Ҫ����ı���
        tips ������ʾ��
------------------------------------------------------------------------*/
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


int len[maxn];
//8 4 5 1 2 1 3 1 1 
int main()
{
    MinHeap<int> hp;
    int n;
    int sum=0;
    safe_cin_positive_integer(n,"����������N(<=10000)",10000);
    for(int i=0;i<n;i++)
    {
        cin>>len[i];
        hp.push(len[i]);
    }
    for(int i=0;i<n-1;i++)
    {
        int first,second;
        hp.pop(first);
        if(hp.is_empty()==YES)break;
        hp.pop(second);
        first=first+second;
        hp.push(first);
        sum+=first;
    }
    if(n==1)
    {
        cout<<len[0]<<endl;
    }
    else
    {
        cout<<sum<<endl;
    }
    
    return 0;
}












