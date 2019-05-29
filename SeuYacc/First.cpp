#include"Declaration.h"

extern uniProduction uni_production;//���в���ʽ
FirstMap firstMap;//���м�����ķ���first��
extern vector<string> tokenVector;//�ս��
bool judgeToken(vector<string>& str, string val)
{
	//cout << "c" << endl;
	for (auto iteral = str.begin(); iteral != str.end(); ++iteral)
	{
		if (!val.compare(*iteral))
			return true;
	}
	return false;
}

void calcFirst(string symbol, set<string> &temp)
{
	//cout << "d" << endl;
	for (auto iteral = uni_production.begin(); iteral != uni_production.end(); ++iteral)
	{
		if (!iteral->first.compare(symbol))
		{
			if (judgeToken(tokenVector, (*iteral).second.front()))//�ս��
			{
				//cout << "E" << endl;
				temp.insert((*iteral).second.front());
			}

			else//���ս��
			{
				//cout << "F" << endl;
				temp.insert((*iteral).second.front());
				if (temp.find((*iteral).second.front())!= temp.end())
					break;
				calcFirst((*iteral).second.front(), temp);
			}
		}
	}
}

void mapFirst()
{
	cout << "mapFirst1" << endl;
	for (auto iteral = uni_production.begin(); iteral != uni_production.end(); ++iteral)
	{
		set<string> temp;
		calcFirst((*iteral).first, temp);
		firstMap.insert(pair<string, set<string>> ((*iteral).first, temp));
	}
}

