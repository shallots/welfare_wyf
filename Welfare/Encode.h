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
	int frequency;			// Ƶ��
	int span;				// ���
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
	vector<CodeType> highFreqCode;
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

	// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);
	
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

	// ������
	void getSupplementarySet(vector<CodeType> competeSet);

	void setInQueue(bool isInQueue);
	bool getIsInQueue();

	int copyCode(vector<CodeType> src, vector<CodeType> &dst);

	// ��Ƶɱ��,����ʣ������
	int killCodeByHFC();

	// ���ٱ���
	void eraseCode();
	// ��ӡ
	void printCode();
};