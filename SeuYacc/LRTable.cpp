#include"Declaration.h"

extern set<LRState, stateSET> stateTable;//����״̬
set<GOTO, gotoSET> gotoTable;//����goto
extern vector<string> pdnLeft;//���ս��
extern vector<string> tokenVector;//�ս��
vector<vector<string>> AnalyTable;//LR������
extern string startExplus;//S'
void InitTable()
{
	for (auto iteral = tokenVector.begin(); iteral != tokenVector.end(); ++iteral)
	{
		vector<string> temp;
		temp.push_back((*iteral));
		AnalyTable.push_back(temp);
	}
	vector<string> temp;
	temp.push_back("$");
	AnalyTable.push_back(temp);
	for (auto iteral = pdnLeft.begin(); iteral != pdnLeft.end(); ++iteral)
	{
		vector<string> temp;
		temp.push_back((*iteral));
		AnalyTable.push_back(temp);
	}
}

void SetTable()
{
	for (auto iteral = AnalyTable.begin(); iteral != AnalyTable.end(); ++iteral)
	{
		for (auto iter = gotoTable.begin(); iter != gotoTable.end(); ++iter)
		{
			if (!(*iteral).front().compare((*iter).mid))//�ƽ���goto��Ϊ�˼򵥶��� "s"
			{
				(*iteral)[(*iter).left.stateCount] = to_string((*iter).right.stateCount);
			}
		}
		
	}
	for (auto iter = stateTable.begin(); iter != stateTable.end(); ++iter)//����״̬
	{
		for (auto iteral = (*iter).item.begin(); iteral != (*iter).item.end(); ++iteral)//������
		{
			if ((*iteral).point == (*iteral).pdn.second.size())//���λ�������
			{
				for (auto itera = AnalyTable.begin(); itera != AnalyTable.end(); ++itera)//������ͷ
				{
					for (auto ite = (*iteral).predictSymbol.begin(); ite != (*iteral).predictSymbol.end(); ++ite)//����Ԥ���
					{
						if (!(*itera).front().compare((*ite)))//��ͷ==Ԥ���
						{
							if ((*iteral).pdn.first.compare(startExplus))//chan'shen
								(*itera)[(*iter).stateCount] = to_string((*iteral).pdn.second.size());
							else
								(*itera)[(*iter).stateCount] = "accept";
						}

					}
				}
			}
		}
	}
}