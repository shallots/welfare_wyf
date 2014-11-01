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
	bool codeFlag;				// 是否编码序列标志
	bool isInQueue;				// 是否被添加到队列
	bool isMerge;
	int codetype;
public:
	vector<CodeType> dvCode;
	vector<CodeType> backup;
	// 杀大和，杀两头，全大全小，全奇全偶
	vector<CodeType> recycleBin;

	// 杀码队列

	Encode();
	~Encode();

	// 3向量编码函数，成功，返回完成的编码个数
	int encodingThree(vector<int>, vector<int>, vector<int>);
	int encodingTwo(vector<int>, vector<int>, vector<int>);
	int encoding(vector<int>, vector<int>, vector<int>,bool);
	// 1向量编码，成功，返回完成的编码个数
	int encoding(vector<int>);
	// 1向量编码，bool为真，则进行编码，bool为假，则只改变频度
	int encoding(vector<int>,bool);
	// 4向量编码函数，成功，返回编码个数
	int encoding(vector<int>, vector<int>, vector<int>, vector<int>,bool);
	// 去重
	int de_weight();
	// 组选函数
	int groupChoose();
	// 组选转直选
	int grouptodirect();
	// 编码排序,返回编码个数
	int ordering();
	int orderForRecycleBin();
	// 按频度排序
	int orderByFreq();

	// 和值尾改变频度
	int AdjustFreqByMantissa(vector<int>);

	// 杀码，返回杀码个数
	int killCode(vector<int>,vector<int>,vector<int>,vector<int>,vector<Gossip>);
	// 筛选和值
	int siftPlus(int min, int max);

	// 定三码
	int tcSelect(char *tcSelect);

	// 钓叟选码
	int dsSelect(char *dsSequence);
	// 杀大和
	int killBig(int big=20);

	// 获得组码类型
	int getCodeType();
	// 设置组码类型
	int setCodeType(int ct);

	bool getIsMerge();
	void setIsMerge(bool isMerge);

	// 归并多组编码
	int merge(Encode *ec);

	void setInQueue(bool isInQueue);
	bool getIsInQueue();

	// 销毁编码
	void eraseCode();
	// 打印
	void printCode();
};