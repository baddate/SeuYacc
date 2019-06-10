#include"Declaration.h"
extern vector<string> tokenVector;//终结符
extern vector<string> pdnLeft;//非终结符
extern vector<string> functionVector;//第三部分
extern vector<vector<string>> AnalyTable;//LR分析表

void genFile()
{
	//生成 y.tab.h文件
	ofstream out;
	out.open("y.tab.h", ios::out);
	out << "#ifndef Y_TAB_H" << endl;
	out << "#define Y_TAB_H" << endl;

	for (const auto& p : tokenVector)
	{
		out << "#define  " << p << "    " <<"\""<< p <<"\""<< endl;
	}
	for (const auto& p : pdnLeft)
	{
		out << "#define  " << p << "    " << "\"" << p << "\"" << endl;
	}
	out << "#endif" << endl;
	out.close();

	//生成 y.tab.c文件
	out.open("y.tab.cpp", ios::out);

	if (!out)
	{
		cout << "ERROR: can't open file y.tab.c !" << endl;
	}
	out << "#include <stdio.h>" << endl;
	out << "#include <stdlib.h>" << endl;
	out << "#include <assert.h>" << endl;
	out << "#include <stack>" << endl;
	out << "#include <string>" << endl;
	out << "#include <fstream>" << endl;
	out << "#include <iostream>" << endl;
	out << "#include <vector>" << endl;
	out << "using namespace std;" << endl;
	for (const auto& s : functionVector) {
		out << s << endl;
	}
	out << "int main() " << endl;
	out << "{" << endl;
	//读lex输出
	out << "ifstream lex_out;" << endl;
	out << "lex_out.open(\"filename\", ios::in);" << endl;
	out << "string temp;" << endl;
	out << "vector<string> Lex_OUT;" << endl;
	out << "do {" << endl;
	out << "lex_out >> temp;" << endl;
	out << "Lex_OUT.push_back(temp);" << endl;
	out << "} while (!lex_out.eof());" << endl;

	out << "stack<int> stateStack;" << endl;//状态栈
	out << "stack<string> symbolStack;" << endl;//符号栈
	out << "stateStack.push(0);" << endl;//初始化
	out << "int cnt = 0;" << endl;

	out << "do {" << endl;
	out << "for (auto iteral = AnalyTable.begin(); iteral != AnalyTable.end(); ++iteral)" << endl;
	out << "{" << endl;
	out << "if (!(*iteral).front().compare(Lex_OUT[cnt]))" << endl;
	out << "{" << endl;
	out << "if (!(*iteral)[stateStack.top() + 1].compare(\"accept\"))" << endl;
		out << "	break;" << endl;
		out << "if ((*iteral)[stateStack.top() + 1].front() !=\'s\')" << endl;
		out << "{" << endl;
		out << "	string s = (*iteral)[stateStack.top() + 1];" << endl;
		out << "	int i = atoi(s.erase(0, 1).c_str());" << endl;
		out << "	stateStack.push(i);" << endl;
		out << "	symbolStack.push(Lex_OUT[cnt]);" << endl;
		out << "}" << endl;
		out << "else if((*iteral)[stateStack.top() + 1].empty())" << endl;
		out << "{" << endl;
		out << "	cout << \"ERROR: syntax errror\" << endl;" << endl;
		out << "}" << endl;
		out << "else" << endl;
		out << "{" << endl;
		out << "	string s,s1 = (*iteral)[stateStack.top() + 1];" << endl;
		out << "	int offset = s.find_first_of(\"#\", 0);" << endl;
		out << "	int i = atoi(s.erase(offset, s.size()-offset).c_str());" << endl;
		out << "	while (i != 0)" << endl;
		out << "	{" << endl;
		out << "		symbolStack.pop();" << endl;
		out << "		stateStack.pop();" << endl;
		out << "		i--;" << endl;
		out << "	}" << endl;
		out << "	string j = s1.erase(0, offset);" << endl;//产生式的左边字符串
		out << "	int t = stateStack.top();" << endl;//栈顶
		out << "	for (auto itera = AnalyTable.begin(); itera != AnalyTable.end(); ++itera)" << endl;
		out << "	{" << endl;
		out << "		if (!(*itera).front().compare(j))" << endl;
		out << "		{" << endl;
		out << "			string temp = (*itera)[t];" << endl;
		out << "			i = atoi(temp.erase(0, 1).c_str());" << endl;
		out << "			stateStack.push(i);" << endl;
		out << "			cout << j << endl;" << endl;//没有右边
		out << "		}" << endl;
		out << "	}" << endl;
		out << "}" << endl;
		out << "	}" << endl;
		out << "}" << endl;
		out << "cnt++;" << endl;
		out << "} while (cnt != Lex_OUT.size());" << endl;
		out << "return 0;" << endl;
		out << "}" << endl;
}
