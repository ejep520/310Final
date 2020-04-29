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
    bool find_node(int); // Int is the employee number.
    bool remove_node(int); // Int is the employee number.
    bool update_node(char[30], int, int); // Dept then employee number.
    void print_tree(void);
    EMP_REC *bin_out_tree(void);
    private:
    // private fields
    node *head = nullptr;
    // private methods
    node *p_find_node(int); // Int is the employee number.
    node *p_find_successor(node*);
    int p_remove_node(node*);
    void p_remove_subtree(node*);
};

#endif

*/

#ifndef _BST_H_
#define	_BST_H_

#include "bstNode.h"

// Binary Search Tree for int data
class bst {
  private:
    bstNode* root;

    //private member functions
    bstNode* insert(int data, int employeeNumber,bstNode* r); //inserts employee data into node, then into a bst
    bstNode* remove(int employeeNumber, bstNode* r); //removes employee node
    void inOrder(bstNode* r, void (*visit)(int)); //inorder traversal through bst
    bool search(bstNode* r, int employeeNumber); //search bst for employee node
    int returnOffset(bstNode* r,int employeeNumber); //searches then returns offset of employee node
    void deleteTree(bstNode* r); //deletes bst
    bstNode*	findSuccessor(bstNode*); //find successor node

  public:
    bst(); //constructor
    virtual ~bst(); //destructor

    //public member functions
    void insert(int data, int employeeNumber) { root = insert(data, employeeNumber, root); } //calls private insert method
    void remove(int employeeNumber) { root = remove(employeeNumber, root); } //calls private remove method
    bool search(int employeeNumber) { return search(root, employeeNumber); } //calls private search method
    int returnOffset(int employeeNumber) {return returnOffset(root, employeeNumber); } //calls private returnOffset method
    
    // Tree Traversal
    void inOrder( void (*visit)(int) ) { inOrder(root, visit); } //calls recursive inOrder method

};

#endif	/* _BST_H_ */