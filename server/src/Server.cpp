#include "Server.hpp"



Server::Server()
{

    if ( ( udp_socket = socket( AF_INET, SOCK_DGRAM, 0 ) ) < 0 )
    {
        std::cout << "Server::Server(): Error initializa server" << std::endl;
        exit( EXIT_FAILURE );
    }


    buffer = new char[ BUFFER_SIZE ];
    memset( buffer, 0, sizeof( BUFFER_SIZE ) );


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( SERVER_PORT );


    if ( ( bind( udp_socket, ( const struct sockaddr * ) &server_address, sizeof( server_address ) ) ) < 0 )
    {
        std::cout << "Server::Server(): Error bind " << SERVER_IP << " with port " << SERVER_PORT << std::endl;
        exit( EXIT_FAILURE );
    }
}


void Server::listen()
{

    socklen_t sock_len;
    sock_len = sizeof( client_address );

    int n = 0;

    while ( true )
    {
        std::cerr << "Server::listen(): Wait packets" << std::endl;
        n = recvfrom( udp_socket, ( char * ) buffer, BUFFER_SIZE, MSG_WAITALL, ( struct sockaddr * ) &client_address, &sock_len );

        buffer[ n ] = '\0';

        json data = json::parse( buffer );

        std::cout <<  "Server::listen(): recv: " << data.dump() << std::endl;
    }

}
