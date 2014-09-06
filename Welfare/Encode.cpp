#include "stdafx.h"
#include "Encode.h"
using std::sort;
Encode::Encode()
{
	codeFlag = false;
	codetype = GROUP;
}

Encode::~Encode()
{
	eraseCode();
}

/*********************************************************
*	���ƣ����������뺯��
*	���ܣ�ʹ�����������������б���
*	������
*		da,��һ������������db���ڶ�������������dc����������������
*	����:Hyw
*	����:14/06/04
*	˵��:�°�Ҫ����ѡɱ�룬���ɵ���ֱѡ������Ԥ����ʱ�����ɶ���
*********************************************************/
int Encode::encoding(vector<int> da, vector<int> db, vector<int> dc)
{
	//  ��δд�쳣����
	if(codeFlag)
	{
		return 0;
	}
	if(!(da.size() && db.size() && dc.size()))
	{
		return -1;
	}

	// ֱѡ����
	vector<int> *data[3];
	data[0] = &da;
	data[1] = &db;
	data[2] = &dc;
	int i=0;
	int k=0;
	for(i=0; i<3; i++)
	{
		for(vector<int>::iterator ita = data[i]->begin(); ita != data[i]->end(); ita++)
		{
			for(k=i+1;k<3;k++)
			{
				for(vector<int>::iterator itc = data[k]->begin(); itc != data[k]->end(); itc++)
				{
					CodeType tmp;
					tmp.codeSeq[0] = *ita;
					tmp.codeSeq[1] = *itc;
					for(int j=0;j<=9;j++){
						tmp.codeSeq[2] = j;
						int codeSum = (*ita + j + *itc);
						tmp.mantissa = codeSum % 10;
						dvCode.push_back(tmp);
					}
				}
			}
		}
	}
	de_weight();
	if(codetype == GROUP)
		groupChoose();
	codeFlag = true;
	return dvCode.size();
}

/*********************************************************
*	���ƣ����������뺯��
*	���ܣ�ʹ�����������������б���
*	������
*		da,��һ������������db���ڶ�������������dc����������������
*	����:Hyw
*	����:13/05/13
*   ע��: �°汾������������������3�룬�ʴ˺�������
*********************************************************/
/*
int Encode::encoding(vector<int> da, vector<int> db, vector<int> dc)
{
	//  ��δд�쳣����
	if(codeFlag)
	{
		return 0;
	}
	if(!(da.size() && db.size() && dc.size()))
	{
		return -1;
	}

	// ֱѡ����
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
*/

