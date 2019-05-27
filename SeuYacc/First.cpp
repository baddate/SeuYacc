#include"Declaration.h"

extern uniProduction uni_production;//���в���ʽ
FirstMap firstMap;//���м�����ķ���first��
extern vector<string> tokenVector;//�ս��
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
		if (judgeToken(tokenVector, (*iteral).second.front()))//�ս��
		{
			temp.insert((*iteral).second.front());
		}
		else//���ս��
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

