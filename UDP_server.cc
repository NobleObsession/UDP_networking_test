#include "UDP_server.h"
#include <iostream>
#include <boost/bind/bind.hpp>

UDP_server::UDP_server(): socket_(ioc_), remote_endpoint_(udp::v4(), 55514){};

void UDP_server::start_receive(){
     boost::asio::ip::udp::endpoint client;
     boost::array<char, 3> recv_buffer_;
     socket_.async_receive_from(
             boost::asio::buffer(recv_buffer_), remote_endpoint_,
             boost::bind(&UDP_server::handle_receive, this,
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
     ioc_.run();
  };

void UDP_server::handle_receive(const boost::system::error_code& error,
      std::size_t bytes_transferred/*bytes_transferred*/)
  {
    std::cout << "handle_receive" << '\n';
    if (!error){
      std::cout << bytes_transferred << std::endl;
      start_receive();

    }else{
    std::string str_err = "ErrorListen: " + error.message();
    std::cout << str_err << std::endl;
}
  };
