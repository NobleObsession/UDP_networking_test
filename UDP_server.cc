#include "UDP_server.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <boost/bind/bind.hpp>

extern thread_local int local_thread_number;

PacketPrinter::PacketPrinter():prev_processed_id_(-1), done_(false){
    output_thread_= std::thread([this](){OutputThread();});
    output_file_.open("processed_packets.txt");
};

PacketPrinter::~PacketPrinter(){
    done_ = false;
    if(output_thread_.joinable()){
       output_thread_.join();
    }
    output_file_.close();
};

void PacketPrinter::OutputThread(){
    while(!done_){
       std::pair<int, std::string> top_element;
       if(!packet_queue_.Top(top_element)){
         std::this_thread::yield();
         continue;
       }
       if(1 == top_element.first - prev_processed_id_){
         packet_queue_.Pop();
         prev_processed_id_ = top_element.first;
         output_file_ << top_element.second;
       }else{
         std::this_thread::yield();
       }
    }
};

void PacketPrinter::PushPacket(const int packet_id, const std::string& message){
    packet_queue_.Push(std::make_pair(packet_id, message));
}

UDP_server::UDP_server(boost::asio::io_context& io_context, int port,
                       int num_threads, bool test_mode)
    : remote_endpoint_(udp::v4(), port),
    socket_(io_context, remote_endpoint_),
    thread_pool_(num_threads), packet_counter_(0), test_mode_(test_mode){
    StartReceive();
};

void UDP_server::StartReceive(){
    socket_.async_receive_from(
             boost::asio::buffer(data_), remote_endpoint_,
             boost::bind(&UDP_server::HandleReceive, this,
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
  };

void UDP_server::ProcessPacket(const int packet_id, const std::string& received_packet){
    std::thread::id thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << received_packet << ' ' <<
                 thread_id << ' ' << local_thread_number << '\n';
    std::string processed_msg = ss.str();
    int latency = rand() % 200;
    std::this_thread::sleep_for(std::chrono::milliseconds(latency));

    if(test_mode_){ //Add debug info
       processed_msg = std::to_string(packet_id) + " " + processed_msg;
    }
    printer_.PushPacket(packet_id, processed_msg);
};

void UDP_server::HandleReceive(const boost::system::error_code& error,
      std::size_t){
    if(error){
      std::string str_err = "ErrorListen: " + error.message();
      std::cerr << str_err << std::endl;
      return;
    }
    int packet_id = packet_counter_;
    ++packet_counter_;
    std::string received_packet = std::string(data_);
    thread_pool_.Submit([received_packet, packet_id, this]
        {ProcessPacket(packet_id, received_packet);});
    StartReceive();
  };
