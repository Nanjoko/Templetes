#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, t, top;

struct Node {
  long long x, y;
  inline bool operator < (const Node &tmp) const {
    return this->x != tmp.x ? this->x < tmp.x : this->y < tmp.y;
  }
} node[maxn], sta[maxn];

inline long long Distance(const Node &a, const Node &b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline long long Check(const Node &o, const Node &a, const Node &b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline long long Rotate_calipers() {
  --top, reverse(sta + t + 1, sta + top + 1), sta[0] = sta[--top];
  long long ans = 0, p = 0;
  for(int i = 0; i < top; ++i) {
    while( Check(sta[p], sta[i], sta[i + 1]) < Check(sta[p + 1], sta[i], sta[i + 1]) ) p = (p + 1) % n;
    long long tmp_1 = max(Distance(sta[i], sta[p]), Distance(sta[i + 1], sta[p]));
    long long tmp_2 = max(Distance(sta[i], sta[p + 1]), Distance(sta[i + 1], sta[p + 1]));
    ans = max(ans, max(tmp_1, tmp_2));
  }
  return ans;
}

int main(int argc, char const *argv[])
{
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) scanf("%lld%lld", &node[i].x, &node[i].y);
  if( n < 3 ) printf("%lld\n", n == 1 ? 0 : Distance(node[1], node[2])), exit(0);
  sort(node + 1, node + n + 1);
  t = top, sta[++top] = node[1], sta[++top] = node[2];
  for(int i = 3; i <= n; ++i) {
    while( top > t + 1 && Check(sta[top - 1], sta[top], node[i]) <= 0 ) --top;
    sta[++top] = node[i];
  }
  t = top, sta[++top] = node[1], sta[++top] = node[2];
  for(int i = 3; i <= n; ++i) {
    while( top > t + 1 && Check(sta[top - 1], sta[top], node[i]) >=  0 ) --top;
    sta[++top] = node[i];
  }
  printf("%lld\n", Rotate_calipers());

  return 0;
}