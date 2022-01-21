#include <gtest/gtest.h>

#include "UDP_server.h"
#include "UDP_client.h"

TEST(Initial_test, BasicAssertions) {

    auto server = std::make_shared<UDP_server>();
    server->start_receive();

    UDP_client client;
    client.run();
}
