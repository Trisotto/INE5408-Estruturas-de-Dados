// Copyright [2016] <Felipe Longarai Trisotto (15103032) e William Magagnin Kair (15200624)>

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>


namespace structures {

class Client {
 private:
 	int spend_;
 	int products_;
 	int start_time_;
 	int end_time_;
 	bool for_product_;
 	bool pay_check_;


 	void create_products(){
        spend_ = 0;
 		products_ = std::rand()%99 + 2;
 		for (int i = 0; i < products_; ++i)
 		{
			spend_ = spend_ + (std::rand()%90 + 1);
 		}

 	}
 	void set_pay_check(){
 		int i = std::rand()%100;

 		if (i < 20){
 			pay_check_ = true;

 		} else {
 			pay_check_ = false;
 		}
 	}
 	void type(){
 		int i = std::rand()%100;

 		if (i >= 50){
 			for_product_ = true;

 		} else {
 			for_product_ = false;
 		}
 	}

 public:
 	Client(int start_time) {

 		start_time_ = start_time;
 		create_products();
 		type();
 		set_pay_check();

 	}
    Client(){
    }

    int end_time(){
 		return end_time_;
 	}
 	void end_time(int time){
 		end_time_ = time;
 	}
 	int spend(){
 		return spend_;
 	}
 	bool for_product(){
 		return for_product_;
 	}
 	int products(){
 		return products_;
 	}
 	bool pay_check(){
 		return pay_check_;
 	}
    int start_time(){
        return start_time_;
    }



};

} // namespace structures


#endif
