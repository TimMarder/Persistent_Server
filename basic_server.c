#include "pipe_networking.h"


int main() {

  //signal( SIGINT, sighandler );

  int to_client;
  int from_client;
  char input[BUFFER_SIZE];

  from_client = server_handshake( &to_client );

  while( read( from_client, input, sizeof( input ) ) ) {

      printf("Message received from CLIENT: %s\n", input);
      for (char *i = input; *i; i++) {

          (*i)++;

      }
      write( to_client, input, sizeof( input ) );
      printf("Sent back to CLIENT: %s\n", input);

      }

}


static void sighandler( int n ) {

    if (n == SIGINT) {

        remove("wkp");
        printf("Exiting...\n");
        exit( 0 );

    }

}
