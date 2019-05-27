#include"Declaration.h"

void genFile()
{
	//���� y.tab.h�ļ�
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
		out << "#define  " << p << "    " << p<< endl;
	}
	out << "#endif" << endl;
	out.close();

	//���� y.tab.c�ļ�
	out.open("y.tab.c", ios::out);

	if (!out)
	{
		cout << "ERROR: can't open file y.tab.c !" << endl;
	}
	out << "#include <stdio.h>" << endl;
	out << "#include <stdlib.h>" << endl;
	out << "#include <assert.h>" << endl;


}
