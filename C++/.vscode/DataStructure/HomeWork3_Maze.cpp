/*------------------------------------------------------------------------
��������Ⱥ͹���������ַ���
���ù������������·��
------------------------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>   //��һ���string
#include <iomanip>  //�����ʽ����ͷ�ļ�
#include <conio.h>  //_getche
using namespace std;

#if 1
/*------------------------------------------------------------------------
���еĳ����������͵�ʵ��
------------------------------------------------------------------------*/

//����������������洢�ռ�
const int MaxSize = 50;
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
�������͵�ͨ����ʽ����
------------------------------------------------------------------------*/

//�ڵ�
template<class T>
struct Node {
    T element;  //Ԫ�� ֻҪ�ض�����=�����;Ϳ���ʹ��
    Node<T>* Next;  //ָ�� ָ����һ��Node
    Node(Node<T>* ptr = NULL) { this->Next = ptr; }    //�ճ�ʼ���ʹ�һ�γ�ʼ��
    Node(const T& item, Node<T>* ptr = NULL) { this->element = item; this->Next = ptr; }   //һ�γ�ʼ�������γ�ʼ��
};

//����
template<class T>
class LinkedQueue {
protected:
    Node<T>* head;
    Node<T>* end;
public:
    LinkedQueue();
    ~LinkedQueue() { makeEmpty(); }
    void makeEmpty();           //��ն���
    Status EnQueue(const T& x); //Ԫ��x�������
    Status DeQueue(T& x);     //��ͷԪ�س�����
    Status GetFront(T& x);    //��ȡ��ͷԪ�ص�ֵ
    Status IsEmpty()const;    //�ж϶����Ƿ�Ϊ��
    int GetSize()const;        //�����Ԫ�ظ���
};
/*------------------------------------------------------------------------
�������͵�ͨ�������ʵ��
------------------------------------------------------------------------*/
template<class T>
LinkedQueue<T>::LinkedQueue()
{
    Node<T>* s = new Node<T>;  //����ͷ��� nextΪnull
    if (s == NULL)exit(LOVERFLOW); //������벻�ɹ����˳�
    this->head = s;   //ͷָ��ָ��s
    this->end = s;    //βָ��ָ��s
}
template<class T>
void LinkedQueue<T>::makeEmpty()
{
    Node<T>* p = this->head, *q;
    while (p != NULL)
    {
        q = p;
        p = p->Next;
        delete q;
    }
    return;
}
template<class T>
Status LinkedQueue<T>::EnQueue(const T& x)
{
    //���뵽β���֮��
    Node<T>* s = new Node<T>(x); //����һ���½ڵ�,ֵΪx��nextΪnull
    if (s == NULL)exit(LOVERFLOW); //������벻�ɹ����˳�
    this->end->Next = s;
    this->end = s;
    return OK;
}
template<class T>
Status LinkedQueue<T>::DeQueue(T& x)
{
    if (this->IsEmpty() == YES)return ERROR;
     //ά��β���
    if(this->end==this->head->Next)
    {
        this->end=this->head;
    }
    //����ǿ� ɾ����һ���ڵ�
    Node<T>* p = this->head, *q = p->Next;
    x = q->element;
    p->Next = q->Next;
    delete q;
    return OK;
}
template<class T>
Status LinkedQueue<T>::GetFront(T& x)
{
    if (this->IsEmpty() == YES)return ERROR;
    //�ǿ� ���ص�һ���ڵ��ֵ
    x = this->head->Next->element;
    return OK;
}
template<class T>
Status LinkedQueue<T>::IsEmpty()const
{
    if (this->head->Next == NULL)return YES;
    else { return NO; }
}
template<class T>
int LinkedQueue<T>::GetSize()const
{
    Node<T>* p = this->head->Next;
    int cnt = 0;
    while (p != NULL)
    {
        cnt++;
        p = p->Next;
    }
    return cnt;
}

#endif

/*------------------------------------------------------------------------
������  :wait_for_enter
����    :�ȴ�����س��Խ���
����    :
------------------------------------------------------------------------*/
void wait_for_enter()
{
    cout << "������س�����" << endl;
    if(getchar()=='\n')return;
    while (getchar() != '\n')
        ;
}

