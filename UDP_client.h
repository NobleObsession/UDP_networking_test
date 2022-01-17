#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
using boost::asio::ip::udp;

class UDP_client{
public:
    UDP_client();
    void send();
private:
    void handler(
            const boost::system::error_code& error,
            std::size_t bytes_transferred
          );
    boost::asio::io_context ioc_;
    udp::resolver resolver_;
    udp::endpoint remote_endpoint_;
    udp::socket socket_;
};

#endif // UDP_CLIENT_H
