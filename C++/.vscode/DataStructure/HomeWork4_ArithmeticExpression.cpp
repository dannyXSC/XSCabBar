/*------------------------------------------------------------------------
����ջ����������ʽ
1����ȫ��������
    ��֪����string������cin������
        string����ȫ���������ж�
        cin���Զ�������
2���ж��Ƿ��Ż�������
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
�������͵�ͨ����ʽջ
------------------------------------------------------------------------*/

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

//ջ
template<class T>
class LinkedStack{
protected:
    Node<T> *top;   //ջֻ��Ҫһ����ͷ����
public:
    LinkedStack();
    ~LinkedStack(){MakeEmpty();}
    void MakeEmpty();       //���ջ
    void Push(const T& x);  //��ջ
    Status Pop(T& x);       //��ջ
    Status GetTop(T& x)const;   //ȡջͷ 
    Status IsEmpty()const;      //�ж��Ƿ��ǿ�ջ
    int GetSize()const;         //ȡսԪ�ظ���
    void DisplayStack();
};

/*------------------------------------------------------------------------
�������͵�ͨ����ʽջ��ʵ��
------------------------------------------------------------------------*/
template<class T>
LinkedStack<T>::LinkedStack()
{
    //����ͷ���
    this->top=new Node<T>;
    if(this->top==NULL)exit(LOVERFLOW);
    //��ʼ����Node��д����
}
template<class T>
void LinkedStack<T>::MakeEmpty()
{
    Node<T> *p=this->top,*q;
    while(p)
    {
        q=p;
        p=p->Next;
        delete q;
    }
}
template<class T>
void LinkedStack<T>::Push(const T& x)
{
    Node<T> *s=new Node<T>(x);
    if(s==NULL)
    {
        exit(LOVERFLOW);
    }
    //����
    s->Next=this->top->Next;
    this->top->Next=s;
}
template<class T>
Status LinkedStack<T>::Pop(T& x)
{
    //����ǿձ� ���ش���
    if(this->top==NULL||this->top->Next==NULL)return ERROR;
    //��ֵ
    x=this->top->Next->element;
    //ɾ���ڵ�
    Node<T> *p=this->top->Next;
    this->top->Next=p->Next;
    delete p;
    return OK;
}
template<class T>
Status LinkedStack<T>::GetTop(T& x)const
{
    if(this->top==NULL||this->top->Next==NULL)return ERROR;
    //��ֵ
    x=this->top->Next->element;
    return OK;
}
template<class T>
Status LinkedStack<T>::IsEmpty()const
{
    if(this->top==NULL||this->top->Next==NULL)return YES;
    else return NO;
}
template<class T>
int LinkedStack<T>::GetSize()const
{
    Node<T> *p=this->top->Next;
    int cnt=0;
    while(p!=NULL)
    {
        cnt++;
        p=p->Next;
    }
    return cnt;
}
template<class T>
void LinkedStack<T>::DisplayStack()
{
    Node<T> *p=this->top->Next;
    while(p)
    {
        if(p->Next==NULL)
        {
            printf("<%d>\n",p->element);
        }
        else
        {
            printf("<%d>-->",p->element);
        }
        p=p->Next;
    }
}

#endif


/*------------------------------------------------------------------------
ʵ��
ֻ�������ܽ��в���  �պ����ά��һ��
��Ҫ���ǵ������� 1/-+-+2    +-+-2^4
�˷��ĸ�������
�涨���ȺŽ���
------------------------------------------------------------------------*/

const char Order_OutStack[]="=)+-*/%^(";    //ջ�����
const char Order_InStack[]="=(+-*/%^)";     //ջ�ڴ���

class CalculateInix{
protected:
    LinkedStack<int> num;    //��ջ
    LinkedStack<char> cha;      //����ջ
    string expression;          //������ʽ
    int cur_point;              //ָ��ǰ���㵽��λ��
    Status if_push(char coming);     //�жϷ���c�Ƿ���Ҫ��ջ
    Status calculate();         //��ջ������ʹ����
public:
    CalculateInix(string exp);
    Status solve();
};

