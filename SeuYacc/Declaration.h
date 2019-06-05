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
	bool operator () (const LRItem left, const LRItem right)
	{
		int flag = 0;
		if (left.point == right.point)
		{
			if (left.predictSymbol.size() == right.predictSymbol.size())
			{
				for (auto iteral = left.predictSymbol.begin(); iteral != left.predictSymbol.end(); ++iteral)
				{
					flag = 0;
					for (auto itera = right.predictSymbol.begin(); itera != right.predictSymbol.end(); ++itera)
					{
						if (!iteral->compare(*itera))
						{
							flag = 1;
							break;
						}

					}
					if (flag == 0)
						return false;
				}

				if (!left.pdn.first.compare(right.pdn.first))
				{
					if (left.pdn.second.size() == right.pdn.second.size())
					{
						for (auto iteral = left.pdn.second.begin(); iteral != left.pdn.second.end(); ++iteral)
						{
							flag = 0;
							for (auto itera = right.pdn.second.begin(); itera != right.pdn.second.end(); ++itera)
							{
								if (!iteral->compare(*itera))
								{
									flag = 1;
									break;
								}

							}
							if (flag == 0)
								return false;
						}
						return true;
					}
					else
						return false;

				}
				else
					return false;
			}
			else
				return false;
		
		}
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
	bool operator()(const LRState left, const LRState right)
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
	bool operator()(const GOTO left, const GOTO right)
	{
		if (left.left.stateCount < right.left.stateCount)
			return true;
		else
			return false;
	}
};










