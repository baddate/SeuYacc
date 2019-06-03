#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>

using namespace std;

typedef pair<string, vector<string>> Production;//一个产生式做一个类型
typedef vector<Production> uniProduction;//所有产生式做一个类型
typedef map<string, set<string>> FirstMap;//非终结符和它的first集

typedef	struct LRItem {
	Production pdn;
	vector<string> predictSymbol;
	int point;
};
 
struct itemSET
{
	bool operator()(const LRItem& left, const LRItem& right)
	{
		if (left.pdn.first < right.pdn.first)
			return true;
		else
			return false;
	}
};


typedef struct LRState{
	set<LRItem, itemSET> item;
	int stateCount; 
};

struct stateSET
{
	bool operator()(const LRState& left, const LRState& right)
	{
		if (left.stateCount < right.stateCount)
			return true;
		else
			return false;
	}
};

typedef struct GOTO {
	LRState left;
	LRState right;
	string mid;
};

struct gotoSET
{
	bool operator()(const GOTO& left, const GOTO& right)
	{
		if (left.left.stateCount < right.left.stateCount)
			return true;
		else
			return false;
	}
};










