#include"Declaration.h"

set<GOTO, gotoSET> gotoTable;//所有goto
bool StateCompare(LRState state);
bool PredictCompare(vector<string> v1, vector<string> v2);
bool itemscmp(set<LRItem, itemSET> items1, set<LRItem, itemSET> items2);
bool ItemCompare(LRItem item1, LRItem item2);
bool judgeToken(vector<string>& str, string val);
extern uniProduction uni_production;//所有产生式
extern vector<string> tokenVector;//终结符
set<LRState, stateSET> stateTable;//所有状态
extern vector<string> pdnLeft;//非终结符
int Counts = 0;//计状态数
string startExplus = "startExplus";//S'
extern FirstMap firstMap;//所有计算出的符号first集
extern string startExp;//开始符号
LRState StateFind(LRState state);
int genCount()
{
	return Counts++;
}

void Closure(LRState& state)
{
	//cout << "32" << endl;
	int initSize;
	do
	{	
		initSize = state.item.size();
		//cout << initSize << " ";
		for (auto iteral = state.item.begin(); iteral != state.item.end(); ++iteral)
		{
			if ((*iteral).point != (*iteral).pdn.second.size() && !judgeToken(tokenVector, (*iteral).pdn.second[(*iteral).point]))
			{
				for (auto temp = uni_production.begin(); temp != uni_production.end(); ++temp)
				{
					if (!(*iteral).pdn.second[(*iteral).point].compare((*temp).first))
					{
						LRItem test;
						for (auto tmp = firstMap[(*iteral).pdn.second[(*iteral).point]].begin();
							tmp != firstMap[(*iteral).pdn.second[(*iteral).point]].end(); ++tmp)
						{
							test.predictSymbol.push_back((*tmp));
						}
						test.point = 0;
						test.pdn = (*temp);
						//state.item.insert(test);
						cout << state.item.insert(test).second << "  $   ";
					}
				}
				
			}
		}
	} while (state.item.size()!=initSize);

}

LRState GOTOLR(LRState state, string temp)
{
	//cout << "22" << endl;
	LRState Next;
	Next.stateCount = genCount();
	for (auto iteral = state.item.begin(); iteral != state.item.end(); ++iteral)
	{
		if (iteral->pdn.second.size() != iteral->point && !iteral->pdn.second[iteral->point].compare(temp))
		{
			LRItem tmp;
			tmp.pdn = (*iteral).pdn;
			tmp.point = (*iteral).point + 1;
			tmp.predictSymbol = (*iteral).predictSymbol;
			Next.item.insert(tmp);
		}	
	}
	Closure(Next);

	return Next;
}

void GenLRTable()
{
	//cout << "12" << endl;
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
		//cout << initSize << " ";
		for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
		{
			for (auto it1 = pdnLeft.begin(); it1 != pdnLeft.end(); ++it1)//非终结符
			{
				LRState tem = GOTOLR((*iteral), (*it1));
				if (tem.item.size() != 0)
				{
					if (!StateCompare(tem))
					{
						GOTO got;
						got.left = (*iteral);
						got.mid = (*it1);
						got.right = tem;
						gotoTable.insert(got);
						stateTable.insert(tem);
					}
					else
					{
						GOTO got;
						got.left = (*iteral);
						got.mid = (*it1);
						got.right = StateFind(tem);
						gotoTable.insert(got);
					}
				}
			}
			for (auto it2 = tokenVector.begin(); it2 != tokenVector.end(); ++it2)//终结符
			{
				LRState tem = GOTOLR((*iteral), (*it2));
				if (tem.item.size() != 0)
				{
					LRState tem = GOTOLR((*iteral), (*it2));
					if (tem.item.size() != 0)
					{
						if (!StateCompare(tem))
						{
							GOTO got;
							got.left = (*iteral);
							got.mid = (*it2);
							got.right = tem;
							gotoTable.insert(got);
							stateTable.insert(tem);
						}
						else
						{
							GOTO got;
							got.left = (*iteral);
							got.mid = (*it2);
							got.right = StateFind(tem);
							gotoTable.insert(got);
						}
					}
				}
			}
		}
	} while (stateTable.size() != initSize);
	
}

bool StateCompare(LRState state)
{
	for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
	{
		if (itemscmp(state.item, (*iteral).item))
			return true;		
	}
	return false;
}

LRState StateFind(LRState state)
{
	for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
	{
		if (itemscmp(state.item, (*iteral).item))
			return (*iteral);
	}
}

bool whethercontain(string& str, vector<string>& v1)
{
	for (auto iteral = v1.begin(); iteral != v1.end(); ++iteral)
	{
		if (!str.compare(*iteral))
			return true;
	}
	return false;
}
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