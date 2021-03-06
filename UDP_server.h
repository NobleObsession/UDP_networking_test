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
    ~PacketPrinter();
    void PushPacket(const int packet_id, const std::string& message);
    void OutputThread();
private:
    std::ofstream output_file_;
    int prev_processed_id_;
    std::atomic<bool> done_;
    std::thread output_thread_;
    ThreadsafePriorityQueue<std::pair<int, std::string>> packet_queue_;

};

class UDP_server{
public:
  UDP_server(boost::asio::io_context& io_context, int port,
             int num_threads, bool test_mode);
private:
  void StartReceive();
  void HandleReceive(const boost::system::error_code& error,
        std::size_t);
  void ProcessPacket(const int packet_id, const std::string& received_packet);

  udp::endpoint remote_endpoint_;
  udp::socket socket_;
  char data_[100];
  PacketPrinter printer_;
  ThreadPool thread_pool_;
  int packet_counter_;
  bool test_mode_;
};

#endif // UDP_SERVER_H
