#include "server.h"

int main()
{
    redis::Server server(6380);
    server.start();
    return 0;
}
