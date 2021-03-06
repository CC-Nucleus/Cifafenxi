#include"node.h"

int main(int argc, char *argv[]) {

	initHashTable();
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen : ");
	}

	//循环读取字符
	while ((ch = fgetc(fp)) != EOF) {
		pNode_t pnode = (pNode_t)calloc(1, sizeof(Node_t));
		alp2word(fp, pnode);            
		findHashTable(hashTable, pnode);
		wordTailInsert(&pHead, &pTail, pnode);
	}
	printWordList(pHead);
}
//初始化哈希表，把所有非标识符，非常量存入。
void insertHashTable(pNode_t* hashTable, pNode_t pnode) {
	int hashValue = hash(pnode->pWord);
	if (hashTable[hashValue] == NULL) {
		hashTable[hashValue] = pnode;
	}
	else {
		pnode->pNext = hashTable[hashValue];//pHead
		hashTable[hashValue] = pnode;
	}
}
//在哈希表里查找并插入
void findHashTable(pNode_t*hashTable, pNode_t pInsert) {
	int hashValue = hash(pInsert->pWord);
	if (hashTable[hashValue] == NULL) {//如果没有发生碰撞
		insertHashTable(hashTable, pInsert);

	}
	else {
		pNode_t pCur = hashTable[hashValue];
		while (pCur) {
			if (strcmp(pCur->pWord, pInsert->pWord) == 0) {
				pInsert->tokenCode = pCur->tokenCode;
				break;
			}
			pCur = pCur->pNext;
		}
		if (pCur == NULL) {
			insertHashTable(hashTable, pInsert);
		}
	}
}
//尾插法链接链表
void wordTailInsert(pWordNode_t *ppHead, pWordNode_t *ppTail, pNode_t ptokenNode) {
	pWordNode_t pNew = (pWordNode_t)calloc(1, sizeof(WordNode_t));
	pNew->ptokenNode = ptokenNode;
	if (*ppHead == NULL) {
		*ppHead = pNew;
		*ppTail = pNew;
	}
	else {
		(*ppTail)->pNext = pNew;
		*ppTail = pNew;
	}
}
//设置打印方式
void printWordList(pWordNode_t pHead) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	pWordNode_t pCur = pHead;
	while (pCur) {
		if (pCur->ptokenNode->tokenCode <= TK_EOF)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED);
		}
		else if (pCur->ptokenNode->tokenCode >= KW_CHAR &&
			pCur->ptokenNode->tokenCode <= KW_STDCALL) {
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (pCur->ptokenNode->tokenCode >= TK_CINT &&
			pCur->ptokenNode->tokenCode <= TK_CSTR)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
		}
		else {
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
		}
		printf("%s", pCur->ptokenNode->pWord);
		pCur = pCur->pNext;
	}
}
//将文件字符一个个读取并判断组建“单词”。
void alp2word(FILE *fp, pNode_t pnode) {
	char *word = (char *)calloc(30, 1);
	int wordPos = 0;
	pnode->pWord = word;
	pnode->tokenCode = TK_IDENT;
	//+ += 标识符 整型常量 空白 浮点型常量
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
		word[wordPos++] = ch;
		return;
	}
	else if (ch == ';' || ch == ',' || ch == '&') {
		word[wordPos++] = ch;
		return;
	}
	else if (ch == ' ' || ch == '\n'||ch =='\t') {
		word[wordPos++] = ch;
		pnode->tokenCode = -1;
		return;
	}
	//直接读取的字符
	else if (ch == '(' || ch == ')') {
		word[wordPos++] = ch;
		return;
	}
	else if (ch == '[' || ch == ']') {
		word[wordPos++] = ch;
		return;
	}
	else if (ch == '{' || ch == '}') {
		word[wordPos++] = ch;
		return;
	}
	else if (ch == '_' || ch >= 'a' && ch <= 'z'|| ch >= 'A' && ch <= 'Z') {
		word[wordPos++] = ch;
		ch = fgetc(fp);
		while (ch == '_' || ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9' || ch >= 'A' && ch <= 'Z') {
			word[wordPos++] = ch;
			ch = fgetc(fp);
		}
		fseek(fp, -1, SEEK_CUR);
		return;
	}
	//整型 浮点型常量
	else if (ch >= '0' && ch <= '9') {
		word[wordPos++] = ch;
		ch = fgetc(fp);
		while (ch >= '0' && ch <= '9') {
			word[wordPos++] = ch;
			ch = fgetc(fp);
		}
		if (ch != '.') {
			pnode->tokenCode = TK_CINT;
			fseek(fp, -1, SEEK_CUR);
			return;
		}
		word[wordPos++] = ch;
		ch = fgetc(fp);
		while (ch >= '0' && ch <= '9') {
			word[wordPos++] = ch;
			ch = fgetc(fp);
		}
		pnode->tokenCode = TK_CINT;
		fseek(fp, -1, SEEK_CUR);
		return;
	}
	//后面可加‘=’的运算符
	else if (ch == '<' || ch == '>' || ch == '=' || ch == '!')
	{
		word[wordPos++] = ch;
		ch = fgetc(fp);
		if (ch == '=')
		{
			word[wordPos++] = ch;
			return;
		}
		fseek(fp, -1, SEEK_CUR);
		return;
	}
	//' -> '
	else if (ch == '-')
	{
		word[wordPos++] = ch;
		ch = fgetc(fp);
		if (ch == '>')
		{
			word[wordPos++] = ch;
			return;
		}
	}
	// \' 字符常量
	else if (ch == 39) {
		pnode->tokenCode = TK_CCHAR;
		word[wordPos++] = ch;
		ch = fgetc(fp);
		while (ch != 39) {
			word[wordPos++] = ch;
			ch = fgetc(fp);
		}
		word[wordPos++] = ch;
	}
	//字符串常量
	else if (ch == 34) {
		word[wordPos++] = ch;
		ch = fgetc(fp);
		while (ch != 34) {
			word[wordPos++] = ch;
			ch = fgetc(fp);
		}
		word[wordPos++] = ch;
		pnode->tokenCode = TK_CSTR;
		return;
	}
	else if (ch == '|') {
		word[wordPos++] = ch;
	}
}
void initHashTable() {
	for (int i = 0; i < sizeof(preInsert) / sizeof(Node_t); ++i) {
		insertHashTable(hashTable, &preInsert[i]);
	}
}