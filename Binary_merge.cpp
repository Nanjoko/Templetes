#include <stdlib.h>
#include <stdio.h>

/*	归并子算法：把位置相邻的两个按值有序序列合并成一个按值有序序列。
				例如把序列 X[s..u] = {3, 12, 23, 32}和 序列 X[u+1..v] = {2, 5, 8, 99} 合并 
				将有序的X[s..u]和X[u+1..v]归并为有序的Z[s..v].  */
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

    while( i <= u )   	//将X中剩余元素X[i..u]复制到Z
        Z[q++] = X[i++];
    while( j <= v )   	//将X中剩余元素X[j..v]复制到Z
        Z[q++] = X[j++];
}

/*	一趟归并扫描子算法：
	将参加排序的序列分成若干个长度为t的各自按值有序的子序列，
	然后多次调用归并子算法merge将所有两两相邻成对的子序列合并成若干个长度为2t的各自按值有序的子序列。
	若某一趟归并扫描到最后，剩下的元素个数不足两个子序列的长度时：
		若剩下的元素个数大于一个子序列的长度 t 时，
			则再调用一次归并子算法 merge 将剩下的两个不等长的子序列合并成一个有序子序列;
		若剩下的元素个数小于或者等于一个子序列的长度 t 时，只须将剩下的元素依次复制到前一个子序列后面。*/
		
/*	 X[0..n-1]表示参加排序的初始序列
 	t为某一趟归并时子序列的长度
 	整型变量i指出当前归并的两个子序列中第1个子序列的第1个元素的位置
 	Y[0..n-1]表示这一趟归并后的结果	 */
void MergePass(int X[], int Y[], int n, int t)
{
    int i=0, j;
    while( n-i>=2*t )     //将相邻的两个长度为t的各自有序的子序列合并成一个长度为2t的子序列
    {
        Merge(X, Y, i, i+t-1, i+2*t-1);
        i = i + 2 * t;
    }
    if( n-i>t )       //若最后剩下的元素个数大于一个子序列的长度t时
        Merge(X, Y, i, i+t-1, n-1);
    else             //n-i <= t时，相当于只是把X[i..n-1]序列中的数据赋值给Y[i..n-1]
        for( j=i; j<n; ++j)
            Y[j] = X[j];
}

/*	二路归并排序算法：
	将参加排序的初始序列分成长度为1的子序列使用mergePass函数进行第一趟排序，
	得到 n / 2 个长度为 2 的各自有序的子序列（若n为奇数，还会存在一个最后元素的子序列），
	再一次调用mergePass函数进行第二趟排序，得到 n / 4 个长度为 4 的各自有序的子序列， 
	第 i 趟排序就是两两归并长度为 2^(i-1) 的子序列得到 n / (2^i) 长度为 2^i 的子序列，
	直到最后只剩一个长度为n的子序列。由此看出，一共需要 log2n 趟排序，每一趟排序的时间复杂度是 O(n), 
	由此可知该算法的总的时间复杂度是是 O(n logn)，
	但是该算法需要 O(n) 的辅助空间，空间复杂度很大.  */
void MergeSort(int X[], int n)		//归并排序 
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

void print_array(int array[], int n)	//输出序列 
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

