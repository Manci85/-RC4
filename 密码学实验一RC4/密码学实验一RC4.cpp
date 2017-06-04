//在vc上可以顺利运行，将scanf设置完成即可
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


unsigned char rc4key[256];//随机化密钥表
unsigned char s[256];//初始化阶段所用的s表

void swap(unsigned char si, unsigned char sj)//交换si和sj的值
{
	unsigned char temp;
	temp = si;
	si = sj;
	sj = temp;
}


void init_s(unsigned char key_data[])//初始化s表
{
	int i, j;
	for (i = 0; i<256; i++)//s表先初始化为s[0]=0,s[1]=1,...,s[255]=255
		s[i] = i;

	for (i = 0; i<256; i++)//初始化密钥表
	{
		j = i % 256;
		rc4key[i] = key_data[j];
	}

	for (i = 0, j = 0; i<256; i++)//根据密钥表rc4key填充s表
	{
		j = (rc4key[i] + s[i] + j) % 256;
		swap(s[i], s[j]);
	}
}


void create_key(int buffer_len)//生成密钥序列
{
	int t, i, j;
	int counter;
	unsigned char keystream[1024];
	for (counter = 0; counter<buffer_len; counter++)
	{
		i = (i + 1) % 256;
		j = (s[i] + j) % 256;
		swap(s[i], s[j]);
		t = (s[i] + s[j]) % 256;
		keystream[counter] = s[t];
	}
}


unsigned char *rc4(unsigned char buffer_data[], int buffer_len)//加密和解密操作
{
	int i;
	unsigned char *result = (unsigned char *)malloc(sizeof(unsigned char)*buffer_len + 1);
	for (i = 0; i<buffer_len; i++)//将缓冲区中的数据与随机密钥序列进行异或，就可以进行加密和解密
		result[i] = buffer_data[i] ^ rc4key[i];
	result[i] = '\0';
	return result;//返回加密后的密文或解密后的明文
}


int main()
{
	int i, m, n;
	int key_len = 0;
	int buf_len = 0;
	unsigned char key_data[256];
	unsigned char buf_data[1024];
	unsigned char *result;
	printf("加密解密演示!\n");
	printf("请输入密钥：");
	scanf_s("%s", key_data);
	for (m = 0; m<256; m++)
		if (key_data[m] != '\0') key_len++;

	printf("请输入明文：");
	scanf_s("%s", buf_data);
	for (n = 0; n<1024; n++)
		if (buf_data[n] != '\0') buf_len++;

	init_s(key_data);
	create_key(buf_len);

	result = rc4(buf_data, buf_len);
	printf("\n加密后的密文为：%s\n\n", result);

	result = rc4(result, buf_len);
	printf("解密后的明文为：%s\n", result);
	return 1;
}