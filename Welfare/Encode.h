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
	bool codeFlag;				// 编码序列标志
	int codetype;
public:
	vector<CodeType> dvCode;
	vector<CodeType> backup;

	Encode();
	~Encode();
	// 3向量编码函数，成功，返回完成的编码个数
	int encoding(vector<int>, vector<int>, vector<int>);
	// 4向量编码函数，成功，返回编码个数
	int encoding(vector<int>, vector<int>, vector<int>, vector<int>);
	// 去重
	int de_weight();
	// 组选函数
	int groupChoose();
	// 组选转直选
	int grouptodirect();
	// 编码排序,返回编码个数
	int ordering();
	// 杀码，返回杀码个数
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);
	// 筛选和值
	int siftPlus(int min, int max);

	// 钓叟选码
	int dsSelect(char *dsSequence);
	
	// 获得组码类型
	int getCodeType();
	// 设置组码类型
	int setCodeType(int ct);
	// 销毁编码
	void eraseCode();
	// 打印
	void printCode();
};