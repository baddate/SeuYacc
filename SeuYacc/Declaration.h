#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <map>

using namespace std;



typedef pair<string, vector<string>> Production;//一个产生式
typedef vector<Production> uniProduction;//所有产生式
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
vector<string> tokenVector;//终结符
FirstMap firstMap;
uniProduction uni_production;
vector<string> functionVector;
int Count = 0;
unordered_set<LRState> stateTable;//所有状态
unordered_set<GOTO> gotoTable;//所有goto
vector<string> pdnLeft;//非终结符
unordered_set<LRState> lalrTable;
vector<vector<string>> AnalyTable;//LR分析表