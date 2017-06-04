//��vc�Ͽ���˳�����У���scanf������ɼ���
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


unsigned char rc4key[256];//�������Կ��
unsigned char s[256];//��ʼ���׶����õ�s��

void swap(unsigned char si, unsigned char sj)//����si��sj��ֵ
{
	unsigned char temp;
	temp = si;
	si = sj;
	sj = temp;
}


void init_s(unsigned char key_data[])//��ʼ��s��
{
	int i, j;
	for (i = 0; i<256; i++)//s���ȳ�ʼ��Ϊs[0]=0,s[1]=1,...,s[255]=255
		s[i] = i;

	for (i = 0; i<256; i++)//��ʼ����Կ��
	{
		j = i % 256;
		rc4key[i] = key_data[j];
	}

	for (i = 0, j = 0; i<256; i++)//������Կ��rc4key���s��
	{
		j = (rc4key[i] + s[i] + j) % 256;
		swap(s[i], s[j]);
	}
}


void create_key(int buffer_len)//������Կ����
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


unsigned char *rc4(unsigned char buffer_data[], int buffer_len)//���ܺͽ��ܲ���
{
	int i;
	unsigned char *result = (unsigned char *)malloc(sizeof(unsigned char)*buffer_len + 1);
	for (i = 0; i<buffer_len; i++)//���������е������������Կ���н�����򣬾Ϳ��Խ��м��ܺͽ���
		result[i] = buffer_data[i] ^ rc4key[i];
	result[i] = '\0';
	return result;//���ؼ��ܺ�����Ļ���ܺ������
}


int main()
{
	int i, m, n;
	int key_len = 0;
	int buf_len = 0;
	unsigned char key_data[256];
	unsigned char buf_data[1024];
	unsigned char *result;
	printf("���ܽ�����ʾ!\n");
	printf("��������Կ��");
	scanf_s("%s", key_data);
	for (m = 0; m<256; m++)
		if (key_data[m] != '\0') key_len++;

	printf("���������ģ�");
	scanf_s("%s", buf_data);
	for (n = 0; n<1024; n++)
		if (buf_data[n] != '\0') buf_len++;

	init_s(key_data);
	create_key(buf_len);

	result = rc4(buf_data, buf_len);
	printf("\n���ܺ������Ϊ��%s\n\n", result);

	result = rc4(result, buf_len);
	printf("���ܺ������Ϊ��%s\n", result);
	return 1;
}