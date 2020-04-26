#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

#include "bst.h"

bst::bst() {
  root = NULL;
}

bst::bst() {
  //check the NULL root first. otherwise delete will cause a segmentation fault
  if (root != NULL) 
    deleteTree(root);

  //The line below is critical to make root non-dangling pointer
  root = NULL;
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
bstNode* bst::remove(int data, int empNumber, bstNode* rt) {
  if (rt == NULL)
    return rt; // data not found. Do nothing.
  if (data < rt->data)
    rt->left = remove(data, empNumber, rt->left);
  else if (data > rt->data)
    rt->right = remove(data, empNumber, rt->right);

  // now, 'rt' holds 'data' to be removed
  else if (rt->left !=NULL && rt->right != NULL)
  {
    // Two children exist
    // step1: findSuccessor is to find the successor node
    double minData = findSuccessor(rt->right)->data;

    // step2: replace the data
    rt->data = minData;

    // step3: remove the successor node by using recursion
    //        passing rt->right as the tree root
    //        so that the successor node can be deleted
    rt->right = remove(minData, empNumber, rt->right);
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

void bst::inOrder(bstNode* rt, void (*visit)(int)) {
  if (rt != 0) {
    inOrder(rt->left, visit);
    (*visit)(rt->data);
    inOrder(rt->right, visit);
  }
}

// private: search data in the BST with rt as root
bool bst::search(bstNode* rt, int data, int empNumber) {
  if (rt == NULL) return false;
  else if (rt->data == data) return true;
  else if (data < rt->data)
    return search(rt->left, data, empNumber);
  else
    return search(rt->right, data, empNumber);
}

/**********************NOT NEEDED*************************
int bst::getNodeCount(bstNode* rt) {
  if (rt == 0) return 0;
  return getNodeCount(rt->left) + getNodeCount(rt->right) + 1;
}
*/

/**********************NOT NEEDED*************************
int bst::getHeight(bstNode* rt) {
  if (rt == NULL) return 0;
  else if (rt->left == NULL && rt->right == NULL) return 1;
  else {
    int rh = getHeight(rt->right);
    int lh = getHeight(rt->left);
    return rh > lh ? rh+1 : lh+1;
  }
}
*/

//findSuccessor is written as a recursive function to practice recursion
//You can change this function with a loop, making it iterative
//Note: the return type is a node pointer
bstNode* bst::findSuccessor(bstNode* rt) {
  if (rt->left == NULL)
    return rt;
  else
    return findSuccessor(rt->left);
}