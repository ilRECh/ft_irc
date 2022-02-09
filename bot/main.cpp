#include "Bot.hpp"

void usage() {
    std::cout << "\nusage: ./bot <ip/domain_of_Server> <port> <password>\n\n" << std::endl;
}

int main(int argc, char **argv) {
    if (argc not_eq 4) {
        usage();
        return 1;
    }
    Bot SimpleBot(argv[1], argv[2], argv[3]);
    try {
        SimpleBot.run();
    } catch (...) {}
    return 0;
}
