#include"Declaration.h"

extern bool itemscmp(unordered_set<LRItem> items1, unordered_set<LRItem> items2);
bool compareState(LRState state1, LRState state2)
{
	if (itemscmp(state2.item, state1.item)) 
		return true;
	return false;
}

bool mergeSame()
{
	for (auto iteral = stateTable.begin(); iteral != stateTable.end(); ++iteral)
	{
		for (auto iter = iteral++; iter != stateTable.end(); ++iter)
		{
			if (compareState((*iteral), (*iter)))
			{
				lalrTable.insert((*iter));
				continue;
			}
			return false;
		}
	}
	return true;
}

void GenLALRTable()
{

}