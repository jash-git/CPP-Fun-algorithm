//program 3-4-1
#include <stdlib.h>
#include <cstring>
#include <iostream>
using namespace std;

#define M 100

char sa[1000];
char sb[1000];

typedef struct _Node
{
    int s[M];
    int l;            //代表字符串的长度
    int c;
} Node,*pNode;


void add(pNode pa, pNode pb, pNode ans)
{
    int i,cc,k,palen,pblen,len;
    int ta, tb;
    pNode temp;
    if((pa->c<pb->c))   //保证Pa的次幂大
    {
        temp = pa;
        pa = pb;
        pb = temp;
    }
    ans->c = pb->c;
    cc = 0;
    k=pa->c - pb->c;
    palen=pa->l + pa->c;
    pblen=pb->l + pb->c;
    if(palen>pblen)
        len=palen;
    else
        len=pblen;
    len=len-ans->c;
    for(i=0; i<len; i++) //结果的长度最长为pa，pb之中的最大长度减去最低次幂
    {
        if(i<k)
            ta = 0;
        else
            ta = pa->s[i-k];//次幂高的补0，大于低的长度后与0进行计算
        if(i<pb->l)
            tb = pb->s[i];
        else
            tb = 0;
        if(i>=pa->l+k)
            ta = 0;
        ans->s[i] = (ta + tb + cc)%10;
        cc = (ta + tb + cc)/10;
    }
    if(cc)
        ans->s[i++] = cc;
    ans->l = i;
}

int main()
{
    Node ans,a,b;//ans用来存储结果，倒向存储
    cout << "输入大整数 a:"<<endl;
    cin >> sa;
    cout << "输入大整数 a的次幂:"<<endl;
    cin >> a.c;
    cout << "输入大整数 b:"<<endl;
    cin >> sb;
    cout << "输入大整数 b的次幂:"<<endl;
    cin >> b.c;
    a.l=strlen(sa);//sa,sb以字符串进行处理
    b.l=strlen(sb);
    int z=0,i;
    for(i = a.l-1; i >= 0; i--)
        a.s[z++]=sa[i]-'0';             //倒向存储
    z=0;
    for(i = b.l-1; i >= 0; i--)
        b.s[z++] = sb[i]-'0';
    cout << "a=";
    for(i = a.l-1; i >= 0; i--)
        cout << a.s[i];
    cout << "*10^"<<a.c;
    cout << endl;
    cout << "b=";
    for(i = b.l-1; i >= 0; i--)
        cout << b.s[i];
    cout << "*10^"<<b.c;
    cout << endl;
    add(&a, &b, &ans);
    cout << "最终结果为：";
    for(i = ans.l-1; i>=0; i--)
        cout << ans.s[i];  //ans用来存储结果，倒向存储
    cout << "*10^"<<ans.c;
    cout<<endl;
    return 0;
}
