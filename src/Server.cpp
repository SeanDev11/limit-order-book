#include "Server.hpp"

Server::Server() : exchange(BookManager()) {}

int check(int exp, const char *msg);
void send_msg(int client_socket, char *buffer, size_t buffer_size, const char *format, ...);

void Server::handle_connection(int client_socket) {
    char r_buff[BUFFSIZE];
    char w_buff[BUFFSIZE];
    size_t bytes_read;

    while (true) {
        memset(r_buff, 0, BUFFSIZE);
        memset(w_buff, 0, BUFFSIZE);

        bytes_read = read(client_socket, r_buff, sizeof(r_buff) - 1);
        if (bytes_read <= 0) {
            std::cerr << "Connection closed or error reading data." << std::endl;
            break; // Exit the loop on client disconnect or error
        }

        r_buff[bytes_read] = '\0'; // Null-terminate the received data

        std::cout << "REQUEST: " << r_buff << std::endl;

        char *split;
        int i = 0;
        char *command[10];

        split = strtok(r_buff, " \n");
        while (split != NULL) {
            command[i++] = split;
            std::cout << split << std::endl;
            split = strtok(NULL, " \n");
        }

        if (strcmp(command[0], "orders") == 0) {
            unsigned int security_id = atoi(command[1]);
            int num_orders = exchange.get_num_open_orders(security_id);

            send_msg(client_socket, w_buff, sizeof w_buff, "Total of %d open orders for security %d", num_orders, security_id);
        } else if (strcmp(command[0], "buy") == 0) {
            unsigned int security_id = atoi(command[1]);
            int volume = atoi(command[2]);
            int price = atoi(command[3]);
            int executed_volume = exchange.place_order(security_id, true, volume, price);

            send_msg(client_socket, w_buff, sizeof w_buff, "Bought %d shares of security %d @%d", executed_volume,
                     security_id, price);
        } else if (strcmp(command[0], "sell") == 0) {
            unsigned int security_id = atoi(command[1]);
            int volume = atoi(command[2]);
            int price = atoi(command[3]);
            int executed_volume = exchange.place_order(security_id, false, volume, price);

            send_msg(client_socket, w_buff, sizeof w_buff, "Sold %d shares of security %d @%d", executed_volume,
                     security_id, price);
        } else if (strcmp(command[0], "cancel") == 0) {
            unsigned int security_id = atoi(command[1]);
            unsigned int order_id = atoi(command[2]);

            int status = exchange.cancel_order(security_id, order_id);
            if (status < 0) {
                send_msg(client_socket, w_buff, sizeof w_buff, "Failed to cancel order with id %d for security %d", order_id, security_id);
            } else {
                send_msg(client_socket, w_buff, sizeof w_buff, "Successfully cancelled order with id %d for security %d", order_id, security_id);
            }
        } else if (strcmp(command[0], "spread") == 0) {
            unsigned int security_id = atoi(command[1]);
            int spread = exchange.get_spread(security_id);

            send_msg(client_socket, w_buff, sizeof w_buff, "Current spread for security %d is %d", security_id, spread);
        } else if (strcmp(command[0], "volume") == 0) {
            unsigned int security_id = atoi(command[1]);
            int limit = atoi(command[2]);
            int volume = exchange.get_volume_at_limit(security_id, limit);

            send_msg(client_socket, w_buff, sizeof w_buff, "Current volume @%d for security %d is %d", limit, security_id, volume);
        } else if (strcmp(command[0], "bestbid") == 0) {
            unsigned int security_id = atoi(command[1]);
            int bestbid = exchange.get_best_bid(security_id);

            send_msg(client_socket, w_buff, sizeof w_buff, "Current best bid for security %d is %d", security_id, bestbid);
        } else if (strcmp(command[0], "bestask") == 0) {
            unsigned int security_id = atoi(command[1]);
            int bestask = exchange.get_best_ask(security_id);

            send_msg(client_socket, w_buff, sizeof w_buff, "Current best ask for security %d is %d", security_id, bestask);
        } else {
            send_msg(client_socket, w_buff, sizeof w_buff, "Command not recognized. Type 'help' for a list of available commands.");
        }
    }
    close(client_socket);
}

void Server::run() {
    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket.");

    //bzero(&servaddr, sizeof servaddr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //htonl
    server_addr.sin_port = htons(SERVERPORT);

    check(bind(server_socket, (SA*)&server_addr, sizeof server_addr), "Bind failed.");

    check(listen(server_socket, SERVER_BACKLOG), "Listen failed.");

    while (true) {
        std::cout << "Waiting..." << std::endl;
        addr_size = sizeof (SA_IN);
        check(client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size),
              "Accept failed.");

        std::cout << "Connected" << std::endl;
        handle_connection(client_socket);
    }

}

int check(int exp, const char *msg) {
    if (exp == SOCKETERROR) {
        perror(msg);
        exit(1);
    }
    return exp;
}

void send_msg(int client_socket, char *buffer, size_t buffer_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int to_send = vsnprintf(buffer, buffer_size, format, args);
    va_end(args);
    write(client_socket, buffer, to_send);
}
