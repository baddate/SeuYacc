#include"Declaration.h"
extern vector<vector<string>> AnalyTable;//LR分析表
extern vector<GOTO> gotoTable;//所有goto
extern int parsingFile(const string& fileName);
extern void mapFirst();
extern void GenLRTable();
extern void InitTable();
extern void SetTable();
extern void genFile();
extern vector<LRState> stateTable;//所有状态
extern uniProduction uni_production;//所有产生式
int main()
{
	parsingFile("yacc.y");
	mapFirst();
	GenLRTable();
	InitTable();
	SetTable();
	//genFile();
	ofstream analy;
	analy.open("AnalyTable.txt", ios::out);
	cout << endl;
	///
	analy << AnalyTable.front().size() << endl;
	analy << AnalyTable.size() << endl;
	for (auto iteral = AnalyTable.begin(); iteral != AnalyTable.end(); ++iteral)
	{
		for (auto itera = iteral->begin(); itera != iteral->end(); ++itera)
		{
			analy << *itera << endl;
		}
	}
	///
	cout << stateTable.begin()->item.size()<<"  |  "<< AnalyTable.front().size() << endl;
	cout << stateTable.size() << "  sssssss  "<< endl;
	for (auto iteral = gotoTable.begin(); iteral != gotoTable.end(); ++iteral)
	{
		cout << iteral->left.stateCount << " " << iteral->mid << " " << iteral->right.stateCount;
		cout << endl;
	}


	ifstream lex_out;
	lex_out.open("test.l", ios::in);
	string temp;
	vector<string> Lex_OUT;
	do {
		lex_out >> temp;
		cout << temp << " ";
		Lex_OUT.push_back(temp);
	} while (!lex_out.eof());
	cout << endl;
	Lex_OUT.push_back("$");
	stack<int> stateStack;
	stack<string> symbolStack;
	stateStack.push(0);
	int cnt = 0;
	do {
		for (auto iteral = AnalyTable.begin(); iteral != AnalyTable.end(); ++iteral)
		{
			//cout << "!" << endl;
			if (!(*iteral).front().compare(Lex_OUT[cnt]))
			{
				if (!(*iteral)[stateStack.top() + 1].compare("accept"))
				{
					cout << "Successful!!!!!!!!!!!!!!!!" << endl;
					break;
				}
					
				if (!(*iteral)[stateStack.top() + 1].find("s"))
				{
					string s = (*iteral)[stateStack.top() + 1];
					int i = atoi(s.erase(0, 1).c_str());
					stateStack.push(i);
					symbolStack.push(Lex_OUT[cnt]);
				}
				else if ((*iteral)[stateStack.top() + 1].empty())
				{
					cout << "ERROR: syntax errror" << endl;
				}
				else
				{
					//cout << "test" << endl;
					string s1 = (*iteral)[stateStack.top() + 1];
					string s = s1;
					int offset = s.find_first_of("#", 0);
					int i = atoi(s.erase(offset, s.size() - offset).c_str());
					while (i != 0)
					{
						symbolStack.pop();
						stateStack.pop();
						i--;
					}
					string j = s1.erase(0, offset+1);
					int t = stateStack.top();
					for (auto itera = AnalyTable.begin(); itera != AnalyTable.end(); ++itera)
					{
						if (!(*itera).front().compare(j))
						{
							string temp = (*itera)[t+1];
							i = atoi(temp.erase(0, 1).c_str());
							stateStack.push(i);
							symbolStack.push(j);
							cout << j << endl;
						}
					}
					cnt--;
				}
				break;
			}
			
		}
		cnt++;
	} while (cnt != Lex_OUT.size());
	return 0;
}
