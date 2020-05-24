#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
//following this refrence 
	//https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
 std::vector<std::string> value = LinuxParser::CpuUtilization();

  float user = std::stof(value[LinuxParser::kUser_]);
  float nice = std::stof(value[LinuxParser::kNice_]);
  float system = std::stof(value[LinuxParser::kSystem_]);
  float idle = std::stof(value[LinuxParser::kIdle_]);
  float iowait = std::stof(value[LinuxParser::kIOwait_]);
  float irq = std::stof(value[LinuxParser::kIRQ_]);
  float softirq = std::stof(value[LinuxParser::kSoftIRQ_]);
  float steal = std::stof(value[LinuxParser::kSteal_]);
  float Total_CPU_time_since_boot =
      user + nice + system + idle + iowait + irq + softirq + steal;
  float ideal_time=idle+iowait;
  cpu =(Total_CPU_time_since_boot-ideal_time)/(Total_CPU_time_since_boot);
  return cpu;
 }