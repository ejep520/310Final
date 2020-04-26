#include <iostream>
using namespace std;

#include "bstNode.h"

bstNode::bstNode(int data, int empNumber) {
  this->data = data; 
  this->employeeNumber = empNumber;
  right = left = NULL;
}

bstNode::~bstNode() {

}
