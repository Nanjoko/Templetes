#define miho register int
#include<cstdio>
#include<cstring>
#define max(a,b) ((a)>(b)?(a):(b))

inline int turn(int *b, int x) {
    int t = 0;
    while(x) b[++t] = x % 10, x /= 10;
    return t;
}
class bign {
    protected:
        static const int maxn = 1e5 + 10;
        int a[maxn];
    public:
        bign() {
            memset(a,0,sizeof a);
        }

        bign operator + (const bign& b) const {
            bign c;
            int x=0;
            c.a[0] = max(this->a[0], b.a[0]) + 1;
            for(miho i=1; i<=c.a[0]; ++i) {
                c.a[i] = this->a[i] + b.a[i] + x;
                x=c.a[i] / 10;
                c.a[i] %= 10;
            }
            while( !c.a[c.a[0]] ) --c.a[0];
            return c;
        }
        bign operator * (int n) {
            bign c;
            int b[maxn], x = 0, lenb = turn(b, n);
            c.a[0] = this->a[0] + lenb + 1;
            for(miho i=1; i<=this->a[0]; ++i) {
                x = 0;
                for(miho j=1; j<=lenb; ++j) {
                    c.a[i+j-1] += this->a[i] * b[j] + x;
                    x = c.a[i+j-1] / 10;
                    c.a[i+j-1] %= 10;
                }
                c.a[i+lenb] = x;
            }
            while( !c.a[c.a[0]] ) --c.a[0];
            return c;
        }
        bign operator += (int b) {
            int t = 1;
            this->a[1] += 1;
            while( this->a[t]==10 ) {
                this->a[t] %= 10;
                a[++t] += 1;
            }
        }
        bign operator = (int b) {
            int t = 0;
            memset(this->a, 0, sizeof(this->a));
            while(b) {
                this->a[++t] = b % 10;
                b /= 10;
            }
            this->a[0] = t;
        }
        
        void read() {
            char ss[maxn];
            scanf("%s", ss);
            int len = strlen(ss);
            this->a[0] = len;
            for(int i=1; i<=len; ++i) this->a[i] = ss[len-i]^48;
        }
        void print() {
            
            for(miho i=this->a[0]; i>=1; --i) {
                printf("%d", this->a[i]);
            }
        }
};

bign b, add, ans;

int main() {
    int n;
    scanf("%d", &n);
    
    for(miho i=1; i<=n; ++i) {
        add = 1;
        for(miho j=1; j<=i; ++j) {
            add = add * j;
        }
        ans = ans + add;
    }
    ans.print();
    return 0;
}

