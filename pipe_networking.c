#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

    char pid[HANDSHAKE_BUFFER_SIZE];
    char msg[HANDSHAKE_BUFFER_SIZE];

    mkfifo( "wkp", 0666 );
    printf("WKP created.\n");

    int from_client = open( "wkp", O_RDONLY );
    printf("Opened client in Read Mode.\n");
    read( from_client, pid, sizeof( pid ) );
    printf("Got PID: %s\n", pid);

    remove( "wkp" );
    printf("Removed Wkp.\n");

    *to_client = open( pid, O_WRONLY );
    printf("Opened client in Write Mode.\n");

    write( *to_client, ACK, sizeof( ACK ) );
    printf("Written to Client.\n");

    read( from_client, msg, sizeof( msg ) );
    printf("Message: %s\n", msg);

    return from_client;

}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

    char pid[HANDSHAKE_BUFFER_SIZE];
    char msg[HANDSHAKE_BUFFER_SIZE];

    sprintf( pid, "%d", getpid() );
    mkfifo( pid, 0666 );
    printf("Private FIFO created.\n");

    *to_server = open( pid, O_WRONLY );
    printf("Opened server in Write Mode.\n");
    write(*to_server, pid, sizeof( pid ) );
    printf("Written to server.\n");

    int from_server = open( pid, O_RDONLY );
    printf("Opened server in Read Mode.\n");
    read( from_server, msg, sizeof( msg ) );
    printf("Message: %s\n", msg);
    remove( pid );
    printf("Removed PID.\n");

    write(*to_server, ACK, sizeof( ACK ) );
    printf("Written to server.\n");

    return from_server;

}
