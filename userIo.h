// Definition of the clientIo class

#ifndef userIo_class
#define userIo_class

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "Socket.h"
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include<cstring>
#include<stdint.h>
#include "avlTree.h"

class userIo
{
    public:
        void inputFromUser(char*);
        packet outputToUser(char*, int*);
};

#endif

