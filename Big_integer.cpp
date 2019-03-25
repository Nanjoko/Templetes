#include <iostream>
#include <cstdio>
#include <cstring>
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)<0?-(a):(a))
using std::swap;

class bign {
    protected:
        static const int maxn = 100010;
        int a[maxn], f;
    public:
        bign() { f=0; memset(a,0,sizeof a); }
        
        inline void operator = (int a) {
        	int len;
        	if(!a) { this->a[0]=1;return; }
        	if(a<0) this->f=1;
        	for(len=1;a;++len,a/=10) {
        		this->a[len]=abs(a%10);
            }
            this->a[0]=len-1;
        }
        
        inline int operator < (const bign& b) const {
            if(this->a[0]!=b.a[0]) return this->a[0]<b.a[0];
            for(int i=this->a[0];i>=1;--i) {
                if(this->a[i]!=b.a[i]) return this->a[i]<b.a[i];
            }
            return 0;
        }
        
        inline bign operator + (const bign& b) const {
        	bign c;
            if(this->f&&b.f) c.f=1;
            if(this->f) return b-*this;
            if(b.f) return *this-b;
            int x=0;
            c.a[0]=max(this->a[0],b.a[0])+1;
            for(int i=1;i<=c.a[0];++i) {
                c.a[i]=this->a[i]+b.a[i]+x;
                x=c.a[i]/10;
                c.a[i]%=10;
            }
            while(!c.a[c.a[0]]&&c.a[0]>1) --c.a[0];
            return c;
        }
        
        inline void operator += (const bign& b) {
            *this=*this+b;
        }
        
        inline bign operator - (const bign& b) const {
            bign a0=*this,a1=b,c;
            if(a0<a1) swap(a0,a1),c.f=1;
            c.a[0]=a0.a[0];
            for(int i=1;i<=c.a[0];++i) {
                c.a[i]=a0.a[i]-a1.a[i];
                if(c.a[i]<0) c.a[i]+=10,--a0.a[i+1];
            }
            while(!c.a[c.a[0]]&&c.a[0]>1) --c.a[0];
            if(c.a[0]==1&&!c.a[1]) c.f=0;
            return c;
        }
        
        inline bign operator * (const int& b) const {
            bign c;
            c.a[0]=this->a[0];
            int x=0;
            for(int i=1;i<=c.a[0];++i) {
                c.a[i]=this->a[i]*b+x;
                x=c.a[i]/10;
                c.a[i]%=10;
            }
            for(++c.a[0];x;x/=10,++c.a[0]) {
                c.a[c.a[0]]=x%10;
            }
            while(!c.a[c.a[0]]&&c.a[0]>1) --c.a[0];
            return c;
        }
        
        inline bign operator * (const bign& b) const {
            bign c;
            c.a[0]=this->a[0]+b.a[0]-1;
            for(int i=1;i<=this->a[0];++i) {
                for(int j=1;j<=b.a[0];++j) {
                    c.a[i+j-1]+=this->a[i]*b.a[j];
                    c.a[i+j]+=c.a[i+j-1]/10;
                    c.a[i+j-1]%=10;
                }
            }
            if(c.a[c.a[0]+1]) ++c.a[0];
            while(!c.a[c.a[0]]&&c.a[0]>1) --c.a[0];
            return c;
        }
        
        inline void read() {
            char ss[maxn];
            scanf("%s",ss);
            int len = strlen(ss);
            this->a[0]=ss[0]=='-'?len-1:len;
            this->f=int(ss[0]=='-');
            for(int i=1;i<=len;++i) this->a[i]=ss[len-i]^48;
        }
        
        inline void print() {
            if(this->f) printf("-");
            for(int i=this->a[0];i>=1;--i) {
                printf("%d",this->a[i]);
            }
        }
};

bign a[25];
bign flag;

int main(int argc,char** argv) {
    int n,f;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) a[i].read();
    for(int i=1;i<=n;++i) {
        if(flag<a[i]) flag=a[i],f=i; 
    }
    printf("%d\n",f);
    flag.print();
    return 0;
}
