#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <boost/asio.hpp>
#include <fstream>
#include <string>

#include "thread_util.h"

using boost::asio::ip::udp;

class PacketPrinter{
public:
    PacketPrinter();
    void PrintPacket(int packet_id, std::string message);
private:
    std::ofstream output_file_;
    int prev_processed_id_ = 0;
};

class UDP_server{
public:
  UDP_server(boost::asio::io_context& io_context, int port, int num_threads);
private:
  void StartReceive();
  void HandleReceive(const boost::system::error_code& error,
        std::size_t bytes_transferred);
  void ProcessPacket(int packet_id, std::string received_packet);

  udp::endpoint remote_endpoint_;
  udp::socket socket_;
  char data_[100];
  PacketPrinter printer_;
  ThreadPool thread_pool_;
  int packet_counter_;
};

#endif // UDP_SERVER_H
