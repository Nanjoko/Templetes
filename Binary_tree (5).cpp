#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = (1 << 12) + 10;
int n, m; long long s[maxn][maxn];

class Binary_tree {
public:
  inline void Update(int x, int y, int c) {
    for(int i = x; i <= n; i = i + (i & -i))
      for(int j = y; j <= m; j = j + (j & -j)) s[i][j] = s[i][j] + c;
  }

  inline long long Querry(int x, int y) {
    long long ans = 0ll;
    for(int i = x; i; i = i - (i & -i))
      for(int j = y; j; j = j - (j & -j)) ans = ans + s[i][j];  
    return ans;
  }
} bit;

inline int read() {
  register int ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline void Addnum(int sx, int sy, int c) {
  bit.Update(sx, sy, c), bit.Update(tx + 1, ty + 1, c);
  bit.Update(sx, ty + 1, -c), bit.Update(tx + 1, sy, -c);
}

inline void Getsum(int sx, int sy, int tx, int ty) {
  --sx, --sy;
  printf("%lld\n", bit.Querry(tx, ty) - bit.Querry(tx, sy) - bit.Querry(sx, ty) + bit.Querry(sx, sy));
}

int main(int argc, char const *argv[])
{
  scanf("%d%d", &n, &m);
  int ques = 0, sx = 0, sy = 0, tx = 0, ty = 0;
  while( ~scanf("%d", &ques) )
    if( ques == 1 ) sx = read(), sy = read(), tx = read(), ty = read(), Addnum(sx, sy, tx, ty, read());
    else sx = read(), sy = read(), Getsum(sx, sy);

  return 0;
}