/*------------------------------------------------------------------------
ʵ���Թ�������㷨
------------------------------------------------------------------------*/
/*���崢���Թ�ǽ�ͷ�ǽ������*/
typedef int ELEMENT;
//������1,0��ʾ��ǽ����ǽ
#define map_have_barrier 1
#define map_no_barrier 0
#define map_path 2

/*�������*/
const char* Mark_Barrier = "#";
const char* Mark_NO_Barrier = "0";
const char* Mark_Path = "1";

/*������·��r��c��Ӱ��*/    //0-3�ֱ�Ϊ���ϡ����ҡ����¡�������
const int walk_r[] = { -1,0,1,0 };
const int walk_c[] = { 0,1,0,-1 };

/*����������*/
const int MAP_OUT_WIDTH = 5;

/*������ṹ��*/
struct point {
    int r;
    int c;
    point(int r = 0, int c = 0) :r(r), c(c) {}
    ~point() {}
    point& operator=(const point& p) { this->r = p.r; this->c = p.c; return *this; }
    bool operator==(const point& p) { if (this->r == p.r && this->c == p.c)return true; else return false; }
};

class Solve_Maze {
private:
    int row_total;
    int col_total;
    const point start;          //���Ǵ�1��ʼ��r��c
    const point destination;
    ELEMENT** map;  //�Թ���ͼ
    bool** is_visited;    //�ж�һ��ִ�������������û
    point** pre;    //�洢ͨ�����ڵ��ǰһ���ڵ�   ���õ��ı���θ�ֵ����Ϊvisit���˾Ͳ�����visit��
    LinkedQueue<point> queue;

    //�������
    const char* M_Barrier;
    const char* M_NoBarrier;
    const char* M_Path;
public:
    Solve_Maze(const int r, const int c, const int rs, const int cs, const int rd, const int cd, ELEMENT** map
        , const char* MB = Mark_Barrier, const char* MNB = Mark_NO_Barrier, const char* MP = Mark_Path);
    ~Solve_Maze();
    int solve();
    void show_map();
    void show_path(int r, int c);
};

