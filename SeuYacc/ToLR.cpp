#include"Declaration.h"
extern bool judgeToken(vector<string>& str, string val);
extern vector<string> tokenVector;
extern uniProduction uni_production;
extern FirstMap firstMap;
extern int genCount();
void Closure(LRState& state)
{
	int initSize;
	do
	{	
		initSize = state.item.size();
		for (auto iteral = state.item.begin(); iteral != state.item.end(); ++iteral)
		{
			if (!judgeToken(tokenVector, (*iteral).pdn.second[(*iteral).point]))
			{
				for (auto temp = uni_production.begin(); temp != uni_production.end(); ++temp)
				{
					if (!(*iteral).pdn.second[(*iteral).point].compare((*temp).first))
					{
						LRItem test;
						for (auto tmp = firstMap[(*iteral).pdn.second[(*iteral).point + 1]].begin();
							tmp != firstMap[(*iteral).pdn.second[(*iteral).point + 1]].end(); ++tmp)
						{
							test.predictSymbol.push_back((*tmp));
						}
						test.point = 0;
						test.pdn = (*temp);
						state.item.insert(test);
					}
				}
				
			}
		}
	} while (state.item.size()!=initSize);
}

LRState GOTOLR(LRState& state, string temp)
{
	LRState Next;
	Next.stateCount = genCount();
	for (auto iteral = state.item.begin(); iteral != state.item.end(); ++iteral)
	{
		LRItem tmp;
		tmp.pdn = (*iteral).pdn;
		tmp.point = (*iteral).point + 1;
		tmp.predictSymbol = (*iteral).predictSymbol;
		Next.item.insert(tmp);
	}
	Closure(Next);
	return Next;
}
void GenLRTable()
{
	int initSize;
	LRItem item;
	item.point = 0;
	item.predictSymbol.push_back("$");
	item.pdn.first = startExplus;
	item.pdn.second.push_back(startExp);
	LRState temp;
	temp.stateCount = 0;
	temp.item.insert(item);
	Closure(temp);
	stateTable.insert(temp);
	do
	{
		initSize = stateTable.size();
		for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
		{
			for (auto it1 = pdnLeft.begin(); it1 != pdnLeft.end(); ++it1)
			{
				LRState tem = GOTOLR((*iteral), (*it1));
				if (tem.item.size() != 0 && StateCompare(tem)) stateTable.insert(tem);
			}
			for (auto it2 = tokenVector.begin(); it2 != tokenVector.end(); ++it2)
			{
				LRState tem = GOTOLR((*iteral), (*it2));
				if (tem.item.size() != 0 && StateCompare(tem)) stateTable.insert(tem);
			}
		}
	} while (stateTable.size() != initSize);
	
}

bool StateCompare(LRState state)
{
	for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
	{
		if (itemscmp(state.item, (*iteral).item)) return true;
	}
	return false;
}
bool itemscmp(unordered_set<LRItem>& items1, unordered_set<LRItem>& items2) 
{
	int f = 0;
	if (items1.size() != items2.size()) return false;
	for (auto iteral = items1.begin(); iteral != items1.end(); ++iteral) {
		for (auto itera = items2.begin(); itera != items2.end(); ++itera) {
			if (ItemCompare((*itera), (*iteral))) {
				f = 1;
				break;
			}
		}
		if (f == 0) return false;
		else f = 0;
	}
	return true;
}
bool ItemCompare(LRItem item1, LRItem item2)
{
	if (item1.point != item2.point) return false;
	if (item1.pdn.first.compare(item2.pdn.first.compare)) return false;
	if (!PredictCompare(item1.predictSymbol, item2.predictSymbol)) return false;
	if (!PredictCompare(item1.pdn.second, item2.pdn.second)) return false;
	return true;
}
bool PredictCompare(vector<string> v1, vector<string> v2)
{
	if (v1.size() != v2.size()) return false;
	for (auto iteral = v1.begin(); iteral != v1.end(); ++iteral)
	{
		if (!whethercontain((*iteral), v2)) return false;
	}
	return true;
}
bool whethercontain(string& str, vector<string>& v1) 
{
	for (auto iteral = v1.begin(); iteral != v1.end(); ++iteral)
	{
		if (!str.compare(*iteral)) return true;
	}
	return false;
}