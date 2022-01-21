#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
using boost::asio::ip::udp;

class UDP_server: public std::enable_shared_from_this<UDP_server>{
public:
  UDP_server();
  void start_receive();
private:
  void handle_receive(const boost::system::error_code& error,
        std::size_t bytes_transferred);
  boost::asio::io_context ioc_;
  udp::endpoint remote_endpoint_;
  udp::socket socket_;
  char data_[100];
  boost::asio::thread_pool io_pool_;
};

#endif // UDP_SERVER_H
