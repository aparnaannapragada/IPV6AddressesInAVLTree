#include "avlTree.h"


int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = std::max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*
 *  * Height Difference 
 *   */
int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}


/*
 *  * Right- Right Rotation
 *   */
avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
/*
 *  * Left- Left Rotation
 *   */
avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

/*
 *  * Left - Right Rotation
 *   */
avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}

/*
 *  * Right- Left Rotation
 *   */
avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);

}


/*
 *  * Balancing AVL Tree
 *   */
avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}


void avlTree::display(avl_node *root, avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(root, ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
           std::cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            std::cout<<"        ";
        std::cout<<"Country is: "<<ptr->country<<"\n";
        display(root, ptr->left, level + 1);
    }
}


/*
 * Insert Element into the tree
 *  */
avl_node* avlTree::insert(avl_node *root, struct in6_addr fromIp, struct in6_addr toIp, char* code)
{
    int ret = 0;
    if (root == NULL)
    {
        root = new avl_node;
        root->sa_fromIp = fromIp;
        root->sa_toIp = toIp;
        strncpy(root->country, code, sizeof(root->country));
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else
    {
       ret = compare_ipv6(root->sa_fromIp, fromIp);
       if (ret >= 0)
       {
          root->left = insert(root->left, fromIp, toIp, code);
          root = balance (root);
       }
       else if (ret < 0)
       {
          root->right = insert(root->right, fromIp, toIp, code);
          root = balance (root);
       }
    }
    return root;
}


void avlTree::search(avl_node * p, struct in6_addr searchIp, char *s)
{
        if (p==NULL)
        {
                std::cout<<"Not found\n"<<"\n";
                strcpy(s, "Not found");
        }
        else
        {
               if (proceedOrNot(p, searchIp) == 0)
               {
                  std::cout<<"Elment found!"<<"\n";
                  strncpy(s, p->country, 50);
               }
               else
               {
                    if (isLessThanRoot(p, searchIp) == true)
                    {
                       std::cout<<"Going left"<<"\n";
                       search(p->left, searchIp, s);
                    }
                    else
                    {
                       std::cout<<"Going right"<<"\n";
                       search (p->right, searchIp, s);
                    }
                }
         }
}

int avlTree::proceedOrNot (avl_node *root, struct in6_addr searchIp)
{
     int ret, ret1;
     ret = compare_ipv6(root->sa_fromIp, searchIp);
     ret1 = compare_ipv6(root->sa_toIp, searchIp);
     if ((ret == 0) || (ret == -1 && ret1 == 1) || (ret1 == 0))
           return 0;
     else
           return -1;
}


bool avlTree::isLessThanRoot (avl_node *root, struct in6_addr searchIp)
{
     bool ret;
     int val1, val2;
     val1 = compare_ipv6(root->sa_fromIp, searchIp);
     val2 = compare_ipv6(root->sa_toIp, searchIp);
     if (val1 == 1)
           return true;
     else
           return false;
}

int avlTree::compare_ipv6(struct in6_addr ipA, struct in6_addr ipB)
{
    int i = 0;
    for(i = 0; i < sizeof(in6_addr); ++i)
    {
        if (ipA.s6_addr[i] < ipB.s6_addr[i])
            return -1;
        else if (ipA.s6_addr[i] > ipB.s6_addr[i])
            return 1;
    }
    return 0;
}

