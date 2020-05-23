#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stof;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int Process_id):pid_(Process_id),
  user(LinuxParser::User(Process_id)),
  command(LinuxParser::Command(Process_id)),
  ram(LinuxParser::Ram(Process_id)),
  uptime(LinuxParser::UpTime(Process_id)){}
  int Pid();                               // using linux_parser
  std::string User();                      // using linux_parser
  std::string Command();                   // using linux_parser
  float CpuUtilization();                  // TODO: See src/proce
  std::string Ram();                       // using linux_parser
  long int UpTime();                       // using linux_parser
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  std::string user;
  std::string command;
  float cpu_utilization;
  std::string ram;
  long int uptime;
};

#endif

/*
each process has some information 
it has id 
user that intiate it
command that intiated it
its own cpu ituliation
memorty ultization
its own uptime
we define a sort function to sort 
the process according to the most active
Process Data

Linux stores data about individual processes in files
 within subdirectories
 of the /proc directory. Each subdirectory is 
 named for that
  particular process's identifier number.
   The data that this project 
  requires exists in those files.

PID
The process identifier (PID) is accessible from the /proc directory. 
Typically, all of the subdirectories of /proc that have integral 
names correspond to processes. Each integral name corresponds to a 
process ID.

`ls /proc`
Parsing directory names with C++ is tricky, so we have provided in the project'
 starter code a pre-implemented function to capture the PIDs.

User
Each process has an associated user identifier (UID),
 corresponding to the process owner. This means that determining 
 the process owner requires two steps:

Find the UID associated with the process
Find the user corresponding to that UID
The UID for a process is stored in /proc/[PID]/status.

`cat /proc/[PID]/status`
The man page for proc contains a "/proc/[pid]/status" 
section that describes this file.

For the purposes of this project, you simply need 
to capture the first integer on the "Uid:" line.

Username
/etc/passwd contains the information
 necessary to match the UID to a username.

`cat /etc/passwd`
Processor Utilization
Linux stores the CPU utilization of a
 process in the /proc/[PID]/stat file.

`cat /proc/[PID]/stat`
Much like the calculation of aggregate processor utilization,
 half the battle is extracting the relevant data from the file, 
 and the other half of the battle is figuring out how to use those numbers
  to calculate processor utilization.

The "/proc/[pid]/stat" section of the proc man page describes 
the meaning of the values in this file. This StackOverflow answer 
explains how to use this data to calculate the process's utilization.

As with the calculation of aggregate processor utilization, 
it is sufficient for this project to calculate the average utilization 
of each process since the process launched. If you would like to extend 
your project to calculate a more current measurement of process utilization,
 we encourage you to do that!

Memory Utilization
Linux stores memory utilization for the process in /proc/[pid]/status.


In order to facilitate display, consider converting the memory utilization into megabytes.

Up Time
Linux stores the process up time in /proc/[pid]/stat.

`cat /proc/[pid]/stat`
The "/proc/[pid]/stat" section of the proc man page describes each of the values in this file.

(22) starttime %llu

The time the process started after system boot. In kernels before Linux 2.6, this value was expressed in jiffies. Since Linux 2.6, the value is expressed in clock ticks (divide by sysconf(_SC_CLK_TCK)).

Note that the "starttime" value in this file is measured in "clock ticks". In order to convert from "clock ticks" to seconds, you must:

#include <unistd.h>
divide the "clock ticks" value by sysconf(_SC_CLK_TCK)
Once you have converted the time value to seconds, you can use the Format::Time() function from the project starter code to display the seconds in a "HH:MM:SS" format.

Command
Linux stores the command used to launch the function in the /proc/[pid]/cmdline file.

`cat /proc/[pid]/cmdline`
*/