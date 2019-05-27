#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <set>
#include <map>
#include <stack>

using namespace std;



typedef pair<string, vector<string>> Production;//һ������ʽ��һ������
typedef vector<Production> uniProduction;//���в���ʽ��һ������
typedef map<string, set<string>> FirstMap;//���ս��������first��
typedef	struct LRItem {
	Production pdn;
	vector<string> predictSymbol;
	int point;
};
 

typedef struct LRState{
	set<LRItem> item;
	int stateCount; 
};

typedef struct GOTO {
	LRState left;
	LRState right;
	string mid;
};

string startExplus = "startExplus";//S'
string startExp;//��ʼ����
vector<string> tokenVector;//�ս��
FirstMap firstMap;//���м�����ķ���first��
uniProduction uni_production;//���в���ʽ
vector<string> functionVector;//��������
int Count = 0;//��״̬��
set<LRState> stateTable;//����״̬
set<GOTO> gotoTable;//����goto
vector<string> pdnLeft;//���ս��
vector<vector<string>> AnalyTable;//LR������

