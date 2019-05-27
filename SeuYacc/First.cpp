#include"Declaration.h"
extern vector<string> tokenVector;
extern FirstMap firstMap;
bool judgeToken(vector<string>& str, string val);
extern uniProduction uni_production;
void calcFirst(string symbol, set<string> &temp)
{
	
	for (auto iteral = uni_production.begin(); iteral != uni_production.end(); ++iteral)
	{
		if (judgeToken(tokenVector, (*iteral).second.front()))//ÖÕ½á·û
		{
			temp.insert((*iteral).second.front());
		}
		else//·ÇÖÕ½á·û
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

bool judgeToken(vector<string> &str,string val)
{
	for (auto iteral = str.begin(); iteral != str.end(); ++iteral)
	{
		if (!val.compare(*iteral))
			return true;
	}
	return false;
}