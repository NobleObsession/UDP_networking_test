#include <iostream>
#include <boost/asio.hpp>
#include "UDP_server.h"
#include "UDP_client.h"

using namespace std;

int main()
{
    auto server = std::make_shared<UDP_server>();
    server->start_receive();
    return 0;
}
