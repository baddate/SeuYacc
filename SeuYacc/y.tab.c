#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stack.h>
#include <string.h>

#include <stdio.h>

void yyerror()
{
}
ifstream lex_out;
lex_out.open("filename", ios::in);
string temp;
vector<string> Lex_OUT;
do {
lex_out >> temp;
Lex_OUT.push_back(temp);
} while (!lex_out.eof());
stack<int> stateStack;
stack<string> symbolStack;
stateStack.push(0)
int cnt = 0;
do {
for (auto iteral = AnalyTable.begin(); iteral != AnalyTable.end(); ++iteral)
{
if (!(*iteral).front().compare(Lex_OUT[cnt]))
{
if (!(*iteral)[stateStack.top() + 1].compare("accept"))
	break;
if (!(*iteral)[stateStack.top() + 1].front().compare())
{
	string s = (*iteral)[stateStack.top() + 1];
	int i = atoi(s.erase(0, 1).c_str());
	stateStack.push(i);
	symbolStack.push(Lex_OUT[cnt]);
}
else if((*iteral)[stateStack.top() + 1].empty())
{
	cout << "ERROR: syntax errror" << endl;
}
else
{
	string s,s1 = (*iteral)[stateStack.top() + 1];
	int offset = s.find_first_of("#", 0);
	int i = atoi(s.erase(offset, s.size()-offset).c_str());
	while (i != 0)
	{
		symbolStack.pop();
		stateStack.pop();
		i--;
	}
	string j = s1.erase(0, offset);
	int t = symbolStack.top(); << endl;
	for (auto itera = AnalyTable.begin(); itera != AnalyTable.end(); ++itera)
	{
		if (!(*itera).front().compare(j))
		{
			string temp = (*itera)[t];
			i = atoi(temp.erase(0, 1).c_str());
			stateStack.push(i);
			cout << j << endl;
		}
	}
}
	}
}
cnt++;
} while (cnt != Lex_OUT.size());
