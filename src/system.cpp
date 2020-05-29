#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
//tell you what you need (missing)
// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }
// TODO: Return a container composed of the system's processes (missing)
bool compare(Process A,Process B){
	return A<B;
}
vector<Process>& System::Processes() { 
	  vector<int> pids = LinuxParser::Pids();
  for (int pid : pids) {
    Process process(pid);
    processes_.emplace_back(process);
  }
    sort(processes_.begin(), processes_.end(),compare);
	return processes_;
	 }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
/*
Linux 
	stores system data withtin /proc directory, data in the project is requried in here
OS
	 data are inside /etc/os-relase
Kernel information
	it is stored at /proc/version
Memory utilization
	it is stored in /proc/meminfo file
	there are many ways to use this data to callculate the utlatication 
	link for different ways to calculate memory utilization
	https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
	htop author here. These are the calculations I make to get the numbers for the green, blue and yellow bars in the memory meter:

	Total used memory = MemTotal - MemFree
	Non cache/buffer memory (green) = Total used memory - (Buffers + Cached memory)
	Buffers (blue) = Buffers
	Cached memory (yellow) = Cached + SReclaimable - Shmem
	Swap = SwapTotal - SwapFree
	In the htop source code: linux/LinuxProcessList.c and linux/Platform.c.
	**************
Total Processes
	information exists about total number of process on the system exist in  /proc/meminfo
	**************
Running Processes
	information about the number of process on the system that are currently running exists in
	/proc/meminfo
Uptime
	infmation abbout system up time exist in /proc/uptime file
	This file contains two numbers (values in seconds): the uptime of the system (including time spent in suspend) and the amount of time spent in the idle process.
information got from
	http://man7.org/linux/man-pages/man5/proc.5.html
inside proc there are many different process
fi id li process or general infomration 

we use linux parser header and .it is not a class.
it is defined as namespace.
functions live inside a parser.
namespace with different functions.
some off the function  you need to go replace to get the project to work

What is the relationship between the system class and the parser?
3andak 2 ways to work things out here.
either fi kol function in the system betcall funciton bet5aletha fl linux parser.
aw gowa system object you intiate and do the parsing w kol sheia ykon fi update function 3lshan teged el 
local variable w bet returnoh. mn a5eer betkoon cached inside of system to make sure things go on as wanted,
faham 7aga?
you intiate constructor for system and it calls the other function in the parser. then when you call the uptime function maslan.
you do not need to go to the zift linux-parser 3lshan enta already 3andak saved parameters in your system
kol fatra bykon fi system update function.
3lshan tezbat donia  


*/