#ifndef _BST_H_
#define	_BST_H_

#include "bstNode.h"
#include <vector>

using namespace std;

// Binary Search Tree for int data
class bst {
  private:
    bstNode* root;
    

    //private member functions
    bstNode* insert(int data, int employeeNumber,bstNode* r); //inserts employee data into node, then into a bst
    bstNode* remove(int employeeNumber, bstNode* r); //removes employee node
    vector<int> inOrder(bstNode* r); //inorder traversal through bst
    bool search(bstNode* r, int employeeNumber); //search bst for employee node
    int returnOffset(bstNode* r,int employeeNumber); //searches then returns offset of employee node
    void deleteTree(bstNode* r); //deletes bst
    bstNode*	findSuccessor(bstNode*); //find successor node
    vector<int> storeOffset(int storedOffset); //stores offsets into vector and returns the vector

  public:
    bst(); //constructor
    virtual ~bst(); //destructor

    //public member functions
    void insert(int data, int employeeNumber) { root = insert(data, employeeNumber, root); } //calls private insert method
    void remove(int employeeNumber) { root = remove(employeeNumber, root); } //calls private remove method
    bool search(int employeeNumber) { return search(root, employeeNumber); } //calls private search method
    int returnOffset(int employeeNumber) {return returnOffset(root, employeeNumber); } //calls private returnOffset method
    vector<int> store() {return inOrder(root);} //calls private storeOffset method
    

};

#endif	/* _BST_H_ */