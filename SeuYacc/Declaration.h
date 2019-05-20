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
vector<string> tokenVector;
FirstMap firstMap;
uniProduction uni_production;
vector<string> functionVector;
int Count = 0;
unordered_set<LRState> stateTable;
unordered_set<GOTO> gotoTable;
vector<string> pdnLeft;
unordered_set<LRState> lalrTable;