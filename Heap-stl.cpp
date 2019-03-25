#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

vector<int> a;
int num, n;
bool cmp(int x,int y)
{
	return x > y;	//��һ��С���ѣ��������Ǵ��ںš� > �� 
}

int main()
{
	cin >> n;
	for(int i=1; i<=n; ++i)
	{
		cin >> num;
		a.push_back(num);
	}
	make_heap(a.begin(), a.end(), cmp);		//������ 
	
	cin >> num;
	a.push_back(num);
	push_heap(a.begin(), a.end(), cmp);	//ÿ�ζ�����ά��  
	cout << a[0] << endl;		//�Ѷ� 
	pop_heap(a.begin(),a.end(),cmp);	//����һ��Ԫ�طŵ����Ȼ��������һ��Ԫ�ص��������ά��һ��� 
	a.pop_back();	//�Ƶ����һ��Ԫ�� 
	
	return 0;
}

/*
	Ҳ������priority_queue������
	����ѣ�priority_queue <int> heap�� 
	С���ѣ�priority_queue<int, vector<int>, greater<int> > heap�� 
	������heap.top();  ���ضѶ�ֵ�� 
		 heap.pop();  ɾ���Ѷ��� 
		heap.push(num);  �ӽ��ѣ� 
	����ѻ��Զ�ά����
*/


