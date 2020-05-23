
#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hours, minutes;
    string x,y,z,value;
    minutes =seconds/60;
    hours =minutes/60;
    long format_seconds=int(seconds%60);
    minutes=int(minutes%60);
    if(hours>=10){
     x =std::to_string(hours);
	}
	else{
     x ="0"+std::to_string(hours);

	}
    if(minutes>=10){
     y =std::to_string(minutes);
	}
	else{
		     y ="0"+std::to_string(minutes);
	}
	    if(format_seconds>=10){
     z =std::to_string(format_seconds);
	}
	else{
		     z ="0"+std::to_string(format_seconds);

	}
	value = x+":"+y+":"+z;
 	return value; }