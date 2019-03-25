#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = (1 << 12) + 10;
int n, m; long long s[maxn][maxn], si[maxn][maxn], sj[maxn][maxn], sum[maxn][maxn];

class Binary_tree {
public:
  inline void Update(int x, int y, int c) {
    for(int i = x; i <= n; i = i + (i & -i))
      for(int j = y; j <= m; j = j + (j & -j)) {
        s[i][j] = s[i][j] + c;
        si[i][j] = si[i][j] + 1ll * x * c;
        sj[i][j] = sj[i][j] + 1ll * y * c;
        sum[i][j] = sum[i][j] + 1ll * x * y * c;;
      }
  }

  inline long long Querry(int x, int y) {
    long long ans = 0ll;
    for(int i = x; i; i = i - (i & -i))
      for(int j = y; j; j = j - (j & -j)) {
        ans = ans - (y + 1) * si[i][j] - (x + 1) * sj[i][j];
        ans = ans + 1ll * (x + 1) * (y + 1) * s[i][j] + sum[i][j];
      }
    return ans;
  }
} bit;

inline int read() {
  register int ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline void Addnum(int sx, int sy, int tx, int ty, int c) {
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
    sx = read(), sy = read(), tx = read(), ty = read(),
    ques == 1 ? Addnum(sx, sy, tx, ty, read()) : Getsum(sx, sy, tx, ty);

  return 0;
}