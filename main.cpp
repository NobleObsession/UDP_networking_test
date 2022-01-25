#include <boost/asio.hpp>
#include <iostream>

#include "UDP_server.h"

int main(int argc, char *argv[]){
    bool test_mode = false;
    if(argc == 2 && std::string(argv[1]) == "test"){
      std::cout << "Server runs in test mode" << std::endl;
      test_mode = true;
    }
    int num_threads = 10;
    int port = 55514;
    boost::asio::io_context io_context;
    UDP_server server(io_context, port, num_threads, test_mode);
    io_context.run();
    return 0;
}
