#include"Declaration.h"

extern int parsingFile(const string& fileName);
extern void mapFirst();
extern void GenLRTable();
extern void InitTable();
extern void SetTable();
extern void genFile();
int main()
{
	parsingFile("test.y");
	mapFirst();
	GenLRTable();
	InitTable();
	SetTable();
	genFile();
	return 0;
}
