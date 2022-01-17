#include <iostream>
#include <boost/bind/bind.hpp>

#include "UDP_client.h"

UDP_client::UDP_client():
    resolver_(ioc_), remote_endpoint_(udp::v4(), 55514), socket_(ioc_){
}

void UDP_client::send(){
    socket_.open(udp::v4());
    boost::array<char, 3> send_buf = {{'a', 'b', 'c'}};
    //auto res = resolver_.resolve("localhost", "55514", ec);
    udp::endpoint destination(
        boost::asio::ip::address::from_string("127.0.0.1"), 12345);
    std::cout << "UDP_client::send" << std::endl;
    socket_.async_send_to(
              boost::asio::buffer(send_buf), destination,
              boost::bind(&UDP_client::handler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    ioc_.run();
};

void UDP_client::handler(
  const boost::system::error_code& error, // Result of operation.
  std::size_t bytes_transferred           // Number of bytes sent.
        ){
    std::cout << "UDP_client handler" << '\n';
    if (!error){
      std::cout << "UDP_client " << bytes_transferred << std::endl;
      //start_receive();

    }else{
    std::string str_err = "ErrorSend: " + error.message();
    std::cout << str_err << std::endl;
    }
};
