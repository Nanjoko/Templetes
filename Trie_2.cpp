//数组模拟trie树查询是否出现 
/*
  trie tree的储存方式：将字母储存在边上，边的节点连接与它相连的字母 
  trie[rt][x]=tot: rt是上个节点编号(father)，x是字母(child)，tot是下个节点编号(next)
*/ 
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define maxn 2000010
using namespace std;
int tot=0, rt=1, n;
int trie[maxn][26];
int isw[maxn];		//查询整个单词用

void insert(char *s,int rt)
{
    for(int i=0; s[i]; i++)
    {
        int x=s[i]-'a';
        if( !trie[rt][x] )		//现在插入的字母在之前同一节点处未出现过 
        {
            trie[rt][x] = ++tot;		//字母插入一个新的位置，否则不做处理 
        }
        rt = trie[rt][x];		//为下个字母的插入做准备  
    }
    isw[rt] = 1;		//标志该单词末位字母的尾结点
}

bool find(char *s,int rt)
{
    for(int i=0; s[i]; ++i)
    {
        int x=s[i]-'a';
        if( !trie[rt][x] )
			return 0;		//以rt为头结点的x字母不存在，返回0 
        rt = trie[rt][x];		//为查询下个字母做准备 
    }
    return isw[rt];
}

char s[55];
int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; ++i)
    {
        cin >> s;
        insert(s, rt);
    }
    scanf("%d", &n);
    for(int i=1; i<=n; ++i)
    {
        cin>>s;
        if( find(s,rt) )
			printf("YES\n");
        else
			printf("NO\n");
    }
    return 0;
}
