#include "webserver.cpp"
#include <iostream>
#include <queue>
#include <memory>
#include <algorithm>

using namespace std;

///main load balancer class.
struct load_balancer{
///reqdy queue contains request objects that has already passed received time and are ready to assign to any available webserver
///rqeust queue holds the requests that are not ready but received
	queue<shared_ptr<request>>request_queue,ready_queue;
///server holds a vector of webserver object
	vector<webserver>server;
///current time stamp
	int32_t time;
///load balancer automatically halts at this time
	int32_t total_run_time;

	int request_count;
///default constructor, generates a list of webservers=server_count, 
///generates a list of requests = request_count 
///runs the load balancer from t=0 to t=running_time
///request are randomly generated where at most 5 times amount as to web server are ready at time 0
	load_balancer(int server_count, int request_count, int running_time): time(0), total_run_time(running_time),request_count(request_count){
		for(int i=0;i<server_count;i++)server.push_back(webserver(i));
		for(int i=0;i<min(5*server_count, request_count);i++)
			request_queue.push(make_shared<request>(request::gen_req(0,0)));
		cout<<"request started in queue "<<request_queue.size()<<endl;
	}

///runs an iteration, move things from request queue to ready queue. move things from ready queue to web server, increment time
	void run(){
		while(request_queue.size()>0&&request_queue.front()->time_arrival<=time)
			ready_queue.push(request_queue.front()),request_queue.pop();
		for(auto&sv:server)if(sv.is_free(time))if(ready_queue.size())sv.assign_request(time, ready_queue.front()),ready_queue.pop();
		//cout<<"time: "<<++time<<endl;
		time++;
	}
///starts running the load balancer until reach time limit
	void start(){
		while(time<total_run_time){
			if(time==10)for(int i=min(5*((int)server.size()), request_count);i<request_count;i++)request_queue.push(make_shared<request>(request::gen_req(i, i+2)));
			run();
		}
		cout<<"request remaining in queue: "<<request_queue.size()<<endl;
		//add some more requests at certain time
	}

};

int main(){
	load_balancer lb(5,30,1000);
	lb.start();
}