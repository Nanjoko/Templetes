
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

void lisan(int *x){		//����c++����һ������ֱ�Ӵ������������;ͺ��ˡ�
    arr data;	//typedef int arr[maxn];
    for(int i=1; i<=n; ++i)
		data[i] = x[i];
    sort(data+1,data+1+n);	//�����ǿ϶�Ҫ�ġ�
    int up=unique(data+1, data+1+n)-data-1;		//��data����[1..n]ȥ�أ��ڿƼ�
    for(int i=1; i<=n; ++i)
		x[i]=lower_bound(data+1, data+up+1, x[i]) - data;
			//�ҵ�x[i]��data�е�λ���ٸ�ֵΪ���λ�ã������-data���Ƿ������ֵ��
}
