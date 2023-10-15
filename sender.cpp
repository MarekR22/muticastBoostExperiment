#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
try {
    boost::asio::io_service io_service;
    udp::socket socket(io_service);

    udp::endpoint multicast_endpoint(boost::asio::ip::address::from_string("239.255.0.1"), 12345);
    socket.open(multicast_endpoint.protocol());
    socket.set_option(udp::socket::reuse_address(true));
    socket.set_option(boost::asio::ip::multicast::hops(1));
    
    std::string message;
    while (getline(std::cin, message)) {
        socket.send_to(boost::asio::buffer(message), multicast_endpoint);
        std::cout << "Sent: " << message << std::endl;
    }
    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
}
