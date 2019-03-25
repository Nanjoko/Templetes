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
	/*	输入数组  */ 
	
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
	/*上浮：从当前结点开始，和它的父亲节点比较，若是比父亲节点来的小，就交换，
			然后将当前询问的节点下标更新为原父亲节点下标；否则（比父亲节点大）退出。 
			以用来维护小根堆。	*/
			
	void Shift_down(int node_num, int all)		//all表示当前有all个节点
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
	/*下沉：让当前结点的左右儿子(如果有的话)作比较，哪个比较小就和它交换，
			并更新询问节点的下标为被交换的儿子节点下标，否则（没有孩子）退出。 
			以用来进行堆顶大元素的下沉（维护小根堆）。  */
			
	void Push(int x)
    {
        ++n;
        h[n] = x;
        Shift_up(n);
    }
    /*每次插入的时候，都往最后一个插入，后使它上浮。 */
    
    void Pop(int x)
    {
        swap( h[1] , h[n]);
        --n;
        Shift_down(1);
    }
	/* 让根节点元素和尾节点进行交换，然后让现在的根元素下沉	 */
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
