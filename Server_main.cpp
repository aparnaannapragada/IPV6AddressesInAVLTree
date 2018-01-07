#include<iostream>
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <cstring>
#include "userIo.h"

int main ( int argc, int argv[] )
{
  packet p = {};
  avlTree avl;
  avl_node* root = NULL;
  userIo toClient;
  int portNo;
  int x;
  char s[50] = {0};
  std::string choice;
  char* buffer = new char [sizeof(packet)];

  std::cout << "Hey! This is Server. Currently running on port No. 30000. You want to change it? (Y/N)\n";
  std::cin >> choice;
  if (choice.compare("Y") == 0)
  {
        std::cout << "Enter the port number you want the server to run on: \n";
        std::cin >> portNo;
  }
  else
  {
       portNo = 30000;
  }
  std::cout << "Server running on port number " << portNo << ".......\n";


  try
    {
      // Create the socket
      ServerSocket server ( portNo );
      while ( true )
	{
	  ServerSocket new_sock;
	  server.accept ( new_sock );
     	  try
	    {
	      while ( true )
		{
                   std::string searchString;
                   new_sock >> buffer;
	           p = toClient.outputToUser(buffer, &x);
                   if (x == 1) 
                   {
                       root = avl.insert(root, p.fromIp, p.toIp, p.country);
                       new_sock << "Success!";
                    }
                    else if (x == 2)
                    {
                        avl.search(root, p.fromIp, s);
                        searchString = s;
                        new_sock << searchString;
                    }
                   else 
                           new_sock << "Failure!";
                }
             
	    }
	  catch ( SocketException& ) {}

	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
  
  return 0;
}
