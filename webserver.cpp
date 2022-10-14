#include "request.cpp"
#include <memory>
#include <iostream>

///webserver can process a request at each time stamp
struct webserver{
///this represents the time where this server receives the last request to be processed
	int32_t last_request_time;
///the pointer to the most recent request. if this is reassigned at the same time the previous one will be aborted
	std::shared_ptr<request> current_request;
///IP of the webserver. this is going to be displayed at the log for each processed request
	int32_t IP;

	webserver(int32_t ip):last_request_time(-1),IP(ip){

	}
///returns if the server is free
	bool is_free(int32_t time){
		if(current_request==nullptr)return 1;
		return time>=last_request_time+current_request->processing_duration;
	}
///assings a request to this webserver at this time. flushes log if previous request is processed
	void assign_request(int32_t time, std::shared_ptr<request> req){
		if(time>last_request_time&&current_request!=nullptr){
			current_request->print_log();
		}
		current_request=req;
		current_request->IP_out=IP;
		current_request->time_processed=time;
	}
///flushes log for previous webserver
	~webserver(){
		if(current_request!=nullptr){
			current_request->print_log();
		}
	}
};