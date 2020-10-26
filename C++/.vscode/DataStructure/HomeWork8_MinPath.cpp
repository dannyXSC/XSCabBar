/*------------------------------------------------------------------------
���·��
���ò��鼯
------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>   //��һ���string
#include <iomanip>  //�����ʽ����ͷ�ļ�
#include <conio.h>  //_getche
using namespace std;

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

struct Node{
    string name;    //�����Լ�������
    int root;       //���ڵ�
    int cost;       //�ܻ���(���ڵ����Ч)
    Node():name(""),root(-1),cost(0){}
    Node(string n,int r):name("n"),root(r),cost(0){}
};
struct Edge{
    string name1;
    string name2;
    int value;
    Edge():name1(""),name2{""},value(0){}
    Edge(const Edge& e){this->name1=e.name1;this->name2=e.name2;this->value=e.value;}
    void operator=(const Edge& e){this->name1=e.name1;this->name2=e.name2;this->value=e.value;}
};

class CostSystem{
protected:
    Node* sections; //�涥�������
    Edge* edges;
    int n;
    int n_edges;
    int find(string name);  //����name��Ӧ��λ��
    void Sort_Edges();
    int find_parent(int no);
public:
    CostSystem();
    
};

int CostSystem::find_parent(int no)
{
    return sections[no].root==no?no:(sections[no].root=find_parent(sections[no].root));
}

int CostSystem::find(string name)
{
    for(int i=0;i<this->n;i++)
    {
        if(this->sections[i].name==name)
            return i;
    }
    return -1;
}

void CostSystem::Sort_Edges()
{
    for(int i=0;i<n_edges-1;i++)
    {
        for(int j=n_edges-1;j>i;j--)
        {
            if(this->edges[j].value<this->edges[j-1].value)
            {
                //����
                Edge temp=edges[j];
                edges[j]=edges[j-1];
                edges[j-1]=temp;
            }
        }
    }
    return;
}

CostSystem::CostSystem()
{
    safe_cin_positive_integer(this->n,"�����붥�����:");
    cout<<"����������������"<<endl;
    this->sections=new Node[this->n];
    this->edges=new Edge[n*n];
    for(int i=0;i<this->n;i++)
    {
        cin>>this->sections[i].name;    //��������
        this->sections[i].root=i;       //��ʼ�����ڵ�
    }
    string e1,e2;
    int v;
    int i=0;
    while(1)
    {
        //����edges
        cin>>e1>>e2>>v;
        if(e1=="?"&&e2=="?"&&v==0)
        {
            //��������
            break;
        }
        edges[i].name1=e1;
        edges[i].name2=e2;    
        edges[i].value=v;
        i++;
    }
    this->n_edges=i;
    //edges��value����
    this->Sort_Edges();

    i=0;        //��¼��Ч������
    int cnt=0;  //ѭ������
    while(i<this->n-1)
    {
        int no1=find(edges[cnt].name1);
        int no2=find(edges[cnt].name2);
        int temp_root=find_parent(no1);
        int temp_children=find_parent(no2);
        if(temp_root==temp_children)
        {
            //�ɻ�
            cnt++;
            continue;
        }
        //������ɻ� ����
        sections[no2].root=temp_root;
        sections[temp_root].cost+=sections[temp_children].cost;
        //��ֵ����
        sections[temp_root].cost+=edges[cnt].value;
        cout<<sections[temp_root].cost<<"*"<<endl;
        cnt++;
        i++;
    }
    cout<<sections[find_parent(0)].cost<<endl;
}


/*
4
a b c d
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12
? ? 0

*/

int main()
{
    CostSystem cs;
    return 0;
}











