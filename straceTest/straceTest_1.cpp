#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

int main()
{
	ifstream in("test.txt");
	if(!in.is_open())
	{
		cout << "open test.txt failed"<<endl;
		exit(1);
	}
	char buf[256];
	while(!in.eof())
	{
		in.getline(buf,100);
		cout << buf<<endl;
	}
	return 0;
}
