#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version>>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
	float MemTotal,MemFree;
	float total_used_memory=0;
	string line,temp_1,temp_2;
	std::ifstream stream(kProcDirectory + kMeminfoFilename);
  	if (stream.is_open()) {
	    while (std::getline(stream, line)) {
	     std::istringstream linestream(line);
	     linestream >> temp_1 >> temp_2;
	     if(temp_1=="MemTotal:")
	     {
					MemTotal=stof(temp_2);
	     }
	     else if (temp_1=="MemFree:")
	     {
					MemFree=stof(temp_2);
	     }
	}
		total_used_memory   = MemTotal-MemFree;
	}
	return total_used_memory/MemTotal; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
		string line,temp_1,temp_2;
		std::istringstream linestream;
		long int  process=0;
		std::ifstream stream(kProcDirectory + kUptimeFilename);
				  	if (stream.is_open()) {
				  				  std::getline(stream, line);
				    			  linestream.str(line);
				 				  linestream >> process ;
					}
/*
open cat /proc/uptime
chose any of the 2 values and return it 

*/
	return process; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> data;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  std::istringstream linestream;
  std::getline(stream, line);
  linestream.str(line);
  string info;
  linestream >> info;
  for (int i = 0; i < 10; i++) {
    linestream >> info;
    data.push_back(info);
  }
  return data;
 }
/*
run command cat /proc/stat
we save the data for cpu 0
cpu  213423 3002 61305 3012989 69563 0 2488 0 0 0
*/
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
		string line,temp_1,temp_2;
    	std::istringstream linestream;
		int process=0;
		std::ifstream stream(kProcDirectory + kStatFilename);
				  	if (stream.is_open()) {
				  		while (std::getline(stream, line)) {
				  				  linestream.clear();
				  				  linestream.str(line);	
				 				  linestream >> temp_1;
				 				  if(temp_1=="processes"){
				 				  	linestream>>process;
				 				  	break;
				 				  }
						}
					}
	return process; 
/*
cat /proc/stat
we search for processes 9712

*/
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
		string line,temp_1;
        std::istringstream linestream;
		int process=0;
		std::ifstream stream(kProcDirectory + kStatFilename);
				  	if (stream.is_open()) {
				  		while (std::getline(stream, line)) {
				  				  linestream.clear();
				 				  linestream.str(line);
				 				  linestream >> temp_1 ;
				 				  if(temp_1=="procs_running"){
				 				  linestream >> process ;
				 				  	break;
				 				  }
						}
					}
/*
cat /proc/stat
we search for procs_running 
*/
	return process; }

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
		string line;
		std::ifstream stream(kProcDirectory +std::to_string(pid)+kCmdlineFilename);
		std::getline(stream, line);
		return line;

/*
we search cat /proc/pid/cmdline
we take all the  line as a string
*/		
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
string line,key,value;
int ramsize;
std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
if(filestream.is_open()){
    while (std::getline(filestream, line)) {
    				  std::istringstream linestream(line);
    	   		      while (linestream >> key >> value) {
					        if (key == "VmSize:") {
					          ramsize = std::stoi(value);
					          ramsize /= 1024;  // 1MB = 1024KB
					        }
						}
	}	
}
/*we open 
cat /proc/pid/status
search for 
VmSize:	  866252 kB
and take the value in numbers and turn it to MB

*/
	  return std::to_string(ramsize);

}
string LinuxParser::Uid(int pid) { 
		string line,temp_1,temp_2;
		std::istringstream linestream;
		std::ifstream stream(kProcDirectory +std::to_string(pid)+kStatusFilename);
			while(stream.is_open()){
  			  		linestream.clear();
    				std::getline(stream, line);
    				linestream.str(line);
              	 	linestream >> temp_1;
            if(temp_1=="Uid:"){
          	  linestream >> temp_2;
          	  break;
            }
          }
	return temp_2;
/*
take the values from 
cat /proc/pid/status
search for UID
and take it
*/
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 	
	string line,temp_1,temp_2,temp_3,user;
	string uid =LinuxParser::Uid(pid);
		std::ifstream stream(kPasswordPath);
		if (stream.is_open()) {
			while(std::getline(stream, line)){
			std::replace(line.begin(), line.end(), ':', ' ');
          	std::istringstream linestream(line);
          		while (linestream >> temp_1 >> temp_2>>temp_3){
          		if(uid==temp_3){
          			user= temp_1;
          		}
          	  }
			}
		}
		/*
			open
			cat /etc/passwd
			mafroood bet search for e user of seach process
			messagebus:x:106
			106 state the process number
			messagebus
		*/
return user;
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line,temp_1;
  long time=0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::istringstream linestream;
		if (stream.is_open()) {
		std::getline(stream, line);
		linestream.clear();
		linestream.str(line);
		for(int i=0;i<22;i++){
			 linestream>>temp_1;
		}
   		time = std::stol(temp_1) / sysconf(_SC_CLK_TCK);

   		 /*
			open 
			cat /proc/pid/stat
			search for item number 23 3lshan dh time
			divide it to get the time
   		 */
		}
	return time;
}