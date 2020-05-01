#include <iostream>
#include <cstdlib>
#include <new>
#include <vector>
using namespace std;

#include "bst.h"

/************************* PUBLIC: CONSTRUCTOR*************************/
bst::bst() {
  root = NULL;
}

/************************* PRIVATE: DESTRUCTOR*************************/
bst::~bst() {
  
  //check the NULL root first. otherwise delete will cause a segmentation fault
  if (root != NULL) 
    deleteTree(root);

}

//-=-=-=-=- Private: bst::deleteTree -=-=-=-
/* Name: binaryFile::deleteTree
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: delete a tree and it's pointers at the root.
* Arguments: 1
* bstNode root -- the root node of the tree
* Returns: N/A
*/

//Note: deleteTree calls deleteTree by passing left and right pointers, respectively.
void bst::deleteTree(bstNode* rt) {
  if (rt) {
    deleteTree(rt->left);
    deleteTree(rt->right);
    delete rt;
  }
}

//-=-=-=-=- Private: bst::insert -=-=-=-
/* Name: binaryFile::insert
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: insert a node into the tree.
* Arguments: 3
* int data -- the offset
* int empNumber -- the employee number
* bstNode root -- the root node of the tree
* Returns: 1
* bstNode*: node pointer
*/
bstNode* bst::insert(int data, int empNumber, bstNode* rt) {
  try {
    if (rt == NULL) {
      rt = new bstNode(data, empNumber);
    } 
    else if (empNumber < rt->employeeNumber) {
      rt->left = insert(data, empNumber, rt->left);
    } 
    else if (empNumber > rt->employeeNumber)
      rt->right = insert(data, empNumber, rt->right);

    // else already exists. Ignore or Update counter.

    return rt;
  } catch (bad_alloc &e) {
    cout << "mem allocation exception: " << e.what() << endl;
    exit(1);
  }
}

//-=-=-=-=- Private: bst::remove -=-=-=-
/* Name: binaryFile::remove
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: remove node from tree.
* Arguments: 2
* int empNumber -- the employee number
* bstNode root -- the root node of the tree
* Returns: 1
* bstNode*: node pointer
*/
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

//-=-=-=-=- Private: bst::inOrder -=-=-=-
/* Name: binaryFile::inOrder
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: inorder traversal through the bst.
* Arguments: 1
* bstNode root -- the root node of the tree
* Returns: N/A
*/
vector<int> bst::inOrder(bstNode* rt) {
  vector<int> offsetList;
  if (rt == NULL) {
    return offsetList;
  }  
  vector<int> data;
  if(rt->left != NULL){
    data = inOrder(rt->left);
    offsetList.insert(offsetList.end(), data.begin(), data.end());
  }
  offsetList.push_back(rt->data);
  if(rt->right != NULL){
    data = inOrder(rt->right);
    offsetList.insert(offsetList.end(),data.begin(), data.end());
  }
  return offsetList;
  }


//-=-=-=-=- Private: bst::search -=-=-=-
/* Name: binaryFile::search
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: to return whether or not an employee number is found in the tree.
* Arguments: 2
* bstNode root -- the root node of the tree
* int empNumber -- the employee number
* Returns: bool
* true: returns when employee number is found
* false: returns when tree is empty/employee number isn't found
*/

bool bst::search(bstNode* rt, int empNumber) {
  if (rt == NULL) return false;
  else if (rt->employeeNumber == empNumber) return true;
  else if (empNumber < rt->employeeNumber)
    return search(rt->left, empNumber);
  else
    return search(rt->right, empNumber);
}

//-=-=-=-=- Private: bst::returnOffset -=-=-=-
/* Name: binaryFile::returnOffset
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: searches tree by employee number then returns the node's offset if found.
* Arguments: 2
* int empNumber -- the employee number
* bstNode root -- the root node of the tree
* Returns: int
* int: offset of node if found.
*/

int bst::returnOffset(bstNode* rt, int empNumber) {
  if (rt == NULL) return -1;
  if (rt->employeeNumber == empNumber) 
      return rt->data;
  if (empNumber < rt->employeeNumber)
    return returnOffset(rt->left, empNumber);
  else
    return returnOffset(rt->right, empNumber);
}

//-=-=-=-=- Private: bst::findSuccessor -=-=-=-
/* Name: binaryFile::findSuccessor
* Last worked on by: Justin Gyolai <justin.gyolai@trojans.dsu.edu>
* Purpose: recursive function to find the successor node.
* Arguments: 1
* bstNode root -- the root node of the tree
* Returns: bstNode*
* bstNode*: node pointer to successor node
*/

bstNode* bst::findSuccessor(bstNode* rt) {
  if (rt->left == NULL)
    return rt;
  else
    return findSuccessor(rt->left);
}

/*
vector<int> bst::storeOffset(int storedOffset) {
  vector<int> offsetStorage;
  offsetStorage.push_back(storedOffset);
  return offsetStorage;
}
*/