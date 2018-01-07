#include "userIo.h"


void userIo::inputFromUser(char* buf)
{
    packet p = {};
    int conv = 0;
    int check;
    char fromIpAddress[INET6_ADDRSTRLEN] = {0};
    char toIpAddress[INET6_ADDRSTRLEN] = {0};
    int checkl, checku;
 
    std::cout<<"\n---------------------"<<"\n";
    std::cout<<"AVL Tree Implementation"<<"\n";
    std::cout<<"\n---------------------"<<"\n";
    std::cout<<"1.Insert Element into the tree"<<"\n";
    std::cout<<"2.Search"<<"\n";
    std::cout<<"3.Exit"<<"\n";
    std::cout<<"Enter your Choice: ";
    std::cin>>conv;
   
    switch(conv)
    {
     case 1:
        std::cout<<"Enter the from IPV6 address!"<<"\n";
        std::cin>>fromIpAddress;
        std::cout<<"Enter the to IPV6 address!"<<"\n";
        std::cin>>toIpAddress;
        std::cout << "Enter the country code:\n";
        std::cin.ignore();
        std::cin.getline(p.country, sizeof(p.country));

        checkl = inet_pton(AF_INET6, fromIpAddress, &p.fromIp.s6_addr);
        if (checkl <= 0) {
          if (checkl == 0)
              fprintf(stderr, "Not in presentation format");
          else
              perror("inet_pton");
          exit(EXIT_FAILURE);
         }   
         checku = inet_pton(AF_INET6, toIpAddress, &p.toIp.s6_addr);
         if (checku <= 0) {
            if (checku == 0)
                 fprintf(stderr, "Not in presentation format");
            else
                perror("inet_pton");
            exit(EXIT_FAILURE);
          }
          p.choice = htonl(conv);
          memcpy(buf, &p, sizeof(p));   
          break;

     case 2:
        std::cout<<"Enter value to be searched: ";
        std::cin>>fromIpAddress;
        checkl = inet_pton(AF_INET6, fromIpAddress, &p.fromIp.s6_addr);
        if (checkl <= 0) {
          if (checkl == 0)
              fprintf(stderr, "Not in presentation format");
          else
              perror("inet_pton");
          exit(EXIT_FAILURE);
         }
        p.choice = htonl(conv);
        memcpy(buf, &p, sizeof(p));   
        break;

     case 3:
        exit(1);
        break;

     default:
        std::cout<<"Wrong Choice"<<"\n";
    }
}

packet userIo::outputToUser( char* buf, int* a)
{ 
    packet q = {};
    int32_t conv2;
    char fromIpAddress2[INET6_ADDRSTRLEN] = {0};
    char toIpAddress2[INET6_ADDRSTRLEN] = {0};

    memcpy(&q, buf, sizeof(packet));
    conv2 = ntohl(q.choice);

    if (inet_ntop(AF_INET6, &q.fromIp.s6_addr, fromIpAddress2, sizeof(fromIpAddress2)) != NULL)
       printf("inet6 addr: %s\n", fromIpAddress2);
    else {
       perror("inet_ntop");
       exit(EXIT_FAILURE);
    }

    if (inet_ntop(AF_INET6, &q.toIp.s6_addr, toIpAddress2, sizeof(toIpAddress2)) != NULL)
       printf("inet6 addr: %s\n", toIpAddress2);
    else {
       perror("inet_ntop");
       exit(EXIT_FAILURE);
    }
   
    *a = conv2;
    return q;     

}
