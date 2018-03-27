#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;

long int totalMemory()
{
	ifstream f;
	f.open("/proc/meminfo");
	string buff;
	long int val;
	f >> buff;
	f >> val;
	f.close();
	return val;
}

long int memAvail()
{
	ifstream f;
	f.open("/proc/meminfo");
	string buff;
	for(int i=0;i<7;i++)
		f >> buff;
	long int val;
	f >> val;
	f.close();
	return val;
}

long int memUsed()
{
	return totalMemory() - memAvail();
}

int main()
{
	long int tot = totalMemory(); // use as class variable
	long int avail = memAvail();
	long int used = tot - avail;
	cout<<memAvail()<< " kB available of "<<totalMemory()<<"kb"<<endl;
	printf("%.2f percent used\n", (float(used)/tot)*100);

}
