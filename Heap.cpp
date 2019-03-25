#define /2 >>1
#define *2 <<1
#include<iostream>
#include<vector>
using namespace std;

const int maxn = 1000000 + 100;
int h[maxn], n;
struct Heap{
	void Init(int x)
	{
		for(int i=1; i<=x; ++i)
			cin >> h[i];
	}
	/*	��������  */ 
	
	void Shift_up(int node_num)
	{
		while( node_num/2>=1 )
    	{	
    	    if( h[node_num]<h[node_num/2] )
    	    {
    	        swap( h[node_num], h[node_num/2]);
    	        node_num = node_num/2;
    	    }
    	    else break;
		}
	} 
	/*�ϸ����ӵ�ǰ��㿪ʼ�������ĸ��׽ڵ�Ƚϣ����Ǳȸ��׽ڵ�����С���ͽ�����
			Ȼ�󽫵�ǰѯ�ʵĽڵ��±����Ϊԭ���׽ڵ��±ꣻ���򣨱ȸ��׽ڵ���˳��� 
			������ά��С���ѡ�	*/
			
	void Shift_down(int node_num, int all)		//all��ʾ��ǰ��all���ڵ�
	{
		int child;
		while( node_num*2<=n )
    	{
      		child = node_num*2;
      		if( child+1<=n && h[child+1]<h[child] )
            	child++;
       		if( h[node_num]>h[child] )
        	{
        	   swap( h[node_num], h[child] );
        	    node_num = child;
        	}
        	else break;
        }
	}
	/*�³����õ�ǰ�������Ҷ���(����еĻ�)���Ƚϣ��ĸ��Ƚ�С�ͺ���������
			������ѯ�ʽڵ���±�Ϊ�������Ķ��ӽڵ��±꣬����û�к��ӣ��˳��� 
			���������жѶ���Ԫ�ص��³���ά��С���ѣ���  */
			
	void Push(int x)
    {
        ++n;
        h[n] = x;
        Shift_up(n);
    }
    /*ÿ�β����ʱ�򣬶������һ�����룬��ʹ���ϸ��� */
    
    void Pop(int x)
    {
        swap( h[1] , h[n]);
        --n;
        Shift_down(1);
    }
	/* �ø��ڵ�Ԫ�غ�β�ڵ���н�����Ȼ�������ڵĸ�Ԫ���³�	 */
}heap;

int main()
{
	int a;
	cin >> n;
	for(int i=1; i<=n; ++i)
	{
		cin >> a;
		heap.Push(a);
	}
	for(i=1; i<=n; ++i)
	{
		cout << Q.top() << " ";
		Q.pop();
	}
	return 0; 
}
