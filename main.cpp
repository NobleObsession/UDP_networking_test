#include <boost/asio.hpp>
#include "UDP_server.h"

int main(){
    int num_threads = 10;
    int port = 55514;
    boost::asio::io_context io_context;
    UDP_server server(io_context, port, num_threads);
    io_context.run();
    return 0;
}
