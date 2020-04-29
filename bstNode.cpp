#include <iostream>
using namespace std;

#include "bstNode.h"

/************************* PUBLIC: CONSTRUCTOR *************************/
bstNode::bstNode(int data, int empNumber) {
  this->data = data; 
  this->employeeNumber = empNumber;
  right = left = NULL;
}

/************************* PUBLIC: DESTRUCTOR *************************/
bstNode::~bstNode() {

}
