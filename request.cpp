#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <string>

///
///for holding a request object
///
struct request{
/// time request arrived at load balancer, only process it after this time
	int32_t time_arrival;
///the IP adress where this request is received and assigned to web server
	int32_t IP_in, IP_out;
///this field is used at processing time. the time the request is processed by a webserver
	int32_t time_processed=-1;
///time needed to process this request. from 1 to 10
	int32_t processing_duration;
///randomly generate a request between the time interval provided
	static request gen_req(int32_t start_interval, int32_t end_interval){
		request r;
		r.time_arrival=start_interval;
		if(end_interval>start_interval)r.time_arrival+=rand()%(end_interval-start_interval);
		r.IP_in=((rand()%256)<<24)|((rand()%256)<<16)|((rand()%256)<<8)|(rand()%256);
		r.processing_duration=1+rand()%10;
		//r.IP_out=((rand()%256)<<24)|((rand()%256)<<16)|((rand()%256)<<8)|(rand()%256);
		return r;
	}
///provides log information about the request object
	void print_log(){
		std::cout<<"request with in IP "<<print_ip(IP_in)<<" and time_arrival "<<time_arrival<<" is processed with webserver "<<print_ip(IP_out)<<" at time "<<time_processed+processing_duration<<std::endl;
	}
	std::string print_ip(int32_t ip){
		return std::to_string(ip&(255u<<24)>>24)+"."+std::to_string(ip&(255u<<16)>>16)+"."+std::to_string(ip&(255u<<8)>>8)+"."+std::to_string(ip&(255u<<0)>>0);
	}
};