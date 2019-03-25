#define miho register int
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int arrl = 4;
const int rado = 10000;
const int neko = 1e5 + 10;
char a1[neko], b1[neko];
int a[neko], c[neko], lena, lenb, x, p;

inline int read(char *s, int *n) {
	char tmp[10];
	int len = strlen(s), cur = 0;
	while( len/arrl ) {
		strncpy(tmp, s+len-arrl, arrl);		//搞arrl位进去 
		n[++cur] = atoi(tmp);
		len -= arrl;
	}
	if(len) {
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, s, len);		//全放进去 
		n[++cur] = atoi(tmp);
	}
	return cur;
}
inline void print(int *n) {
	while( !c[p] && p>1 ) --p;
	printf("%d", c[p]);
	for(miho i=p-1; i>=1; --i) {
		printf("%0*d", arrl, n[i]);
	}
}

inline void Add(int *a, int *b) {
	miho i = 1;
	while( i<=lena || i<=lenb ) {
		c[i] = a[i] + b[i] + x;
		x = c[i] / rado;
		c[i] %= rado;
		++i;
	}
	p = i + 1;
}

inline void Sub(int *a, int *b) {
	int k = 0;
	if( lena<lenb )  swap(a, b), k = 1;
	if( lena==lenb ) {
		for(miho i=lena; i>=1; --i)
			if( a[i]<b[i] ) {
				swap(a, b), k = 1;
				break;
			}
	}
	miho i = 1;
	while( i<=lena || i<=lenb ) {
		if( a[i]<b[i] ) {
			--a[i+1], a[i] += rado;
		}
		c[i] = a[i] - b[i];
		++i;
	}
	p = i + 1;
	if(k)  printf("-");
}

inline void Mul(int *a, int *b) {
	for(miho i=1; i<=lena; ++i) {
		x = 0;
		for(miho j=1; j<=lenb; ++j) {
			c[i+j-1] += a[i] * b[j] + x;
			x = c[i+j-1] / rado;
			c[i+j-1] %= rado;
		}
		c[i+lenb] += x;
	}
	p = lena + lenb + 1;
}

inline void Div(int *a, int b) {
	for(miho i=lena; i>=1; --i) {
		c[i] = ( rado*x + a[i] ) / b;
		x = ( rado*x + a[i] ) % b;
	}
	p = lena;
}

int main() {
	int a[neko]={0}, b[neko]={0};
	scanf("%s%s", a1, b1);
	read(a1, a), read(b1, b);
	Add(a, b);
	print(c);
	return 0;
}
