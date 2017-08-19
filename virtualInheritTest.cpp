#include<iostream>

using namespace std;
#pragma pack(8)

class CSuperBase
{
public:
	int m_value;
	void foo(){}
	virtual ~CSuperBase(){}
};

class CBase1 :virtual public CSuperBase
{
public:
	virtual ~CBase1(){}
};

class CBase2:virtual public CSuperBase
{
public:
	virtual ~CBase2(){}
};

class CDerived:public CBase1, public CBase2
{
public:
	virtual ~CDerived(){}
};

class test
{
public:
	int m_val;
};

int main()
{
	CSuperBase csBase;
	cout << "CSuperBase: " << sizeof(csBase)<<endl;
	
	cout << "int: "<< sizeof(int)<<endl;
        cout << "point" <<sizeof(CSuperBase *)<<endl;
	test t;
	cout << "Test"<<sizeof(t)<<endl;

	CBase1 cb1;
	CBase1 cb2;
	cout << "CBase1:" << sizeof(cb1)<<endl;
	cout << "CBase2:" << sizeof(cb2)<<endl;
	
	CDerived cd;
	cout << "CDerived:" << sizeof(cd)<<endl;

//	system("pause");
	return 0;
	
}
