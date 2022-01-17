#include <gtest/gtest.h>

#include "UDP_server.h"
#include "UDP_client.h"

TEST(Initial_test, BasicAssertions) {
    UDP_server server;
    UDP_client client;
    server.start_receive();
    client.send();
}
