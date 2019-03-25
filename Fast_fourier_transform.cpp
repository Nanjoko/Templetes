#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const double pi = acos(-1.0);
const int maxn = 5000000 + 10;
int n, m, len, limit, rado, r[maxn];

struct Complex {
  double x, y;
  Complex(double tx = 0, double ty = 0) { x = tx, y = ty; }
} f_1[maxn], f_2[maxn];

inline Complex operator + (const Complex &a, const Complex &b) { return Complex(a.x + b.x, a.y + b.y); }
inline Complex operator - (const Complex &a, const Complex &b) { return Complex(a.x - b.x, a.y - b.y); }
inline Complex operator * (const Complex &a, const Complex &b) { return Complex(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y); }

inline int read() {
  register char ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w |= (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

inline void Fast_fourior_transform(Complex *a, int type) {
  for(int i = 0; i < limit; ++i) if( i < r[i] ) swap(a[i], a[r[i]]);
  for(int mid = 1; mid < limit; mid = mid << 1) {
    Complex Base_w = Complex(cos(pi / mid), type * sin(pi / mid));
    for(int len = mid << 1, l = 0; l < limit; l = l + len) {
      Complex w = Complex(1, 0);
      for(int k = 0; k < mid; ++k, w = w * Base_w) {
        Complex tmp_1 = a[l + k], tmp_2 = w * a[l + mid + k];
        a[l + k] = tmp_1 + tmp_2, a[l + mid + k] = tmp_1 - tmp_2;
      }
    }
  }
}

int main(int argc, char const *argv[])
{
  freopen("..\\nanjolno.in", "r", stdin);
  freopen("..\\nanjolno.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 0; i <= n; ++i) f_1[i].x = read();
  for(int i = 0; i <= m; ++i) f_2[i].x = read();
  len = n + m, limit = 1, rado = 0;
  while( limit <= len ) limit = limit << 1, ++rado;
  for(int i = 0; i < limit; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (rado - 1));
  Fast_fourior_transform(f_1, 1);
  Fast_fourior_transform(f_2, 1);
  for(int i = 0; i < limit; ++i) f_1[i] = f_1[i] * f_2[i];
  Fast_fourior_transform(f_1, -1);
  for(int i = 0; i <= len; ++i) printf("%d\n", (int)(f_1[i].x / limit + 0.1));

  fclose(stdin), fclose(stdout);
  return 0;
}