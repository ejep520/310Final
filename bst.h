#ifndef __BST_H__
#define __BST_H__
#include "binaryFile.h"

using namespace std;

typedef struct bstnode {
    bstnode *parent = nullptr;
    bstnode *left = nullptr;
    bstnode *right = nullptr;
    EMP_REC employee{
        .dept = 0,
        .enumber = 0,
        .name = ""
    };
}node;

class bst
{
    public:
    // public fields
    // public methods
    bst();
    ~bst();
    bool insert_node(EMP_REC);
    bool find_node(char[30]);
    bool find_node(int); // Int is the employee number.
    bool remove_node(char[30]);
    bool remove_node(int); // Int is the employee number.
    bool update_node(char[30], int, int); // Dept then employee number.
    void print_tree(void);
    EMP_REC *bin_out_tree(void);
    private:
    // private fields
    node *head = nullptr;
    // private methods
    node *p_find_node(int); // Int is the employee number.
    node *p_find_node(char[30]);
    node *p_find_successor(node*);
    int p_remove_node(node*);
    void p_remove_subtree(node*);
};

#endif
