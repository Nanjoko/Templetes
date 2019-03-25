#include <stdlib.h>
#include <stdio.h>

/*	�鲢���㷨����λ�����ڵ�������ֵ�������кϲ���һ����ֵ�������С�
				��������� X[s..u] = {3, 12, 23, 32}�� ���� X[u+1..v] = {2, 5, 8, 99} �ϲ� 
				�������X[s..u]��X[u+1..v]�鲢Ϊ�����Z[s..v].  */
void Merge(int X[], int Z[], int s, int u, int v)	
{
    int i, j, q;
    i = s;
    j = u + 1;
    q = s;
    while( i <= u && j<= v )
    {
        if( X[i] <= X[j] )
            Z[q++] = X[i++];
        else
            Z[q++] = X[j++];
    }

    while( i <= u )   	//��X��ʣ��Ԫ��X[i..u]���Ƶ�Z
        Z[q++] = X[i++];
    while( j <= v )   	//��X��ʣ��Ԫ��X[j..v]���Ƶ�Z
        Z[q++] = X[j++];
}

/*	һ�˹鲢ɨ�����㷨��
	���μ���������зֳ����ɸ�����Ϊt�ĸ��԰�ֵ����������У�
	Ȼ���ε��ù鲢���㷨merge�������������ڳɶԵ������кϲ������ɸ�����Ϊ2t�ĸ��԰�ֵ����������С�
	��ĳһ�˹鲢ɨ�赽���ʣ�µ�Ԫ�ظ����������������еĳ���ʱ��
		��ʣ�µ�Ԫ�ظ�������һ�������еĳ��� t ʱ��
			���ٵ���һ�ι鲢���㷨 merge ��ʣ�µ��������ȳ��������кϲ���һ������������;
		��ʣ�µ�Ԫ�ظ���С�ڻ��ߵ���һ�������еĳ��� t ʱ��ֻ�뽫ʣ�µ�Ԫ�����θ��Ƶ�ǰһ�������к��档*/
		
/*	 X[0..n-1]��ʾ�μ�����ĳ�ʼ����
 	tΪĳһ�˹鲢ʱ�����еĳ���
 	���ͱ���iָ����ǰ�鲢�������������е�1�������еĵ�1��Ԫ�ص�λ��
 	Y[0..n-1]��ʾ��һ�˹鲢��Ľ��	 */
void MergePass(int X[], int Y[], int n, int t)
{
    int i=0, j;
    while( n-i>=2*t )     //�����ڵ���������Ϊt�ĸ�������������кϲ���һ������Ϊ2t��������
    {
        Merge(X, Y, i, i+t-1, i+2*t-1);
        i = i + 2 * t;
    }
    if( n-i>t )       //�����ʣ�µ�Ԫ�ظ�������һ�������еĳ���tʱ
        Merge(X, Y, i, i+t-1, n-1);
    else             //n-i <= tʱ���൱��ֻ�ǰ�X[i..n-1]�����е����ݸ�ֵ��Y[i..n-1]
        for( j=i; j<n; ++j)
            Y[j] = X[j];
}

/*	��·�鲢�����㷨��
	���μ�����ĳ�ʼ���зֳɳ���Ϊ1��������ʹ��mergePass�������е�һ������
	�õ� n / 2 ������Ϊ 2 �ĸ�������������У���nΪ�������������һ�����Ԫ�ص������У���
	��һ�ε���mergePass�������еڶ������򣬵õ� n / 4 ������Ϊ 4 �ĸ�������������У� 
	�� i ��������������鲢����Ϊ 2^(i-1) �������еõ� n / (2^i) ����Ϊ 2^i �������У�
	ֱ�����ֻʣһ������Ϊn�������С��ɴ˿�����һ����Ҫ log2n ������ÿһ�������ʱ�临�Ӷ��� O(n), 
	�ɴ˿�֪���㷨���ܵ�ʱ�临�Ӷ����� O(n logn)��
	���Ǹ��㷨��Ҫ O(n) �ĸ����ռ䣬�ռ临�ӶȺܴ�.  */
void MergeSort(int X[], int n)		//�鲢���� 
{
    int t = 1;
    int *Y = (int *)malloc(sizeof(int)* n);
    while( t < n )
    {
        MergePass(X, Y, n, t);
        t *= 2;
        MergePass(Y, X, n, t);
        t *= 2;
    }
    free(Y);
}

void print_array(int array[], int n)	//������� 
{
    int i;
    for( i = 0 ; i < n ; ++i )
        printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    int array[] = {65, 2, 6, 1, 90, 78, 105, 67, 35, 23, 3, 88, -22};
    int size = sizeof(array) / sizeof(int);
    mergeSort(array, size);
    print_array(array, size);
    return 0;
}
