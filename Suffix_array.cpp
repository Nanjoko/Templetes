#include <queue>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
char str[maxn];
int n, m, cnt[maxn], key[maxn], tmp[maxn], rk[maxn], sa[maxn], height[maxn];

inline void Suffix_array() {
  for(int i = 1; i <= m; ++i) cnt[i] = 0;
  for(int i = 1; i <= n; ++i) ++cnt[key[i] = str[i]];
  for(int i = 2; i <= m; ++i) cnt[i] = cnt[i] + cnt[i - 1];
  for(int i = n; i >= 1; --i) sa[cnt[key[i]]--] = i;
  for(int num = 0, k = 1; k <= n; k = k << 1) {
    for(int i = n - k + 1; i <= n; ++i) tmp[++num] = i;
    for(int i = 1; i <= n; ++i) if( sa[i] > k ) tmp[++num] = sa[i] - k;
    for(int i = 1; i <= m; ++i) cnt[i] = 0;
    for(int i = 1; i <= n; ++i) ++cnt[key[i]];
    for(int i = 2; i <= m; ++i) cnt[i] = cnt[i] + cnt[i - 1];
    for(int i = n; i >= 1; --i) sa[cnt[key[tmp[i]]]--] = tmp[i], tmp[i] = 0;
    swap(key, tmp), num = 1, key[sa[1]] = 1;
    for(int i = 2; i <= n; ++i)
      key[sa[i]] = (num = num + (tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + k] != tmp[sa[i - 1] + k]));
    if( num == n ) break;
    m = num, num = 0;
  }
}

inline void String_height() {
  for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
  for(int k = 0, i = 1; i <= n; ++i) {
    if( rk[i] == 1 ) continue;
    if( k ) --k;
    while( i + k <= n && sa[rk[i] - 1] + k <= n && str[sa[rk[i] - 1] + k] == str[i + k] ) ++k;
    height[rk[i]] = k;
  }
}

int main(int argc, char const *argv[])
{
  scanf("%s", str + 1), n = strlen(str + 1), m = 127;
  Suffix_array();
  for(int i = 1; i <= n; ++i) printf("%d ", sa[i]);

  return 0;
}