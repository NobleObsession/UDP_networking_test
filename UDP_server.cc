#include "UDP_server.h"
#include <iostream>
#include <sstream>
#include <boost/bind/bind.hpp>
#include <chrono>

thread_local int local_thread_number = 0;
int local_thread_counter = 0;
std::atomic<int> packet_counter = 0;

UDP_server::UDP_server(): remote_endpoint_(udp::v4(), 55514), socket_(ioc_, remote_endpoint_), io_pool_(10){};

void UDP_server::start_receive(){
     socket_.async_receive_from(
             boost::asio::buffer(data_), remote_endpoint_,
             boost::bind(&UDP_server::handle_receive, shared_from_this(),
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
     boost::asio::post(io_pool_, [&]() {
         local_thread_counter++; local_thread_number = local_thread_counter; ioc_.run(); });
  };

void UDP_server::handle_receive(const boost::system::error_code& error,
      std::size_t){
    using namespace std::chrono_literals;
    if(error){
      std::string str_err = "ErrorListen: " + error.message();
      std::cerr << str_err << std::endl;
      return;
    }

    std::thread::id thread_id = std::this_thread::get_id();
    int packet_id = ++packet_counter;
    std::stringstream ss;
    ss << std::string(data_) <<' ' << std::hex << thread_id << ' '
       << std::dec << local_thread_number << ' ' << packet_id << '\n';
    std::cout << ss.str() << std::endl;
    int latency = rand() % 100;
    std::this_thread::sleep_for(std::chrono::milliseconds(latency));

    start_receive();
  };
