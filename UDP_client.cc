#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>

#include "UDP_client.h"

UDP_client::UDP_client():
    socket_(ioc_), num_messages_(0){
}

void UDP_client::run(){
    socket_.open(udp::v4());
    while(num_messages_ < 30){
     send_message();
    }
};

void UDP_client::send_message(){
    //std::cout << "UDP_client::send" << std::endl;
    std::string message = "cat";
    udp::endpoint destination(
            boost::asio::ip::address::from_string("127.0.0.1"), 55514);
    socket_.send_to(boost::asio::buffer(message), destination);
    sleep(1);
    num_messages_ ++;

}

