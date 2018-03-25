#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

using namespace std;

int start[5][2], end[5][2];
double perc[5];

void CalcForAllCpu(int numCpu)
{
	string crap;
	int tot_jiffies, work_jiffies, k;
	ifstream cpuStat, c2;
	cpuStat.open("/proc/stat");
	for(int cpu=0;cpu<numCpu;cpu++)
	{
		cpuStat >> crap;
		work_jiffies = 0;
		tot_jiffies = 0;
		for(int i=0;i<10;i++)
		{
			cpuStat >> k;
			if(i<3)
				work_jiffies+=k;
			tot_jiffies+=k;
		}
		start[cpu][0] = work_jiffies;
		start[cpu][1] = tot_jiffies;
	}
	cpuStat.close();
	usleep(1000000);
	cpuStat.open("/proc/stat");
  for(int cpu=0;cpu<5;cpu++)
  {
		cpuStat >> crap;
		work_jiffies = 0;
		tot_jiffies = 0;
    for(int i=0;i<10;i++)
    {
      cpuStat >> k;
      if(i<3)
        work_jiffies+=k;
      tot_jiffies+=k;
    }
    end[cpu][0] = work_jiffies;
    end[cpu][1] = tot_jiffies;
  }
	for(int i=0;i<5;i++)
		perc[i] = double((end[i][0] - start[i][0]))/double((end[i][1] - start[i][1]));
}

int numberOfCpus()
{
	return sysconf(_SC_NPROCESSORS_ONLN);
}

void handle_sig(int sig)
{
	cout << "\033[2J\033[1;1H";
	exit(1);
}

int main()
{
	signal(SIGINT, handle_sig);
	int numCpus = numberOfCpus();
	while(1)
	{
		CalcForAllCpu(numCpus);
		cout << "\033[2J\033[1;1H";
		cout<<"CPU Average"<<": "<<perc[0]*100<<"%"<<endl;
		for(int i=1;i<numCpus+1;i++)
			cout<<"CPU "<<i-1<<": "<<perc[i]*100<<"%"<<endl;
	}

}
