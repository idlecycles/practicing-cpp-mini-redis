#include "server.h"
#include "resp_parser.h"
#include "command_handler.h"

#include <iostream>
#include <stdexcept>

namespace redis
{
    Server::Server(int port) : d_addr{}
    {
        d_server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (d_server_fd == -1)
        {
            throw std::runtime_error("Failed to create socket");
        }

        d_addr.sin_family = AF_INET;
        d_addr.sin_addr.s_addr = INADDR_ANY;
        d_addr.sin_port = htons(port);

        if (bind(d_server_fd, (sockaddr *)&d_addr, sizeof(d_addr)) == -1)
        {
            close(d_server_fd);
            throw std::runtime_error("Failed to bind to port");
        }
    }

    Server::~Server()
    {
        close(d_server_fd);
    }

    void Server::start()
    {
        if (listen(d_server_fd, 10) == -1)
        {
            throw std::runtime_error("Cannot listen on designated port");
        }

        std::cout << "Listening on port " << ntohs(d_addr.sin_port) << "\n";

        while (true)
        {
            int client_fd = accept(d_server_fd, nullptr, nullptr);
            if (client_fd == -1)
            {
                std::cerr << "Failed to accept client\n";
                continue;
            }

            char buffer[1024];
            while (true)
            {
                int bytes = read(client_fd, buffer, sizeof(buffer));
                if (bytes <= 0)
                    break;

                std::string raw(buffer, bytes);
                std::vector<std::string> commands = parse_resp(raw);
                std::string response = handle_command(commands, store);
                write(client_fd, response.c_str(), response.size());
            }
            close(client_fd);
        }
    }
} // namespace redis
