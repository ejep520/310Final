/*
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

*/

#ifndef _BST_H_
#define	_BST_H_

#include "bstNode.h"

// Binary Search Tree for "double" data
class bst {
  private:
    bstNode* root;

    // Internally used by corresponding public function 
    // So, these are private
    bstNode* insert(double data, bstNode* r);
    bstNode* remove(double data, bstNode* r);
    void inOrder(bstNode* r, void (*visit)(double));
    bool search(bstNode* r, double data);
    int getNodeCount(bstNode* r);
    int getHeight(bstNode* r);
    void deleteTree(bstNode* r);
    bstNode*	findSuccessor(bstNode*);

  public:
    bst();
    virtual ~bst();

    // Member functions used by client program 
    // Check the difference between public and corresponding private function call in terms of their signatures
    void insert(double data) { root = insert(data, root); }
    void remove(double data) { root = remove(data, root); }
    bool search(double data) { return search(root, data); }
    
    // Tree Traversal
    void inOrder( void (*visit)(double) ) { inOrder(root, visit); }

    int getNodeCount() { return getNodeCount(root); }
    int getHeight() { return getHeight(root); }
};

#endif	/* _BST_H_ */