#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace redis
{

    class Server
    {
      public:
        Server(int port);
        ~Server() noexcept;

        // listen on the socket + accept client connections
        void start();

        
        private:
          sockaddr_in d_addr;
          int d_server_fd;
          void spawn(int client_fd);
    };

} // namespace redis