//ʵ��
CalculateInix::CalculateInix(string exp)
{
    cur_point=0;
    //�����ǰ׺��������
    //����ͨ�������ŵķ�ʽʵ�ְ�ǰ׺���ʽ�����׺���ʽ
    int i;
    int len=exp.length();
    if(exp[exp.length()-1]!='=')
    {
        cout<<"������=��β"<<endl;
        exit(ERROR);
    }
    for(i=0;i<len;i++)
    {
        //�ȶ�����������ͬ�ķ��Ž��в���
        if(i>0&&!(exp[i]>='0'||exp[i]<='9')&&(exp[i]==exp[i-1]||exp[i]==exp[i-1]))    
        {
            cout<<"������������������"<<exp[i]<<endl;
            exit(ERROR);
        }
    }
    //����һ����֤�� �������ظ����ֵķ��ŵ�ʱ��һ����ǰһ����ͬ
    for(i=0;exp[i]!='=';i++) //���������len��ʵʱ�仯 ����ֻ����
    {
        if((!(exp[i]>='0'&&exp[i]<='9'))&&(i==0||(!(exp[i-1]>='0'&&exp[i-1]<='9')))&&(exp[i]=='-'||exp[i]=='+')&&exp[i-1]!=')')    
        {
            //�������ظ���+-
            //����ǰ׺+-
            //û���ظ���
            int cnt=0;          //�ж��ٸ�������+-+-
            int cnt_pas=0;      //�ж��ٸ�-
            int k=i;            //��һ����ֵ��λ��
            while(k<len&&!(exp[k]>='0'&&exp[k]<='9'))
            {
                if(exp[k]=='-')
                {
                    cnt++;
                    cnt_pas++;
                }
                else if(exp[k]=='+')
                {
                    cnt++;
                }
                else
                {
                    cout<<"������ʽ����(��+-��֮�������������)"<<endl;
                    exit(ERROR);
                }
                k++;
            }
            //�ں���Ѱ�Ҽ�')'��λ��
            for(k=k+1;k<len;k++)    //kΪ��ֵ֮���һ��
            {
                if(!(exp[k]>='0'&&exp[k]<='9')&&exp[k]!='^')
                {
                    //����Ƿ��Ų��Ҳ�Ϊ^
                    //�˳�
                    break;
                }
                //�������
            }
            if(k>=len)
            {
                exp.insert(len,")");    //��������')'
            }
            else
            {
                exp.insert(k,")");      //��kָ���λ��֮ǰ����')'
            }
            
            
            //��ʱ��Ҫ���ⲿ��ɾ������������
            //ǰ������string�ĺ�����벻��Ӱ��ǰ���λ�� ������֮ǰlen��ά��Ҳû��
            string temp="(0";
            temp+=(cnt_pas%2==1?'-':'+');
            exp.erase(i,cnt);   //��i(��һ���ҵ���λ��)ɾ��cnt��
            exp.insert(i,temp);

            //����len�仯�� ά��һ��
            len=exp.length();   
        }
    }
    this->expression=exp;
    cout<<exp<<endl;
}
Status CalculateInix::calculate()
{
    //���ڶ���˫Ŀ����� ���Գ������Ŷ�����Ҫ�������ֵ�
    //���Ų��ñ���������
    //ǰ׺+-Ҳ�����⴦��
    //����ֻ����+-*/%^������

    //�Ȱ���ջջ��������Ԫ��ȡ����
    int x1,x2;
    int ans;
    char instack_char;
    if(this->num.Pop(x1)==ERROR)
    {
        //˵����ջջ��û�� ����
        return ERROR;
    }
    if(this->num.Pop(x2)==ERROR)
    {
        //˵����ջջ��û�� ����
        return ERROR;
    }
    if(this->cha.Pop(instack_char)==ERROR)
    {
        //˵������ջջ��û�� ����
        return ERROR;
    }
    
    //�������Ŷ�ȡ������
    switch(instack_char)
    {
        case('+'):
        {
            ans=x1+x2;
            break;
        }
        case('-'):
        {
            //ע��˳��
            ans=x2-x1;  //����ջ���Ǽ���
            break;
        }
        case('%'):
        {
            ans=x2%x1;
            break;
        }
        case('*'):
        {
            ans=x2*x1;
            break;
        }
        case('/'):
        {
            ans=x2/x1;
            break;
        }
        case('^'):
        {
            ans=1;
            for(int i=0;x1>=0&&i<x1;i++)
            {
                ans*=x2;
            }
            if(x1<0)
            {
                cout<<"�����������Ȼ�����ܽ��д���"<<endl;
                return ERROR;
            }
            break;
        }
        case('('):
        case(')'):
        case('='):
        {
            cout<<"�������ʽ����(���Ż���=����������)"<<endl;
            return ERROR;
            //����Ҫbreak
        }
        default:
        {
            cout<<"ջ�з�������"<<endl;
            return ERROR;
        }
    }
    //��ջ
    this->num.Push(ans);
    return OK;
}
Status CalculateInix::if_push(char coming)
{
    //c��
    char instack;
    if(cha.GetTop(instack)==ERROR)
    {
        //�������ջ�ǿյ� ��ô��ջ
        return YES;
    }
    //��+-  */��������
    if((coming=='*'&&instack=='/')||(coming=='/'&&instack=='*')||
    (coming=='+'&&instack=='-')||(coming=='-'&&instack=='+'))
    {
        return NO;
    }
    if(coming==')'&&instack=='(')
    {
        //���������ƥ���� Ҳ�ý�ջ
        return YES;
    }
    int order_coming=strchr(Order_OutStack,coming)-Order_OutStack;
    int order_instack=strchr(Order_InStack,instack)-Order_InStack;
    if(order_coming>order_instack)
    {
        //���coming���ȼ�����ջ��Ԫ�� ��ô����ջ
        return YES;
    }
    else
    {
        //���comingС�ڵ���ջ��Ԫ�� ��ô����ջ�е�Ԫ��
        return NO;
    }
    
}
Status CalculateInix::solve()
{
    //�϶���һ������ȡ,�����ּ�����ֱ���������ŷ�����ջ���Ƿ����ж�1����ǰ׺������׺2����ջ��Ԫ�رȽ�
    int len=this->expression.length();  //���ܳ��ȼ�¼һ��
    while(this->cur_point<len)    //cur_point�ȱ��ʽ�ĳ���С����ѭ��
    {
        
        if(expression[cur_point]>='0'&&expression[cur_point]<='9')  //��������֣�������ȫ������
        {
            //��ʱ������ǰ׺���
            string temp_num;
            while(cur_point<len&&expression[cur_point]>='0'&&expression[cur_point]<='9')
            {
                temp_num+=expression[cur_point];
                cur_point++;
            }
            num.Push(atoi(temp_num.c_str()));   //��ֵ��ջ
        }
        else
        {
            //����Ƿ���   
            switch(expression[cur_point])
            {
                case('+'):
                {
                    //���flag=0���ոս������ջ ��ô�Ҿ���Ϊ���+��ǰ׺
                    //���ǻ���Ҫ�������ȼ���  ���� -+-+-2^2Ӧ�ò���4����-4
                    while(if_push('+')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����+"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('+');    //��+��ջ
                    break;
                }
                case('-'):
                {
                    while(if_push('-')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����-"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('-');    //��+��ջ
                    break;
                }
                case('%'):
                {
                    while(if_push('%')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����%"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('%');    //��+��ջ
                    break;
                }
                case('*'):
                {
                    while(if_push('*')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����*"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('*');    //��+��ջ
                    break;
                }
                case('/'):
                {
                    while(if_push('/')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����/"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('/');    //��+��ջ
                    break;
                }
                case('^'):
                {
                    while(if_push('^')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����^"<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('^');    //��+��ջ
                    break;
                }
                case('('):
                {
                    while(if_push('(')==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����("<<endl;
                            return ERROR;
                        }
                    }
                    //�����ﲻ���д��� ���ҿ��Լ���
                    this->cha.Push('(');    //��+��ջ
                    break;
                }
                case(')'):
                {
                    while(if_push(')')==NO)
                    {
                        
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����)"<<endl;
                            return ERROR;
                        }
                    }
                    //��ʱӦ������ջ������  ������ ��ջ  =
                    char temp;
                    this->cha.GetTop(temp);
                    if(this->cha.IsEmpty()==YES||temp=='=')
                    {
                        cout<<"������ʽ����(�������Ż��ߵȺŲ����Ϲ淶)"<<endl;
                        return ERROR;
                    }
                    //��������ͷ
                    if(temp=='(')
                    {
                        this->cha.Pop(temp);    //�����ų�ջ ����
                    }
                    else
                    {
                        cout<<"������ʽ����ֵĴ���1"<<endl;
                        return ERROR;
                    }
                    
                    break;
                }
                case('='):
                {
                    //��������
                    while(this->cha.IsEmpty()==NO)
                    {
                        if(this->calculate()==ERROR)
                        {
                            cout<<"�������ʽ����="<<endl;
                            return ERROR;
                        }
                    }
                    //�����������
                    if(this->num.GetSize()!=1)
                    {
                        //���ջ�е�������1�� �д���
                        cout<<"�������ʽ����num"<<endl;
                        return ERROR;
                    }
                    //����ɹ�
                    int temp_num;
                    this->num.GetTop(temp_num);
                    cout<<temp_num<<endl;
                    return OK;
                }
                default:
                {
                    cout<<"�����������"<<endl;
                    return ERROR;
                }
            }
            cur_point++;
        }
    }
}

//����
int main()
{
    string exp;
    cout<<"��������ʽ"<<endl;
    cin>>exp;
    CalculateInix ci(exp);
    ci.solve();
    return 0;
}






