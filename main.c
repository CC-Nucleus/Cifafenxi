#include"node.h"

int main(int argc, char *argv[]) {

	initHashTable();
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen : ");
	}

	//ѭ����ȡ�ַ�
	while ((ch = fgetc(fp)) != EOF) {
		pNode_t pnode = (pNode_t)calloc(1, sizeof(Node_t));
		alp2word(fp, pnode);            
		findHashTable(hashTable, pnode);
		wordTailInsert(&pHead, &pTail, pnode);
	}
	printWordList(pHead);
}
//��ʼ����ϣ�������зǱ�ʶ�����ǳ������롣
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
//�ڹ�ϣ������Ҳ�����
void findHashTable(pNode_t*hashTable, pNode_t pInsert) {
	int hashValue = hash(pInsert->pWord);
	if (hashTable[hashValue] == NULL) {//���û�з�����ײ
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
//β�巨��������
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
//���ô�ӡ��ʽ
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
//���ļ��ַ�һ������ȡ���ж��齨�����ʡ���
void alp2word(FILE *fp, pNode_t pnode) {
	char *word = (char *)calloc(30, 1);
	int wordPos = 0;
	pnode->pWord = word;
	pnode->tokenCode = TK_IDENT;
	//+ += ��ʶ�� ���ͳ��� �հ� �����ͳ���
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
	//ֱ�Ӷ�ȡ���ַ�
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
	//���� �����ͳ���
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
	//����ɼӡ�=���������
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
	// \' �ַ�����
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
	//�ַ�������
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