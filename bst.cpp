#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

#include "bst.h"

bst::bst() {
  //check the NULL root first. otherwise delete will cause a segmentation fault
  if (root != NULL) 
    deleteTree(root);

  //The line below is critical to make root non-dangling pointer
  root = NULL;
}

bst::~bst() {

}

//Note: deleteTree calls deleteTree by passing left and right pointers, respectively.
void bst::deleteTree(bstNode* rt) {
  if (rt) {
    deleteTree(rt->left);
    deleteTree(rt->right);
    delete rt;
  }
}

//Note: the return type is the node pointer
bstNode* bst::insert(int data, int empNumber, bstNode* rt) {
  try {
    if (rt == NULL) {
      rt = new bstNode(data, empNumber);
    } 
    else if (data < rt->data) {
      rt->left = insert(data, empNumber, rt->left);
    } 
    else if (data > rt->data)
      rt->right = insert(data, empNumber, rt->right);

    // else already exists. Ignore or Update counter.

    return rt;
  } catch (bad_alloc &e) {
    cout << "mem allocation exception: " << e.what() << endl;
    exit(1);
  }
}

//Note: the return type is the node pointer
bstNode* bst::remove(int empNumber, bstNode* rt) {
  if (rt == NULL)
    return rt; // data not found. Do nothing.
  if (empNumber < rt->employeeNumber)
    rt->left = remove(empNumber, rt->left);
  else if (empNumber > rt->employeeNumber)
    rt->right = remove(empNumber, rt->right);

  // now, 'rt' holds 'data' to be removed
  else if (rt->left !=NULL && rt->right != NULL)
  {
    // Two children exist
    // step1: findSuccessor is to find the successor node
    int minData = findSuccessor(rt->right)->employeeNumber;

    // step2: replace the data
    rt->employeeNumber = minData;

    // step3: remove the successor node by using recursion
    //        passing rt->right as the tree root
    //        so that the successor node can be deleted
    rt->right = remove(minData, rt->right);
  }
  else {
    // only one child exists or no children
    
    bstNode* discard = rt;

    //if rt->left != NULL, i.e the only one child is the left 
    //    then  rt = rt->left, i.e making the left subtree to rt 
    //if rt->>left != NULL, i.e the only one child should be the right or no children 
    //    then rt = rt->right.  This makes two subcases
    //	       c1) if rt->right is NULL, no children and rt = NULL	
    //         c2) if rt->right is not NULL, the right is the only child, making the right subtree to rt
    rt = (rt->left != NULL) ? rt->left : rt->right; 


    delete discard; 
  }

  return rt;
}

//traversal
void bst::inOrder(bstNode* rt, void (*visit)(int)) {
  if (rt != 0) {
    inOrder(rt->left, visit);
    (*visit)(rt->data);
    inOrder(rt->right, visit);
  }
}

// private: search for employeeNumber in the BST with rt as root
bool bst::search(bstNode* rt, int empNumber) {
  if (rt == NULL) return false;
  else if (rt->employeeNumber == empNumber) return true;
  else if (empNumber < rt->employeeNumber)
    return search(rt->left, empNumber);
  else
    return search(rt->right, empNumber);
}

//private: after searching for employeeNumber in the BST to return bool if employee exists,
//this function will return the offset int for the employee node.
int bst::returnOffset(bstNode* rt, int empNumber) {
  if (rt == NULL) return false;
  else if (rt->employeeNumber == empNumber) 
    {
      int returnOffset = 0;
      returnOffset = rt->data;
      return returnOffset;
    }
  else if (empNumber < rt->employeeNumber)
    return search(rt->left, empNumber);
  else
    return search(rt->right, empNumber);
}

//findSuccessor is written as a recursive function
//Note: the return type is a node pointer
bstNode* bst::findSuccessor(bstNode* rt) {
  if (rt->left == NULL)
    return rt;
  else
    return findSuccessor(rt->left);
}