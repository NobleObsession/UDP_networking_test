#include "UDP_server.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <boost/bind/bind.hpp>

extern thread_local int local_thread_number;

PacketPrinter::PacketPrinter(){
    output_file_.open("processed_packets.txt");
};

void PacketPrinter::PrintPacket(int packet_id, std::string message){
    output_file_ << packet_id << ' ' << message << std::endl;
};

UDP_server::UDP_server(boost::asio::io_context& io_context, int port, int num_threads)
    : remote_endpoint_(udp::v4(), port),
    socket_(io_context, remote_endpoint_), thread_pool_(num_threads), packet_counter_(0){
    StartReceive();
};

void UDP_server::StartReceive(){
    socket_.async_receive_from(
             boost::asio::buffer(data_), remote_endpoint_,
             boost::bind(&UDP_server::HandleReceive, this,
               boost::asio::placeholders::error,
               boost::asio::placeholders::bytes_transferred));
  };

void UDP_server::ProcessPacket(int packet_id, std::string received_packet){
    std::thread::id thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << received_packet << ' ' <<
                 thread_id << ' ' << local_thread_number << '\n';
    std::string processed_msg = ss.str();
    int latency = rand() % 100;
    std::this_thread::sleep_for(std::chrono::milliseconds(latency));
    printer_.PrintPacket(packet_id, processed_msg);
};

void UDP_server::HandleReceive(const boost::system::error_code& error,
      std::size_t){
    if(error){
      std::string str_err = "ErrorListen: " + error.message();
      std::cerr << str_err << std::endl;
      return;
    }
    ++packet_counter_;
    int packet_id = packet_counter_;
    std::string received_packet = std::string(data_);
    thread_pool_.Submit([received_packet, packet_id, this]{ProcessPacket(packet_id, received_packet);});
    StartReceive();
  };
