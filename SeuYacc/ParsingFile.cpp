#include"Declaration.h"

extern vector<string> functionVector;
//extern string startExp;

int parsingFile(const string& fileName, vector<string> &tokenVector, uniProduction &uni_production) 
{
	ifstream in;
	in.open(fileName, ios::in);
	string temp;//file buffer
	if (!in)
	{
		cout << "ERROR: No such a file or can't open it!" << endl;
		return -1;
	}
	in >> temp;
	while (temp != "%left" && temp != "%start" && temp != "%%") 
	{
		if (temp == "%token")
			in >> temp;
		tokenVector.push_back(temp);
		in >> temp;
	}
	while (temp != "%start" && temp != "%%")
	{
		if (temp == "%left")
			in >> temp;
		tokenVector.push_back(temp);
		in >> temp;
	}
//	while (temp != "%%")
//	{
		if (temp == "%start")
		{
			in >> temp;
			startExp = temp;
			in >> temp;
		}
//	}
	if (temp == "%%")/*-----------------part2------------------------*/
	{
		in >> temp;
		while (temp != "%%")
		{
			vector<string> expRight;//产生式右部
			Production production;//一个产生式
			production.first = temp;
			pdnLeft.push_back(temp);
			in >> temp;
			if (temp != ":")
			{
				cout << "ERROR: No \":\"!" << endl;
				return -1;
			}
			in >> temp;
			production.second = expRight;
			while (temp != ";")
			{
				while (temp != "|")
				{
					production.second.push_back(temp);
					in >> temp;
				}
				uni_production.push_back(production);
				production.second = expRight;
				in >> temp;
			}
			in >> temp;
		}
	}
	if (temp == "%%")/*-----------------part3------------------------*/
	{
		while (!in.eof())
		{
			getline(in, temp);
			while (temp.empty())
			{
				getline(in, temp);
			}
			functionVector.push_back(temp);
		}
	}
}