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



/*

*/
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

/*
bool PredictCompare(vector<string> v1, vector<string> v2);
bool ItemCompare(LRItem item1, LRItem item2);
bool itemscmp(set<LRItem, itemSET> items1, set<LRItem, itemSET> items2);
bool whethercontain(string& str, vector<string>& v1);
*/

typedef struct LRState{
	set<LRItem, itemSET> item;
	int stateCount; 
};

struct stateSET
{
	bool PredictCompare(vector<string> v1, vector<string> v2)
	{
		if (v1.size() != v2.size())
			return false;
		for (auto iteral = v1.begin(); iteral != v1.end(); ++iteral)
		{
			if (!whethercontain((*iteral), v2))
				return false;
		}
		return true;
	}

	bool ItemCompare(LRItem item1, LRItem item2)
	{
		if (item1.point != item2.point)
			return false;
		if (item1.pdn.first.compare(item2.pdn.first))
			return false;
		if (!PredictCompare(item1.predictSymbol, item2.predictSymbol))
			return false;
		if (!PredictCompare(item1.pdn.second, item2.pdn.second))
			return false;
		return true;
	}

	bool whethercontain(string & str, vector<string> & v1)
	{
		for (auto iteral = v1.begin(); iteral != v1.end(); ++iteral)
		{
			if (!str.compare(*iteral))
				return true;
		}
		return false;
	}

	bool itemscmp(set<LRItem, itemSET> items1, set<LRItem, itemSET> items2)
	{
		int f = 0;
		if (items1.size() != items2.size()) return false;
		for (auto iteral = items1.begin(); iteral != items1.end(); ++iteral)
		{
			for (auto itera = items2.begin(); itera != items2.end(); ++itera)
			{
				if (ItemCompare((*itera), (*iteral)))
				{
					f = 1;
					break;
				}
			}
			if (f == 0)
				return false;
			else f = 0;
		}
		return true;
	}
	bool operator()(const LRState left, const LRState right)
	{
		return itemscmp(left.item, right.item);
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
		if (left.mid == right.mid)
		{
			if (left.left.stateCount != right.left.stateCount)
				return false;
			if (left.right.stateCount != right.right.stateCount)
				return false;
			return true;
		}
		else
			return false;
	}
};




