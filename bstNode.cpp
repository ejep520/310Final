#include <iostream>
using namespace std;

#include "bstNode.h"

bstNode::bstNode(int data) {
  this->data = data; 
  right = left = NULL;
}

bstNode::~bstNode() {
}
