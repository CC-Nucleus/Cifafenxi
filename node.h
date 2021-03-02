#define _CRT_SECURE_NO_WARNINGS
#pragma once
#define MAXKEY 1000
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
static char ch;

typedef struct node {
	int tokenCode;
	struct node *pNext;
	char *pWord;
}Node_t, *pNode_t;

typedef struct wordNode {
	pNode_t ptokenNode;
	struct wordNode* pNext;
}WordNode_t, *pWordNode_t;

pWordNode_t pHead = NULL;
pWordNode_t pTail = NULL;

/* ���ʱ��� */
enum e_TokenCode
{
	/* ��������ָ��� */
	TK_PLUS,		// + �Ӻ�      !!
	TK_MINUS,		// - ����		!!
	TK_STAR,		// * �Ǻ�		!!
	TK_DIVIDE,		// / ����		!!
	TK_MOD,			// % ���������		!!
	TK_EQ,			// == ���ں�
	TK_NEQ,			// != �����ں�
	TK_LT,			// < С�ں�
	TK_LEQ,			// <= С�ڵ��ں�
	TK_GT,			// > ���ں�
	TK_GEQ,			// >= ���ڵ��ں�
	TK_ASSIGN,		// = ��ֵ����� 
	TK_POINTSTO,	// -> ָ��ṹ���Ա�����
	TK_DOT,			// . �ṹ���Ա�����
	TK_AND,         // & ��ַ�������
	TK_OPENPA,		// ( ��Բ����
	TK_CLOSEPA,		// ) ��Բ����
	TK_OPENBR,		// [ ��������
	TK_CLOSEBR,		// ] ��Բ����
	TK_BEGIN,		// { �������
	TK_END,			// } �Ҵ�����
	TK_SEMICOLON,	// ; �ֺ�    
	TK_COMMA,		// , ����
	TK_ELLIPSIS,	// ... ʡ�Ժ�
	TK_EOF,			// �ļ�������

	/* ���� */
	TK_CINT,		// ���ͳ���
	TK_CCHAR,		// �ַ�����
	TK_CSTR,		// �ַ�������

	/* �ؼ��� */
	KW_CHAR,		// char�ؼ���
	KW_SHORT,		// short�ؼ���
	KW_INT,			// int�ؼ���
	KW_VOID,		// void�ؼ���  
	KW_STRUCT,		// struct�ؼ���   
	KW_IF,			// if�ؼ���
	KW_ELSE,		// else�ؼ���
	KW_FOR,			// for�ؼ���
	KW_CONTINUE,	// continue�ؼ���
	KW_BREAK,		// break�ؼ���   
	KW_RETURN,		// return�ؼ���
	KW_SIZEOF,		// sizeof�ؼ���

	KW_ALIGN,		// __align�ؼ���	
	KW_CDECL,		// __cdecl�ؼ��� standard c call
	KW_STDCALL,     // __stdcall�ؼ��� pascal c call

	/* ��ʶ�� */
	TK_IDENT  //����
};

Node_t preInsert[] = {
	{TK_PLUS,NULL,"+"},
	{TK_MINUS,NULL,"-"},
	{TK_STAR,NULL,"*"},
	{TK_DIVIDE,NULL,"/"},
	{TK_MOD,NULL,"%"},
	{TK_EQ,NULL,"=="},
	{TK_NEQ,NULL,"!="},
	{TK_LT,NULL,"<"},
	{TK_LEQ,NULL,"<="},
	{TK_GT,NULL,">"},
	{TK_GEQ,NULL,">="},
	{TK_ASSIGN,NULL,"="},
	{TK_POINTSTO,NULL,"->"},
	{TK_DOT,NULL,"."},
	{TK_AND,NULL,"&"},
	{TK_OPENPA,NULL,"("},
	{TK_CLOSEPA,NULL,")"},
	{TK_OPENBR,NULL,"["},
	{TK_CLOSEBR,NULL,"]"},
	{TK_BEGIN,NULL,"{"},
	{TK_END,NULL,"}"},
	{TK_SEMICOLON,NULL,";"},
	{TK_COMMA,NULL,","},
	{TK_ELLIPSIS,NULL,"..."},
	{TK_EOF,NULL,"End_Of_File"},
	{TK_CINT,NULL,"���ͳ���"},
	{TK_CCHAR,NULL,"�ַ�����"},
	{TK_CSTR,NULL,"�ַ�������"},
	{KW_CHAR,NULL,"char"},
	{KW_SHORT,NULL,"short"},
	{KW_INT,NULL,"int"},
	{KW_VOID,NULL,"void"},
	{KW_STRUCT,NULL,"struct"},
	{KW_IF,NULL,"if"},
	{KW_ELSE,NULL,"else"},
	{KW_FOR,NULL,"for"},
	{KW_CONTINUE,NULL,"continue"},
	{KW_BREAK,NULL,"break"},
	{KW_RETURN,NULL,"return"},
	{KW_SIZEOF,NULL,"sizeof"},
	{KW_ALIGN,NULL,"__align"},
	{KW_CDECL,NULL,"__cdecl"},
	{KW_STDCALL,NULL,"__stdcall"}
};
pNode_t hashTable[MAXKEY] = { 0 };
int hash(char *key);
void insertHashTable(pNode_t* hashTable, pNode_t pnode);
void findHashTable(pNode_t*hashTable, pNode_t pInsert);
void wordTailInsert(pWordNode_t *ppHead, pWordNode_t *ppTail, pNode_t ptokenNode);
void printWordList(pWordNode_t pHead);
void alp2word(FILE *fp,  pNode_t pnode);
void initHashTable();