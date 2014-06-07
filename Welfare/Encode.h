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
}CodeType;

typedef struct
{
	int x;
	int y;
}Gossip;

class Encode
{
private:
	bool codeFlag;				// �������б�־
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
	// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);
	// ɸѡ��ֵ
	int siftPlus(int min, int max);

	// ����ѡ��
	int dsSelect(char *dsSequence);
	
	// �����������
	int getCodeType();
	// ������������
	int setCodeType(int ct);
	// ���ٱ���
	void eraseCode();
	// ��ӡ
	void printCode();
};