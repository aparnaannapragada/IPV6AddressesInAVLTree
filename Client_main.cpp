#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include "userIo.h"

int main ( int argc, int argv[] )
{
  userIo client;
  char *buffer = new char [sizeof(packet)];
  client.inputFromUser(buffer);
  std::string reply;

  try
    {

      ClientSocket client_socket ( "localhost", 30000 );
      
      try
	{
	  client_socket << buffer;
          client_socket >> reply;
          std::cout<<reply<<"\n";
	}
      catch ( SocketException& ) {}


    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
  return 0;
}
