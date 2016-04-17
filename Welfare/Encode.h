#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#define GROUP	0
#define DIRECT	1

using std::vector;

typedef struct
{
	int codeSeq[3];
	unsigned int mantissa;
	int frequency;
	int span;					// ���
}CodeType;

typedef struct
{
	int x;
	int y;
}Gossip;

class Encode
{
private:
	bool codeFlag;				// �Ƿ�������б�־
	bool isInQueue;				// �Ƿ���ӵ�����
	bool isMerge;
	int codetype;
public:
	vector<CodeType> dvCode;
	vector<CodeType> backup;
	// ɱ��ͣ�ɱ��ͷ��ȫ��ȫС��ȫ��ȫż
	vector<CodeType> recycleBin;

	// ɱ�����

	Encode();
	~Encode();

	// 3�������뺯�����ɹ���������ɵı������
	int encodingThree(vector<int>, vector<int>, vector<int>);
	int encodingTwo(vector<int>, vector<int>, vector<int>);
	int encoding(vector<int>, vector<int>, vector<int>,bool);
	// 4�������뺯�����ɹ������ر������
	int encoding(vector<int>, vector<int>, vector<int>, vector<int>,bool);
	
	// �������
	int encodingTwoCombination(vector<int>**,int);
	int encodingTwoCombination(vector<int>, vector<int>, vector<int>);
	int encodingTwoCombination(vector<int>, vector<int>, vector<int>, vector<int>);

	// ȥ��
	int de_weight();
	// ��ѡ����
	int groupChoose();
	// ��ѡתֱѡ
	int grouptodirect();
	// ��������,���ر������
	int ordering();
	int orderForRecycleBin();
	// ��Ƶ������
	int orderByFreq();

	// ��ֵ��С����
	int orderByVal();

	// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);

		// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<Gossip>);
	
	// ���ѡ��
	int selectBasedSpan(vector<int> span);

	// ɸѡ��ֵ
	int siftPlus(int min, int max);

	// ������
	int tcSelect(char *tcSelect);

	// ����ѡ��
	int dsSelect(char *dsSequence);
	// ɱ���
	int killBig(int big=20);

	// �����������
	int getCodeType();
	// ������������
	int setCodeType(int ct);

	bool getIsMerge();
	void setIsMerge(bool isMerge);

	// �鲢�������
	int merge(Encode *ec);

	void setInQueue(bool isInQueue);
	bool getIsInQueue();

	// ���ٱ���
	void eraseCode();
	// ��ӡ
	void printCode();
};