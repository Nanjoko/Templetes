#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 11000000 + 10;
char tmp[maxn], s[maxn << 1];
int l, p[maxn << 1];

inline int Manacher() {
  int ans = 0, pos = 0;
  for(int i = 0; i <= l; ++i) {
    if( pos + p[pos] > i ) p[i] = min(p[2 * pos - i], pos + p[pos] - i);
    while( i - p[i] >= 0 && i + p[i] <= l && s[i - p[i]] == s[i + p[i]] ) 
      ++p[i];
    if( pos + p[pos] < i + p[i] ) pos = i;
    ans = max(ans, p[i]);
  }
  return ans - 1;
}

int main(int argc, char const *argv[])
{
  scanf("%s", tmp);
  int len = strlen(tmp); l = -1;
  for(int i = 0; i < len; ++i)
    s[++l] = '#', s[++l] = tmp[i];
  s[++l] = '#';
  printf("%d\n", Manacher());

  printf("_______________________________________________\n");
  printf("Process Exited Correctly With A Return Value 0.\n");
  printf("All Rights Reserved By Kimitsu Nanjo In 2018.\n\n");
  return 0;
}