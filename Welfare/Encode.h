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

	Encode();
	~Encode();

	// 3�������뺯�����ɹ���������ɵı������
	int encoding(vector<int>, vector<int>, vector<int>);
	// 4�������뺯�����ɹ������ر������
	int encoding(vector<int>, vector<int>, vector<int>, vector<int>);
	// ȥ��
	int de_weight();
	// ��ѡ����
	int groupChoose();
	// ��ѡתֱѡ
	int grouptodirect();
	// ��������,���ر������
	int ordering();

	// ��Ƶ������
	int orderByFreq();
	// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);
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