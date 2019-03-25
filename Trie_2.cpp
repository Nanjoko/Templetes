//����ģ��trie����ѯ�Ƿ���� 
/*
  trie tree�Ĵ��淽ʽ������ĸ�����ڱ��ϣ��ߵĽڵ�����������������ĸ 
  trie[rt][x]=tot: rt���ϸ��ڵ���(father)��x����ĸ(child)��tot���¸��ڵ���(next)
*/ 
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define maxn 2000010
using namespace std;
int tot=0, rt=1, n;
int trie[maxn][26];
int isw[maxn];		//��ѯ����������

void insert(char *s,int rt)
{
    for(int i=0; s[i]; i++)
    {
        int x=s[i]-'a';
        if( !trie[rt][x] )		//���ڲ������ĸ��֮ǰͬһ�ڵ㴦δ���ֹ� 
        {
            trie[rt][x] = ++tot;		//��ĸ����һ���µ�λ�ã����������� 
        }
        rt = trie[rt][x];		//Ϊ�¸���ĸ�Ĳ�����׼��  
    }
    isw[rt] = 1;		//��־�õ���ĩλ��ĸ��β���
}

bool find(char *s,int rt)
{
    for(int i=0; s[i]; ++i)
    {
        int x=s[i]-'a';
        if( !trie[rt][x] )
			return 0;		//��rtΪͷ����x��ĸ�����ڣ�����0 
        rt = trie[rt][x];		//Ϊ��ѯ�¸���ĸ��׼�� 
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
