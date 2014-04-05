#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

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
	// ��������,���ر������
	int ordering();
	// ɱ�룬����ɱ�����
	int killCode(vector<int>,vector<int>,vector<int>,vector<Gossip>);
	// ɸѡ��ֵ
	int siftPlus(int min, int max);

	// ���ٱ���
	void eraseCode();
	// ��ӡ
	void printCode();
};