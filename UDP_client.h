#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
using boost::asio::ip::udp;

class UDP_client{
public:
    UDP_client();
    void run();
private:
    void send_message();
    boost::asio::io_context ioc_;
    udp::socket socket_;
    int num_messages_;
};

#endif // UDP_CLIENT_H
