#include <cstdio> 
#include <cctype> 
#include <cstring> 
#include <algorithm> 
using namespace std; 

const int maxl = 1000000 + 10; 
char a[maxl], b[maxl]; 
int ans[maxl], nxt[maxl], lena, lenb; 

int main(int argc, char const *argv[]) 
{ 
  scanf("%s%s", a, b); 
  lena = strlen(a), lenb = strlen(b); 
  int t = 0;  nxt[0] = 0;
  for(int i = 1; i < lenb; ++i) {
    while( t && b[i] != b[t] ) t = nxt[t - 1];
    if( b[i] == b[t] ) ++t;  nxt[i] = t;
  }
  int k = 0;  t = 0;
  for(int i = 0; i < lena; ++i) {
    while( t && a[i] != b[t] )  t = nxt[t - 1];
    if( a[i] == b[t] )  ++t;
    if( t == lenb )  ans[++k] = i - lenb + 2;
  }
  for(int i = 1; i <= k; ++i) printf("%d\n", ans[i]);
  for(int i = 0; i < lenb; ++i) printf("%d ", nxt[i]);
  return 0;
}
