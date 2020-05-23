#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:// they return refrences of the private members
  Processor& Cpu();                   // TODO: See src/system.cpp 
  std::vector<Process>& Processes();  // TODO: See src/system.cpp vector of processes
  float MemoryUtilization();          // TODO: See src/system.cpp functions to return memorutilatic
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp kernel of operating system
  std::string OperatingSystem();      // TODO: See src/system.cpp name of the os 

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};// keep pricate
  std::vector<Process> processes_ = {};
};

#endif