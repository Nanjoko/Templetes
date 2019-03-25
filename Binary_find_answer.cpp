#include<algorithm>
#include<iostream>
using namespace std;

const int maxn = 50000 + 500;
int d[maxn], n, m, l;
int lef, righ, mid;
int check(int x)
{
    int num=0, s=d[1];
    for(int i=2; i<=n+2; ++i)
    {
        if( d[i]-s<x )
            ++num;
        else s = d[i];
        if( num>m )	return 0;
    }
    return 1;
}

int main()
{
    cin >> l >> n >> m;
    d[n+2] = l;
    for(int i=2; i<=n+1; ++i)
        cin >> d[i];
    lef = d[1];
    righ = d[n+2] - d[1];
    while( lef+1<righ )
    {
        mid = (lef+righ)/2;
        if( check(mid) )
            lef = mid;
        else	righ = mid;
    }
    if( check(righ) )
        cout << righ;
    else	cout << lef;
    return 0;
}