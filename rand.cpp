#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
using namespace std;
int main()
{
	freopen("test.in", "w", stdout);
	srand((unsigned)time(NULL));
	int i;
	for(int i=1; i<=1e7; i++)
		cout << rand()%100000000 << ' ';
	fclose(stdout);
	return 0;
}