//��Ա������ʵ��
Solve_Maze::Solve_Maze(const int r, const int c, const int rs, const int cs, const int rd, const int cd, ELEMENT** map_source,
    const char* MB, const char* MNB, const char* MP) :start(point(rs, cs)), destination(point(rd, cd))
{
    this->row_total = r;
    this->col_total = c;
    this->M_Barrier=MB;
    this->M_NoBarrier=MNB;
    this->M_Path=MP;
    //��map��is_visited���г�ʼ��
    //����r+2�к�c+2���Է������
    this->map = new ELEMENT * [r + 2];
    this->is_visited = new bool* [r + 2];
    this->pre = new point * [r + 2];
    for (int i = 0; i < r + 2; i++)
    {
        this->map[i] = new ELEMENT[c + 2];
        this->is_visited[i] = new bool[c + 2];
        this->pre[i] = new point[c + 2];
    }
    for (int i = 0; i < r + 2; i++)
    {
        for (int j = 0; j < c + 2; j++)
        {
            if (j == 0 || i == 0 || j == c + 1 || i == r + 1)
            {
                this->map[i][j] = map_have_barrier;
            }
            else
            {
                this->map[i][j] = map_source[i - 1][j - 1];
            }
            this->is_visited[i][j] = 0;   //��is_visited���г�ʼ��
        }
    }
}
Solve_Maze::~Solve_Maze()
{
    for (int i = 0; i < this->row_total + 2; i++)
    {
        delete[]this->map[i];
        delete[]this->is_visited[i];
        delete[]this->pre[i];
    }
    delete[]this->map;
    delete[]this->is_visited;
    delete[]this->pre;
}
void Solve_Maze::show_map()
{
    cout << setiosflags(ios::left);
    cout << "�Թ���ͼ:" << endl;
    cout << setw(MAP_OUT_WIDTH) << " ";
    //���ȴ�ӡ����
    for (int i = 1; i <= this->col_total; i++)
    {
        cout << i << setw(MAP_OUT_WIDTH - (i < 10 ? 1 : 2)) << "��"; //������԰�i��λ��Ҳ������ȥ
    }
    cout << endl;
    for (int i = 1; i <= this->row_total; i++)
    {
        //��ӡ����
        cout << i << setw(MAP_OUT_WIDTH) << "��";
        for (int j = 1; j <= this->col_total; j++)
        {
            if (map[i][j] == map_have_barrier)
            {
                cout << setw(MAP_OUT_WIDTH) << this->M_Barrier;
            }
            else if (map[i][j] == map_no_barrier)
            {
                cout << setw(MAP_OUT_WIDTH) << this->M_NoBarrier;
            }
            else if (map[i][j] == map_path)
            {
                cout << setw(MAP_OUT_WIDTH) << this->M_Path;
            }
        }
        cout << endl;
    }
    cout << endl;
}
void Solve_Maze::show_path(int r, int c)
{
    //�ݹ����
    //��������
    if (r == this->start.r && c == this->start.c)
    {
        printf("(%d,%d)", r, c);
        return;
    }
    //ִ�в���
    point u = pre[r][c];
    show_path(u.r, u.c);
    printf("--->(%d,%d)", r, c);
    return;
}
int Solve_Maze::solve()
{
    //��start�ڵ��Ƚ���
    pre[start.r][start.c] = point(-1, -1); //ά����ʼ�ڵ��ǰ�ڵ�
    is_visited[start.r][start.c]=true;
    queue.EnQueue(start);
    while (this->queue.IsEmpty() == NO)
    {
        point u;
        queue.DeQueue(u);   //�Ѷ��е�ͷ������u�в�ɾ��
        //��������
        if (u.r == destination.r && u.c == destination.c)
        {
            //�ҵ�����
            //��map���в��� ��path����map��path��
            //�����ȶ�map���и���
            point temp = u;
            while (1)
            {
                map[temp.r][temp.c] = map_path;
                temp = pre[temp.r][temp.c];
                if (pre[temp.r][temp.c] == point(-1, -1))
                {
                    //������������� �����һ�ξ�ֹͣ
                    map[temp.r][temp.c] = map_path;
                    break;
                }
            }
            //���map
            this->show_map();
            cout << "�Թ�·��" << endl;
            this->show_path(u.r, u.c);
            cout<<endl;
            //����
            wait_for_enter();
            return OK;
        }
        for (int i = 0; i < 4; i++)
        {
            point v = point(u.r + walk_r[i], u.c + walk_c[i]);
            if (is_visited[v.r][v.c] == 0 && map[v.r][v.c] != map_have_barrier)//�����ߵ�������û��ǽ������û���ʹ�����Ϊ�Ѿ����ʹ���������һ��������̣�
            {
                //������
                //ά��visit
                this->is_visited[v.r][v.c] = 1;
                //ά��pre
                this->pre[v.r][v.c] = u;
                //�����
                this->queue.EnQueue(v);
            }
        }
    }
    //������ж��ж�ȡ���� ˵���߲���
    //�����ʽ
    this->show_map();
    cout << "������·��" << endl;
    return 0;
}


/*��ʦҪ����Զ�������*/
const int r_given = 7, c_given = 7;
const int r_start = 2, c_start = 2;
const int r_des = 7, c_des = 5;
const ELEMENT map_given[r_given][c_given] = {
    1,1,1,1,1,1,1,
    0,0,0,1,1,1,1,
    0,1,0,1,1,1,1,
    0,1,0,1,0,0,0,
    0,0,0,1,0,1,1,
    1,1,0,0,0,1,1,
    0,0,0,1,0,1,1
};

int main()
{
    ELEMENT** map;
    map = new ELEMENT * [r_given];
    for (int i = 0; i < r_given; i++)
    {
        map[i] = new ELEMENT[c_given];
    }
    for (int i = 0; i < r_given; i++)
    {
        for (int j = 0; j < c_given; j++)
        {
            map[i][j] = map_given[i][j];
        }
    }
    Solve_Maze sm(r_given, c_given, r_start, c_start, r_des, c_des, map);
    //sm.show_map();
    sm.solve();
    return 0;
}
