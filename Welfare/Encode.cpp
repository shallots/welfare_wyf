#include "stdafx.h"
#include "Encode.h"
using std::sort;
Encode::Encode()
{
	codeFlag = false;
}

Encode::~Encode()
{
	eraseCode();
}
/*********************************************************
*	名称：三向量编码函数
*	功能：使用三组整数向量进行编码
*	参数：
*		da,第一组整数向量；db，第二组整数向量；dc，第三组整数向量
*	作者:Hyw
*	日期:13/05/13
*********************************************************/
int Encode::encoding(vector<int> da, vector<int> db, vector<int> dc)
{
	//  暂未写异常处理
	if(codeFlag)
	{
		return 0;
	}
	if(!(da.size() && db.size() && dc.size()))
	{
		return -1;
	}

	// 直选编码
	vector<int> *data[3];
	data[0] = &da;
	data[1] = &db;
	data[2] = &dc;
	int i=0;
	int j=0;
	int k=0;
	for(i=0; i<3; i++)
	{
		for(vector<int>::iterator ita = data[i]->begin(); ita != data[i]->end(); ita++)
		{
			for(j=0;j<3;j++)
			{
				if(i==j)
					continue;
				for(vector<int>::iterator itb = data[j]->begin(); itb != data[j]->end(); itb++)
				{
					for(k=0;k<3;k++)
					{
						if(k==j||k==i)
							continue;
						for(vector<int>::iterator itc = data[k]->begin(); itc != data[k]->end(); itc++)
						{
							CodeType tmp;
							tmp.codeSeq[0] = *ita;
							tmp.codeSeq[1] = *itb;
							tmp.codeSeq[2] = *itc;
							int codeSum = (*ita + *itb + *itc);
							tmp.mantissa = codeSum % 10;
							dvCode.push_back(tmp);
						}
					}
				}
			}
		}
	}
	de_weight();
	//groupChoose();
	codeFlag = true;
	return dvCode.size();
}

/*********************************************************
*	名称：四向量编码函数
*	功能：使用四组整数序列进行编码
*	参数：
*		da,第一组整数向量；db，第二组整数向量；dc，第三组整数向量，
*		dd,第四组整数向量
*	作者:Hyw
*	日期:13/06/02
*********************************************************/
int Encode::encoding(vector<int> da, vector<int> db, vector<int> dc, vector<int> dd)
{
	// 未写异常处理
	if(codeFlag)
	{
		return 0;
	}
	if(!(da.size() && db.size() && dc.size()))
	{
		return -1;
	}
	vector<int> *vec[4];
	vec[0] = &da;
	vec[1] = &db;
	vec[2] = &dc;
	vec[3] = &dd;

	int startIndex = 0;
	for(int i=0; i<4; i++)
	{
		int m = (i + 1) % 4;
		int n = (i + 2) % 4;

		codeFlag = FALSE;
		encoding(*vec[i],*vec[m],*vec[n]);
	}
	return dvCode.size();
}

// 取得编码最大值
inline int getMax(const vector<CodeType>::iterator va)
{
	int maxa = va->codeSeq[0]>va->codeSeq[1]?va->codeSeq[0]:va->codeSeq[1];
	maxa = maxa>va->codeSeq[2]?maxa:va->codeSeq[2];
	return maxa;
}

// 取得编码最小值
inline int getMin(const vector<CodeType>::iterator va)
{
	int mina = va->codeSeq[0]>va->codeSeq[1]?va->codeSeq[1]:va->codeSeq[0];
	mina = mina>va->codeSeq[2]?va->codeSeq[2]:mina;
	return mina;
}
/***********************************************
*	名称：去重函数
*	功能：直选辅助函数去重
*	作者：Hyw
*	日期：14/04/04
************************************************/
int Encode::de_weight()
{
	if(dvCode.size()<2)
		return dvCode.size();
	for(vector<CodeType>::iterator it = dvCode.begin(); it!=dvCode.end(); it++)
	{
		for(vector<CodeType>::iterator ita = it+1; ita!=dvCode.end();)
		{
			if(it->codeSeq[0] == ita->codeSeq[0] && 
				it->codeSeq[1] == ita->codeSeq[1] && it->codeSeq[2] == ita->codeSeq[2])
			{
				ita = dvCode.erase(ita);
				continue;
			}
			ita++;
		}
	}
	return dvCode.size();
}
/***********************************************
*	名称：组选函数
*	功能：在直选的基础上实现组选
*	作者：Hyw
*	日期：13/05/13
************************************************/
int Encode::groupChoose()
{
	if(dvCode.size()<2)
		return dvCode.size();
	for(vector<CodeType>::iterator it = dvCode.begin(); it != dvCode.end();it++)
	{
		for(vector<CodeType>::iterator ita =it+1; ita != dvCode.end();)
		{
			if(it->mantissa == ita->mantissa &&
				getMax(it) == getMax(ita) && getMin(it) == getMin(ita))
			{
				ita = dvCode.erase(ita);
				continue;
			}
			ita ++;
		}
	}
	return dvCode.size();
}

