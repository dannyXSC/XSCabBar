/*1951565 ��02 xsc*/
#include <iostream>
#include <string.h>
using namespace std;

const int width=3;
const int high=5;

//���
const int max_length=9;
//��ÿһλ���ݵ�����
int num_bit[max_length];

const char num[][high][width]={
	//���� �߶� ���
	{1,1,1,
	 1,0,1,
	 1,0,1,
	 1,0,1,
	 1,1,1
	},
	{0,0,1,
	 0,0,1,
	 0,0,1,
	 0,0,1,
	 0,0,1
	},
	{1,1,1,
	 0,0,1,
	 1,1,1,
	 1,0,0,
	 1,1,1
	},
	{1,1,1,
	 0,0,1,
	 1,1,1,
	 0,0,1,
	 1,1,1
	},
	{1,0,1,
	 1,0,1,
	 1,1,1,
	 0,0,1,
	 0,0,1
	},
	{1,1,1,
	 1,0,0,
	 1,1,1,
	 0,0,1,
	 1,1,1
	},
	{1,1,1,
	 1,0,0,
	 1,1,1,
	 1,0,1,
	 1,1,1
	},
	{1,1,1,
	 0,0,1,
	 0,0,1,
	 0,0,1,
	 0,0,1
	},
	{1,1,1,
	 1,0,1,
	 1,1,1,
	 1,0,1,
	 1,1,1
	},
	{1,1,1,
	 1,0,1,
	 1,1,1,
	 0,0,1,
	 1,1,1
	}
};

void _print(int x)
{
	int i,j;
	for(i=0;i<high;i++)
	{
		for(j=0;j<width;j++)
		{
			if(num[x][i][j])
			{
				cout<<"* ";
			}
			else
			{
				cout<<"  ";
			}
		}
		cout<<endl;
	}
	return;
}

int _print_nums(int x)
{
	//С��0�˳�
	if(x<0)return -1;
	int i,j,k;
	int length=1;
	int tempx=x;
	while(tempx/10)
	{
		length++;
		tempx=tempx/10;
	}
	if(length>max_length)
	{
		cout<<"ERROR:�������ݳ��ȹ���"<<endl;
		return -1;
	}
	for(i=0,tempx=x;i<length;i++)
	{
		num_bit[i]=tempx%10;
		tempx=tempx/10;
	}

	for(i=0;i<high;i++)
	{
		for(j=length-1;j>=0;j--)	//��ӡ��������
		{
			for(k=0;k<width;k++)	//��ӡ���������
			{
				if(num[num_bit[j]][i][k])
				{
					cout<<"* ";
				}
				else
				{
					cout<<"  ";
				}
			}
			cout<<"  ";
		}
		cout<<endl;
	}
	return 0;
}


//��װ����
//class PRINT_NUM{
///private:
//	int num_bit[max_length];	//��������ÿһλ���ݵ�����
//public:
//
//}


int main()
{
	int n;
	while(1)
	{
		memset(num_bit,0,sizeof(num_bit));
		cin>>n;
		_print_nums(n);
	}
}
