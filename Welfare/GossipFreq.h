#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct{
	bool isPair;
	int freq;
	string gossip;
}GossipType;

class GossipFreq
{
public:
	GossipFreq(char *arr, int length);
	vector<GossipType>* genGossipFreqCode();
	string getInput();
private:
	static string dict[10][10];
	static int count[10];
	string input;
};

