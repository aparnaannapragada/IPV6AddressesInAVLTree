// Definition of the avlTree class

#ifndef avlTree_class
#define avlTree_class

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include "Socket.h"

struct avl_node 
{
   char country[50];
   struct in6_addr sa_fromIp;
   struct in6_addr sa_toIp;
   struct avl_node *left;
   struct avl_node *right;
};


class avlTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        int compare_ipv6(struct in6_addr , struct in6_addr);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, struct in6_addr , struct in6_addr , char*);
        void display(avl_node*, avl_node*, int);
        void search(avl_node *, struct in6_addr, char*);
        int proceedOrNot (avl_node *root, struct in6_addr searchIp);
        bool isLessThanRoot (avl_node *root, struct in6_addr searchIp);
        avlTree()
        {
            avl_node* root;
            root = NULL;
        }
};

#endif