/*********************************************************
*	���ƣ����������뺯��
*	���ܣ�ʹ�������������н��б���
*	������
*		da,��һ������������db���ڶ�������������dc������������������
*		dd,��������������
*	����:Hyw
*	����:13/06/02
*********************************************************/
int Encode::encoding(vector<int> da, vector<int> db, vector<int> dc, vector<int> dd)
{
	// δд�쳣����
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

// ȡ�ñ������ֵ
inline int getMax(const vector<CodeType>::iterator va)
{
	int maxa = va->codeSeq[0]>va->codeSeq[1]?va->codeSeq[0]:va->codeSeq[1];
	maxa = maxa>va->codeSeq[2]?maxa:va->codeSeq[2];
	return maxa;
}

// ȡ�ñ�����Сֵ
inline int getMin(const vector<CodeType>::iterator va)
{
	int mina = va->codeSeq[0]>va->codeSeq[1]?va->codeSeq[1]:va->codeSeq[0];
	mina = mina>va->codeSeq[2]?va->codeSeq[2]:mina;
	return mina;
}
/***********************************************
*	���ƣ�ȥ�غ���
*	���ܣ�ֱѡ��������ȥ��
*	���ߣ�Hyw
*	���ڣ�14/04/04
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
*	���ƣ���ѡ����
*	���ܣ���ֱѡ�Ļ�����ʵ����ѡ
*	���ߣ�Hyw
*	���ڣ�13/05/13
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
�����׼2����3D�����Ӧ������С����
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
	sort(dvCode.begin(),dvCode.end(),comp);
	return 1;
}

int Encode::killCode(vector<int> plustail, vector<int> boldcode,vector<int> hdr,vector<int> decade,vector<int> unit,vector<Gossip> gossip)
{
	if(!codeFlag)
	{
		return 0;
	}
	int count = 0;

	// ɱ������
	sort(plustail.begin(),plustail.end());
	sort(boldcode.begin(),boldcode.end());
	sort(hdr.begin(),hdr.end());
	sort(decade.begin(),decade.end());
	sort(unit.begin(),unit.end());

	//  ��βֵɱ��,�㷨�д��Ż�
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

		// �����ж��ɹ����ܽ�����Զ���ɱ��
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
		if(flag || (!plustail.size() && !boldcode.size() && !gossip.size() && !hdr.size() &&decade.size()))
		{
			for(vector<int>::iterator it=decade.begin(); it!=decade.end(); it++)
			{
				if(itcode->codeSeq[1] == *it)
				{
					flag = true;
					break;
				}else{
					flag = false;
				}
			}
		}
		if(flag || (!plustail.size() && !boldcode.size() && !gossip.size() && !hdr.size() && !decade.size() &&unit.size()))
		{
			for(vector<int>::iterator it=unit.begin(); it!=unit.end(); it++)
			{
				if(itcode->codeSeq[2] == *it)
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

/********************************
* ���ַ�������ת��Ϊ��������
*
*********************************/
vector<int*> parseSeq(char *dsSeqx){
	vector<int*> seq;
	int *ptr = new int[10];
	for(int m=0;m<10;m++){
		*(ptr+m) = -1;
	}
	int j=0,i=0;
	for( i=0; dsSeqx[i] != '\0';i++){
		if(dsSeqx[i]>'9' || dsSeqx[i] < '0')
		{
			if(ptr[0]!=-1){
				seq.push_back(ptr);
				j=0;
				ptr = new int[10];
				for(int m=0;m<10;m++){
					*(ptr+m) = -1;
				}
			}
			continue;
		}
		ptr[j] = dsSeqx[i] - '0';
		j++;
	}
	if(ptr[0] != -1){
		seq.push_back(ptr);
	}else
		delete []ptr;
	return seq;	
}


/********************************
* ��Ԥ�������������������������ڸ���������ʱ��
* ����true�����򷵻�false
*********************************/
bool isInSeq(vector<CodeType>::iterator it, int* ptr){
	int i=0;
	int flag = 0;
	while(ptr[i] != -1 && i<10){
		if(ptr[i] == it->codeSeq[0])
			flag++;
		if(ptr[i] == it->codeSeq[1])
			flag++;
		if(ptr[i] == it->codeSeq[2])
			flag++;
		i++;
	}
	if(flag >1)
		return true;
	else
		return false;
}

bool isInSeq3(vector<CodeType>::iterator it, int* ptr){
	int i=0;
	int flag = 0;
	while(ptr[i] != -1 && i<10){
		if(ptr[i] == it->codeSeq[0])
			flag++;
		if(ptr[i] == it->codeSeq[1])
			flag++;
		if(ptr[i] == it->codeSeq[2])
			flag++;
		i++;
	}
	if(flag >2)
		return true;
	else
		return false;
}
/********************************
* �����뺯��
*********************************/
int Encode::tcSelect(char *tcSeq){
	if(strlen(tcSeq)<1){
		return 0;
	}
	int count = 0;
	vector<int*> seq = parseSeq(tcSeq);
	for(vector<CodeType>::iterator it= dvCode.begin(); it!=dvCode.end();){
		bool flag = false;
		for(vector<int*>::iterator itd = seq.begin(); itd!=seq.end(); itd++){
			int* ptr = *itd;
			if(isInSeq3(it,ptr)){
				flag = true;
				break;
			}
		}

		if(flag){
			it++;	
		}else{
			it = dvCode.erase(it);
			count++;
		}
	}
	delete []tcSeq;
	for(vector<int*>::iterator itd = seq.begin(); itd!=seq.end(); itd++ ){
		delete [] (*itd);
	}
	seq.clear();
	return count;
}

/********************************
* ����ѡ�뺯��
*********************************/
int Encode::dsSelect(char *dsxSeq){
	if(strlen(dsxSeq)<1){
		return 0;
	}
	int count = 0;
	vector<int*> seq = parseSeq(dsxSeq);
	for(vector<CodeType>::iterator it= dvCode.begin(); it!=dvCode.end();){
		bool flag = false;
		for(vector<int*>::iterator itd = seq.begin(); itd!=seq.end(); itd++){
			int* ptr = *itd;
			if(isInSeq(it,ptr)){
				flag = true;
				break;
			}
		}

		if(flag){
			it++;	
		}else{
			it = dvCode.erase(it);
			count++;
		}
	}
	delete []dsxSeq;
	for(vector<int*>::iterator itd = seq.begin(); itd!=seq.end(); itd++ ){
		delete [] (*itd);
	}
	seq.clear();
	return count;
}

void copydvCode(vector<CodeType> ct, vector<CodeType> &dv){
	dv.clear();
	for(vector<CodeType>::iterator it=ct.begin(); it!=ct.end(); it++){
		dv.push_back(*it);
	}
}

void genThree(vector<CodeType>::iterator it,vector<CodeType>& list){
	//list.push_back(*it);
	int code[2];
	if(it->codeSeq[0] == it->codeSeq[1]){
		if(it->codeSeq[0] == it->codeSeq[2]){
			return;
		}
		code[0] = it->codeSeq[0];
		code[1] = it->codeSeq[2];
	}else{
		if(it->codeSeq[0] == it->codeSeq[2]){
			code[0] = it->codeSeq[0];
			code[1] = it->codeSeq[1];
		}else{
			code[0] = it->codeSeq[1];
			code[1] = it->codeSeq[0];
		}
	}
	for(int i=0; i<3; i++){
		CodeType tc;
		tc.codeSeq[i] = code[1];
		tc.codeSeq[(i+1)%3] = code[0];
		tc.codeSeq[(i+2)%3] = code[0];
		tc.mantissa = it->mantissa;
		list.push_back(tc);
	}
}

void genSix(vector<CodeType>::iterator it,vector<CodeType>& list){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(j==i)
				continue;
			for(int k=0; k<3; k++){
				if(k==i || k==j)
					continue;
				CodeType ct;
				ct.codeSeq[0] = it->codeSeq[i];
				ct.codeSeq[1] = it->codeSeq[j];
				ct.codeSeq[2] = it->codeSeq[k];
				ct.mantissa = it->mantissa;
				list.push_back(ct);
			}
		}
	}
}
int Encode::grouptodirect(){
	if(codetype == DIRECT)
		return dvCode.size();
	vector<CodeType> dCode;

	for(vector<CodeType>::iterator it=dvCode.begin(); it!=dvCode.end(); it++){
		if(it->codeSeq[0] == it->codeSeq[1] || it->codeSeq[1]==it->codeSeq[2]
			||it->codeSeq[0] == it->codeSeq[2]){
			genThree(it,dCode);
		}else{
			genSix(it,dCode);
		}
	}
	copydvCode(dCode,dvCode);

	dCode.clear();
	codetype = DIRECT;
	return dvCode.size();
}


int Encode::killBig(int big){
	int count = 0;
	for(vector<CodeType>::iterator it=dvCode.begin(); it!=dvCode.end();){
		if((it->codeSeq[0] + it->codeSeq[1] + it->codeSeq[2])>20){
			it = dvCode.erase(it);
			count++;
		}
		it++;
	}
	return count;
}

int Encode::getCodeType(){
	return codetype;
}

int Encode::setCodeType(int ct){
	if(ct == 1 || ct == 0)
	{
		codetype = ct;
		return codetype;
	}else{
		return -1;
	}
}
void Encode::eraseCode()
{
	if(!codeFlag)
		return;
	dvCode.clear();
	codeFlag = false;
	codetype = GROUP;
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
