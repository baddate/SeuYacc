#include"Declaration.h"

extern uniProduction uni_production;//所有产生式
FirstMap firstMap;//所有计算出的符号first集
extern vector<string> tokenVector;//终结符
bool judgeToken(vector<string>& str, string val)
{
	for (auto iteral = str.begin(); iteral != str.end(); ++iteral)
	{
		if (!val.compare(*iteral))
			return true;
	}
	return false;
}

void calcFirst(string symbol, set<string> &temp)
{
	
	for (auto iteral = uni_production.begin(); iteral != uni_production.end(); ++iteral)
	{
		if (judgeToken(tokenVector, (*iteral).second.front()))//终结符
		{
			temp.insert((*iteral).second.front());
		}
		else//非终结符
		{
			if((*iteral).second.front().compare((*iteral).first))
				continue;
			calcFirst((*iteral).second.front(), temp);
		}
	}
}

void mapFirst()
{
	for (auto iteral = uni_production.begin(); iteral != uni_production.end(); ++iteral)
	{
		set<string> temp;
		calcFirst((*iteral).first, temp);
		firstMap.insert(pair<string, set<string>> ((*iteral).first, temp));
	}
}

