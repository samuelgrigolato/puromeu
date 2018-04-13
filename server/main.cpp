#include <memory>
#include <list>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;


std::string make_daytime_string() {
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}


int main() {

    try {

        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 2020));

        std::list<std::shared_ptr<tcp::socket>> sockets;
        for (;;) {

            std::shared_ptr<tcp::socket> new_socket(new tcp::socket(io_context));
            acceptor.accept(*new_socket);
            sockets.push_back(new_socket);

            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;

            std::list<std::shared_ptr<tcp::socket>>::iterator it = sockets.begin();
            while (it != sockets.end()) {
                boost::asio::write(**it, boost::asio::buffer(message), ignored_error);
                it++;
            }

        }

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
