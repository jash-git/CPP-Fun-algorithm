//program 4-2
#include <iostream>
#include <cstring>
using namespace std;
const int N=100;
char str1[N],str2[N];
int d[N][N]; //���帨�����飬d[i][j]��ʾstr1ǰi���ַ���str2ǰj���ַ��ı༭���롣

int min(int a, int b)
{
    return a<b?a:b;//���ؽ�С��ֵ
}

int editdistance(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);//ȡ�ַ�����С

    for(int i=0;i<=len1;i++)//���ڶ���������Ϊ0���༭�����ʼ��Ϊi
        d[i][0]= i;

    for(int j=0;j<=len2;j++)//����һ��������Ϊ0���༭�����ʼ��Ϊj
        d[0][j]=j;

    for(int i=1;i <=len1;i++)//������������
    {
        for(int j=1;j<=len2;j++)
        {
            int diff;//�ж�str[i]�Ƿ����str2[j],���Ϊ0�������øı�str1�������Ϊ1��������Ҫ�ı�str1��
            if(str1[i-1] == str2[j-1])//���
                diff = 0 ;
            else
                diff = 1 ;
            int temp = min(d[i-1][j] + 1, d[i][j-1] + 1);//������ȡ��Сֵ
            d[i][j] = min(temp, d[i-1][j-1] + diff);//��ȡ��Сֵ���൱������ȡ��Сֵd[i-1][j] + 1, d[i][j-1] + 1��d[i-1][j-1] + diff
        }
    }
    return d[len1][len2];
}
int main()
{
    cout << "�����ַ���str1:"<<endl;
    cin >> str1;
    cout << "�����ַ���str2:"<<endl;
    cin >> str2;
    cout << str1<< "��"<<str2<<"�ı༭������:"<<editdistance(str1,str2);
    return 0;
}
