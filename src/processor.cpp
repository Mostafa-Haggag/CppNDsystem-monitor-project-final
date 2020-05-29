#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
//following this refrence 
//
	//https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
 std::vector<std::string> value = LinuxParser::CpuUtilization();

  double user = std::stof(value[LinuxParser::kUser_]);
  double nice = std::stof(value[LinuxParser::kNice_]);
  double system = std::stof(value[LinuxParser::kSystem_]);
  double idle = std::stof(value[LinuxParser::kIdle_]);
  double iowait = std::stof(value[LinuxParser::kIOwait_]);
  double irq = std::stof(value[LinuxParser::kIRQ_]);
  double softirq = std::stof(value[LinuxParser::kSoftIRQ_]);
  double steal = std::stof(value[LinuxParser::kSteal_]);
  double Total_CPU_time_since_boot =
      user + nice + system + idle + iowait + irq + softirq + steal;
  double ideal_time=idle+iowait;
  cpu =(Total_CPU_time_since_boot-ideal_time)/(Total_CPU_time_since_boot);
  return cpu;
 }