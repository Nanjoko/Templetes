#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

vector<int> a;
int num, n;
bool cmp(int x,int y)
{
	return x > y;	//建一个小根堆，则这里是大于号“ > ” 
}

int main()
{
	cin >> n;
	for(int i=1; i<=n; ++i)
	{
		cin >> num;
		a.push_back(num);
	}
	make_heap(a.begin(), a.end(), cmp);		//建立堆 
	
	cin >> num;
	a.push_back(num);
	push_heap(a.begin(), a.end(), cmp);	//每次都进行维护  
	cout << a[0] << endl;		//堆顶 
	pop_heap(a.begin(),a.end(),cmp);	//将第一个元素放到最后，然后忽略最后一个元素的情况下再维护一遍堆 
	a.pop_back();	//推掉最后一个元素 
	
	return 0;
}

/*
	也可以用priority_queue来建；
	大根堆：priority_queue <int> heap； 
	小根堆：priority_queue<int, vector<int>, greater<int> > heap； 
	操作：heap.top();  返回堆顶值； 
		 heap.pop();  删除堆顶； 
		heap.push(num);  扔进堆； 
	这个堆会自动维护。
*/


