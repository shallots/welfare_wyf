#include "stdafx.h"
#include "GossipFreq.h"


string GossipFreq::dict[][10] = {
		   {"00","02","03","04","05","07","08","09","-1","-1"},
		   {"11","12","13","14","16","17","18","19","-1","-1"},
		   {"22","02","12","23","25","27","28","-1","-1","-1"},
		   {"33","03","13","23","36","37","38","-1","-1","-1"},
		   {"44","04","14","45","46","49","-1","-1","-1","-1"},
		   {"55","05","25","45","57","59","-1","-1","-1","-1"},
		   {"66","16","36","46","68","69","-1","-1","-1","-1"},
		   {"77","07","17","27","37","57","78","-1","-1","-1"},
		   {"88","08","18","28","38","68","78","-1","-1","-1"},
		   {"99","09","19","49","59","69","-1","-1","-1","-1"},
	};
	
int GossipFreq::count[] = {8,8,7,7,6,6,6,7,7,6};

GossipFreq::GossipFreq(char *arr, int length)
{
	input = string(arr);
}


vector<GossipType>* GossipFreq::genGossipFreqCode()
{
	vector<GossipType>* vec = new vector<GossipType>();
	if(input.length() < 1)
	{
		return vec;
	}
	
	int tmpNum[10] = {0};
	int len = input.length();
	for(int i=0; i<len; i++){
		int index = input[i] - '0';
		if(index < 0 || index > 9)
		{
			continue;
		}
		tmpNum[index]++;
	}
	for(int i=0; i<10; i++){
		if(tmpNum[i] == 0)
		{
			continue;
		}
		
		for(int j=0; j<count[i]; j++)
		{
			bool flag = true;
			for(vector<GossipType>::iterator it=vec->begin(); it!=vec->end(); it++)
			{
				GossipType tt = *it;
				if(tt.gossip.compare(dict[i][j])==0)
				{
					tt.freq += tmpNum[i];
					flag = false;
					break; 
				}
			}
			if(flag)
			{
				GossipType gsp;
				gsp.freq = tmpNum[i];
				gsp.gossip = dict[i][j];
				if(gsp.gossip[0] == gsp.gossip[1]){
					gsp.isPair = true;
				}else{
					gsp.isPair = false;
				}
				vec->push_back(gsp);
			}
		}
	}
	return vec;
}

string GossipFreq::getInput()
{
	return input;

}