#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;



typedef pair<string, vector<string>> Production;//一个产生式做一个类型
typedef vector<Production> uniProduction;//所有产生式做一个类型
typedef map<string, unordered_set<string>> FirstMap;//非终结符和它的first集
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

string startExplus = "startExplus";//S'
string startExp;//开始符号
vector<string> tokenVector;//终结符
FirstMap firstMap;//所有计算出的符号first集
uniProduction uni_production;//所有产生式
vector<string> functionVector;//第三部分
int Count = 0;//计状态数
unordered_set<LRState> stateTable;//所有状态
unordered_set<GOTO> gotoTable;//所有goto
vector<string> pdnLeft;//非终结符
vector<vector<string>> AnalyTable;//LR分析表