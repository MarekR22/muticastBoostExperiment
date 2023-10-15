#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/multicast.hpp>

using boost::asio::ip::udp;

int main()
try {
    boost::asio::io_service io_service;
    udp::socket socket(io_service, udp::endpoint(udp::v4(), 12345));

    boost::asio::ip::address multicast_address = boost::asio::ip::address::from_string("239.255.0.1");
    socket.set_option(udp::socket::reuse_address(true));
    socket.set_option(udp::socket::broadcast(true));
    socket.set_option(boost::asio::ip::multicast::outbound_interface(boost::asio::ip::address_v4::any()));
    socket.set_option(boost::asio::ip::multicast::join_group(multicast_address));

    while (true) {
        char data[1024];
        udp::endpoint sender_endpoint;
        size_t length = socket.receive_from(boost::asio::buffer(data), sender_endpoint);

        std::cout << "Received: " << std::string(data, length) << " from " << sender_endpoint.address() << ":" << sender_endpoint.port() << std::endl;
    }
    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 2;
}
