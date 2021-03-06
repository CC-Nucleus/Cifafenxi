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

/* 单词编码 */
enum e_TokenCode
{
	/* 运算符及分隔符 */
	TK_PLUS,		// + 加号      !!
	TK_MINUS,		// - 减号		!!
	TK_STAR,		// * 星号		!!
	TK_DIVIDE,		// / 除号		!!
	TK_MOD,			// % 求余运算符		!!
	TK_EQ,			// == 等于号
	TK_NEQ,			// != 不等于号
	TK_LT,			// < 小于号
	TK_LEQ,			// <= 小于等于号
	TK_GT,			// > 大于号
	TK_GEQ,			// >= 大于等于号
	TK_ASSIGN,		// = 赋值运算符 
	TK_POINTSTO,	// -> 指向结构体成员运算符
	TK_DOT,			// . 结构体成员运算符
	TK_AND,         // & 地址与运算符
	TK_OPENPA,		// ( 左圆括号
	TK_CLOSEPA,		// ) 右圆括号
	TK_OPENBR,		// [ 左中括号
	TK_CLOSEBR,		// ] 右圆括号
	TK_BEGIN,		// { 左大括号
	TK_END,			// } 右大括号
	TK_SEMICOLON,	// ; 分号    
	TK_COMMA,		// , 逗号
	TK_ELLIPSIS,	// ... 省略号
	TK_EOF,			// 文件结束符

	/* 常量 */
	TK_CINT,		// 整型常量
	TK_CCHAR,		// 字符常量
	TK_CSTR,		// 字符串常量

	/* 关键字 */
	KW_CHAR,		// char关键字
	KW_SHORT,		// short关键字
	KW_INT,			// int关键字
	KW_VOID,		// void关键字  
	KW_STRUCT,		// struct关键字   
	KW_IF,			// if关键字
	KW_ELSE,		// else关键字
	KW_FOR,			// for关键字
	KW_CONTINUE,	// continue关键字
	KW_BREAK,		// break关键字   
	KW_RETURN,		// return关键字
	KW_SIZEOF,		// sizeof关键字

	KW_ALIGN,		// __align关键字	
	KW_CDECL,		// __cdecl关键字 standard c call
	KW_STDCALL,     // __stdcall关键字 pascal c call

	/* 标识符 */
	TK_IDENT  //函数
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
	{TK_CINT,NULL,"整型常量"},
	{TK_CCHAR,NULL,"字符常量"},
	{TK_CSTR,NULL,"字符串常量"},
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