bool comp(const CodeType &a,const CodeType &b)
{
	if(a.mantissa == b.mantissa)
	{
		if (a.codeSeq[0] == b.codeSeq[0])
		{
			if (a.codeSeq[1] == b.codeSeq[1])
			{
				return a.codeSeq[2] < b.codeSeq[2];
			}else
				return a.codeSeq[1] < b.codeSeq[1];
		}else
			return a.codeSeq[0] < b.codeSeq[0];
	}
	else
		return a.mantissa < b.mantissa;
}
/**********************************
排序标准2：按3D编码对应整数大小排序
***********************************/
bool comp2(const CodeType &a, const CodeType &b)
{
	if(a.codeSeq[0] == b.codeSeq[0])
	{
		if (a.codeSeq[1] == b.codeSeq[1])
		{
			return a.codeSeq[2] < b.codeSeq[2];
		}else
			return a.codeSeq[1] < b.codeSeq[1];
	}
	else
		return a.codeSeq[0] < b.codeSeq[0];
}

int Encode::ordering()
{
	if(!codeFlag)
		return 0;
	sort(dvCode.begin(),dvCode.end(),comp2);
	return 1;
}

int Encode::killCode(vector<int> plustail, vector<int> boldcode,vector<int> hdr,vector<Gossip> gossip)
{
	if(!codeFlag)
	{
		return 0;
	}
	int count = 0;

	// 杀码有序化
	sort(plustail.begin(),plustail.end());
	sort(boldcode.begin(),boldcode.end());
	sort(hdr.begin(),hdr.end());

	//  和尾值杀码,算法有待优化
	for(vector<CodeType>::iterator itcode = dvCode.begin(); itcode != dvCode.end(); )
	{
		bool flag = false;
		
		for(vector<int>::iterator it = plustail.begin(); it != plustail.end(); it++)
		{
			if(itcode->mantissa == *it)
			{
				flag = true;
				break;
			}else if((int)itcode->mantissa < *it)
				break;
		}

		if(flag || (!plustail.size() && boldcode.size())) 
		{
			for(vector<int>::iterator it = boldcode.begin(); it != boldcode.end(); it++)
			{
				if(itcode->codeSeq[0] == *it ||
					itcode->codeSeq[1] == *it||
					itcode->codeSeq[2] == *it)
				{
					flag = true;
					break;
				}else{
					flag = false;
				}
			}
		}

		// 胆码判定成功才能进入八卦二码杀码
		if(flag || (!plustail.size() && !boldcode.size() && gossip.size()))
		{
			for(vector<Gossip>::iterator it=gossip.begin(); it != gossip.end(); it++)
			{
				if((itcode->codeSeq[0] == it->x ||
					itcode->codeSeq[1] == it->x ||
					itcode->codeSeq[2] == it->x) &&
				   (itcode->codeSeq[0] == it->y ||
					itcode->codeSeq[1] == it->y ||
					itcode->codeSeq[2] == it->y))
				{
					flag = true;
					break;
				}
				else{
					flag = false;
				}
			}
		}

		if(flag || (!plustail.size() && !boldcode.size() && !gossip.size() &&hdr.size()))
		{
			for(vector<int>::iterator it=hdr.begin(); it!=hdr.end(); it++)
			{
				if(itcode->codeSeq[0] == *it)
				{
					flag = true;
					break;
				}else{
					flag = false;
				}
			}
		}
		
		if(!flag)
		{
			itcode = dvCode.erase(itcode);
			count ++;
		}else{
			itcode ++;
		}
	}

	return count;
}

void Encode::eraseCode()
{
	if(!codeFlag)
		return;
	dvCode.clear();
	codeFlag = false;
}


void Encode::printCode()
{
	if(!codeFlag)
		return;
	for(vector<CodeType>::iterator it = dvCode.begin(); it != dvCode.end(); it++)
	{
		std::cout << it->codeSeq[0] << it->codeSeq[1] << it->codeSeq[2] << "," << it->mantissa
			<< std::endl;
	}
}