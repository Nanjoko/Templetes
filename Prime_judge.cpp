
inline int prime(int x) {
	if( x==1 )	return 0;
	if( x==2 || x==3 )	return 1;
	if( x%6!=1 || x%6!=5 )	return 0;
	int tmp = sprt(x);
	for(int i=5; i<=tmp; i+=6)
		if( !(x%i)||!(x%(i+2)) )
			return 0;
	return 1;
}

void lisan(int *x){		//首先c++调用一个数组直接打这个数组的类型就好了。
    arr data;	//typedef int arr[maxn];
    for(int i=1; i<=n; ++i)
		data[i] = x[i];
    sort(data+1,data+1+n);	//排序是肯定要的。
    int up=unique(data+1, data+1+n)-data-1;		//给data数组[1..n]去重，黑科技
    for(int i=1; i<=n; ++i)
		x[i]=lower_bound(data+1, data+up+1, x[i]) - data;
			//找到x[i]在data中的位置再赋值为这个位置，如果不-data就是返回这个值。
}
