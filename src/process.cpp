#include "process.h"
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>


// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
		string line;
		long utime;//14//12
		long stime;//15//13
		long cutime;//16//14
		long cstime;//17//15
		long starttime;//22//20
		string temp;//22//21
		bool flag =false;
		int counter = 1;
		std::istringstream linestream;
		std::ifstream stream(LinuxParser::kProcDirectory +std::to_string(pid_)+ LinuxParser::kStatFilename);
		if(stream.is_open()){
					std::getline(stream, line);
					linestream.str(line);
					while(linestream >> temp){
						switch(counter){
							case 14:utime=std::stol(temp);break;
							case 15:stime=std::stol(temp);break;
							case 16:cutime=std::stol(temp);break;
							case 17:cstime=std::stol(temp);break;
							case 22:starttime=std::stol(temp);break;
							case 23:flag=true;break;
						}
						if(flag)
							break;
						counter++;
					}
				}
		float freq=sysconf(_SC_CLK_TCK);
		float total_time = utime + stime;
		total_time = total_time + cutime + cstime;
		float elapsed_time = LinuxParser::UpTime()-starttime/freq;
		float cpu_usage =  ((total_time / freq) / elapsed_time);
		return cpu_usage;

}
// TODO: Return the command that generated this process
string Process::Command() { return command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime; }

bool Process::operator<(Process const& a) const { return cpu_utilization<a.cpu_utilization; }