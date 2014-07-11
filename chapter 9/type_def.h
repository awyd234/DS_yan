#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

#define ERROR -1
#define OK 1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define FILE_NOT_EXIT -3;	  // ���ļ�ʧ��
#define STACK_INIT_SIZE 100   // ջ��ʼ��ֵ
#define STACKINCREMENT 10     // ջ����ÿ�����ӵ�ֵ
#define DATA_SIZE	20		  // �����������ݵĴ�С


typedef int Status;
typedef bool Boolean;

typedef int KeyType;

typedef struct{
	KeyType	key;			// �ؼ���
	char data[DATA_SIZE];	// ��������
	int weight;				// Ȩֵ
}ElemType;

//----- �������͹ؼ��ֶ��� -----
#define EQ(a,b)	((a)==(b))
#define LT(a,b)	((a)<(b))
#define LQ(a,b) ((a)<=(b))

#endif