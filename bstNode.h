#ifndef _BSTNODE_H_
#define	_BSTNODE_H_

// A Node class for Binary Search Tree for "int" data
class bstNode {
  private:
    bstNode* right; // pointer to right child
    bstNode* left; // pointer to left child
    double data;
  public:
    bstNode(int data);
    virtual ~bstNode();

    friend class bst;
};

#endif	/* _BSTNODE_H_ */

