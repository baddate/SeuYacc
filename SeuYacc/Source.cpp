#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int> ivec;
	for (int i = 0; i < 10; ++i)
		ivec.push_back(i);

	//����vectorԪ��
	//1: ���õ�����
	for (auto it = ivec.begin(); it != ivec.end(); ++it)
		cout << *it << " ";
	cout << endl;
	//2: �����±������
	for (auto i = 0; i < ivec.size(); ++i)
		cout << ivec[i] << " ";
	cout << endl;
	//3: ���÷�Χforѭ��
	for (auto i : ivec)
		cout << i << " ";
	cout << endl << endl;


	//�޸�vector�е�Ԫ�أ�ǰ��������vector������Ԫ�أ������·�ʽ�����ܸı�����Ԫ�صĸ�����
	//1: ���õ�����
	for (auto it = ivec.begin(); it != ivec.end(); ++it)
	{
		*it = *it * 2;
		cout << *it << " ";
	}
	cout << endl;
	//2: �����±������
	for (auto i = 0; i < ivec.size(); ++i)
	{
		ivec[i] = ivec[i] * 2;
		cout << ivec[i] << " ";
	}
	cout << endl;
	//3: ���÷�Χforѭ��
	for (auto& i : ivec)//ע��˴�������
	{
		i = i * 2;
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
