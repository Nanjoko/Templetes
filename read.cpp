#include<cctype>
#include<cstdio> 
#include<ctime> 

inline int read()	//����ԭ��
{
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9')  {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
inline int Read()	//����ģ�� 
{
    int x=0, w=0; 
	char ch=0;
    while( !isdigit(ch) ) {	//isdigit(x)��ʾx�Ƿ���0~9�����������򷵻� true������false
		w |= ch=='-';
		ch = getchar();
	}
    while( isdigit(ch) ) { 
		x = (x<<3)+(x<<1)+(ch^48);
		ch = getchar();
	} 
    return w?-1*x:x;
}
inline double Dbread()	//ʵ��ģ�� 
{
    double x=0, y=1.0; 
	int w=0; 
	char ch=0;
    while( !isdigit(ch) ) {
		w |= ch=='-';
		ch = getchar();
	}
    while( isdigit(ch) ) {
		x = x*10+(ch^48);
		ch = getchar();
	}
    ch=getchar();	//����С����
    while( isdigit(ch) ) {
		x += (y/=10)*(ch^48);
		ch = getchar();
	}
    return w?-1*x:x;
}
inline void write(int x)	//�������ģ�� 
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}

int main()
{
	int a;
	double b;
	a = Read();
	b = Dbread();
	printf("%d ", a);
	printf("%f ", b);
	return 0;
}
