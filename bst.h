#ifndef __BST_H__
#define __BST_H__
#include "binaryFile.h"

using namespace std;

typedef struct bstnode {
    bstnode *parent = nullptr;
    bstnode *left = nullptr;
    bstnode *right = nullptr;
    EMP_REC employee;
}node;

class bst
{
    public:
    bst();
    ~bst();
    bool insert_node(EMP_REC);
    bool find_node(char[30]);
    bool find_node(int);
    bool remove_node(char[30]);
    bool remove_node(int);
    bool update_node(char[30], int, int);
    void print_tree(void);
    EMP_REC *bin_out_tree(void);
    private:
    node *head = nullptr;
    void p_remove_subtree();
    node *p_find_node(int);
    node *p_find_node(char[30]);
    int p_remove_node(node*);
};

#endif
