#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <map>

using namespace std;



typedef pair<string, vector<string>> Production;//һ������ʽ
typedef vector<Production> uniProduction;//���в���ʽ
typedef map<string, unordered_set<string>> FirstMap;
typedef	struct LRItem {
	Production pdn;
	vector<string> predictSymbol;
	int point;
};
 

typedef struct LRState{
	unordered_set<LRItem> item;
	int stateCount; 
};

typedef struct GOTO {
	LRState left;
	LRState right;
	string mid;
};

string startExplus = "startExplus";
string startExp;
vector<string> tokenVector;//�ս��
FirstMap firstMap;
uniProduction uni_production;
vector<string> functionVector;
int Count = 0;
unordered_set<LRState> stateTable;//����״̬
unordered_set<GOTO> gotoTable;//����goto
vector<string> pdnLeft;//���ս��
unordered_set<LRState> lalrTable;
vector<vector<string>> AnalyTable;//LR������