#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, l, top;

struct Node {
  double x, y;
  inline bool operator < (const Node &tmp) const {
    return this->x != tmp.x ? this->x < tmp.x : this->y < tmp.y;
  }
} node[maxn], sta[maxn];

inline double Distance(const Node &a, const Node &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double Check(const Node &o, const Node &a, const Node &b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int main(int argc, char const *argv[])
{
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%lf%lf", &node[i].x, &node[i].y);
  if( n < 3 ) printf("%lf\n", n == 1 ? 0.0 : Distance(node[1], node[2])), exit(0);
  sort(node + 1, node + n + 1);
  double ans = 0;
  top = 0, sta[++top] = node[1], sta[++top] = node[2];
  for(int i = 3; i <= n; ++i) {
    while( top > 1 && Check(sta[top - 1], sta[top], node[i]) <= 0 ) --top;
    sta[++top] = node[i];
  }
  for(int i = 2; i <= top; ++i) ans = ans + Distance(sta[i - 1], sta[i]);
  top = 0, sta[++top] = node[1], sta[++top] = node[2];
  for(int i = 3; i <= n; ++i) {
    while( top > 1 && Check(sta[top - 1], sta[top], node[i]) >=  0 ) --top;
    sta[++top] = node[i];
  }
  for(int i = 2; i <= top; ++i) ans = ans + Distance(sta[i - 1], sta[i]);
  printf("%lf\n", ans);

  return 0;
}