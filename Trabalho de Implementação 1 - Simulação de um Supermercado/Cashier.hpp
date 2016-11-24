// Copyright [2016] <Felipe Longarai Trisotto (15103032) e William Magagnin Kair (15200624)>

#ifndef CASHIER_HPP
#define CASHIER_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "array_queue.h"
#include "Client.hpp"

namespace structures {

class Cashier {

 private:
 	int productivity_;
 	int pay_check_time_;
 	int salary_;
    int products_;
 	int n_visits_;
 	int mtime_visits_;
 	int t_earning_;
 	int mearning_client_;
 	int end_time_;
    structures::ArrayQueue<Client> queue{20u};
    std::string id_;

 public:
    Cashier() = default;
 	Cashier(std::string _id_, int pro, int sal ) {

 		id_ = _id_;
 		productivity_ = pro;
 		if (productivity_ == 3)
 		{
 			pay_check_time_ = 60;
 		}
 		if (productivity_ == 2)
 		{
 			pay_check_time_ = 25;
 		}
 		if (productivity_ == 1)
 		{
 			pay_check_time_ = 10;
 		}
 		salary_ = sal;
 		products_ = 0;
 		n_visits_ = 0;
 		mtime_visits_ = 0;
 		t_earning_ = 0;
 		mearning_client_ = 0;
 		end_time_ = 0;

 	}
 	int size(){
 		return queue.size();
 	}
 	void add_client(Client client_){
 		Client client = client_;

 		products_ += client_.products();
        
        if (queue.empty()){
            end_time_ = client.start_time() + productivity_*client.products();
        }
        else{
            end_time_ += productivity_*client.products();
        }
 		if (client.pay_check())
 		{
 			end_time_ += pay_check_time_;
 		}
        
        
 		client.end_time(end_time_);
        queue.enqueue(client);


 	}
 	void new_visit(){

 		Client client = queue.dequeue();

 		n_visits_++;
 		t_earning_ += client.spend();
 		mearning_client_ = t_earning_/n_visits_;


 	}
 	int next_end(){
        
        if (queue.empty()){
            return -1;
        } else {
 		Client client = queue.front();
 		return client.end_time();
        }
 	}
 	bool full(){
 		return queue.full();
 	}
 	int products(){
 		return products_;
 	}
    int t_earning(){
        return t_earning_;
    }
    std::string id(){
        return id_; 
    }
    int n_visits(){
        return n_visits_;
    }
    int salary(){
        return salary_;
    }
    int productivity(){
        return productivity_;
    }


 
 	
};

} // namespace structures


#endif
