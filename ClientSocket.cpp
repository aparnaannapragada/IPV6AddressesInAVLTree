// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

}

const ClientSocket& ClientSocket::operator << ( const char* p ) const
{
  if ( ! Socket::send ( p ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( char* p ) const
{
  if ( ! Socket::recv ( p ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}


/* Sending int*/
/*const ClientSocket& ClientSocket::operator << ( const int num ) const
{
  if ( ! Socket::send ( num ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( int* num ) const
{
  if ( ! Socket::recv ( num ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}*/



const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send_str ( s ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv_str ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}
