#include"Declaration.h"

vector<string> functionVector;//��������
vector<string> pdnLeft;//���ս��
vector<string> tokenVector;//�ս��
string startExp;//��ʼ����
uniProduction uni_production;//���в���ʽ
int parsingFile(const string& fileName) 
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
			//vector<string> expRight;//����ʽ�Ҳ�
			Production production;//һ������ʽ
			production.first = temp;
			pdnLeft.push_back(temp);
			in >> temp;
			if (temp != ":")
			{
				cout << "ERROR: No \":\"!" << endl;
				return -1;
			}
			//in >> temp;

			do
			{
				in >> temp;
				while (temp != "|" && temp != ";")
				{
					production.second.push_back(temp);
					//cout << temp << endl;
					in >> temp;
				}
				uni_production.push_back(production);
				production.second.clear();
			} while (temp != ";");
			in >> temp;
		}
	}
	if (temp == "%%")/*-----------------part3------------------------*/
	{
		while (!in.eof())
		{
			getline(in, temp);
			functionVector.push_back(temp);
		}
	}
	return 0;
}