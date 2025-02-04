#ifndef _BSTNODE_H_
#define	_BSTNODE_H_

// A Node class for Binary Search Tree for int data
class bstNode {
  private:
    
    bstNode* right;     // pointer to right child
    bstNode* left;      // pointer to left child
    int data;           // data for offset
    int employeeNumber; // employee number
  public:
    bstNode(int, int);  //constructor
    virtual ~bstNode(); //destructor

    friend class bst;   //set friend class for private access
};

#endif	/* _BSTNODE_H_ */

