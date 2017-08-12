#include <iostream>
#include "a3_avl_tree.hpp"
#include "a3_binary_search_tree.hpp"
using namespace std;


//AVL Tree Insert
bool AVLTree::insert(BinarySearchTree::DataType val){
	bool removeSuccess = BinarySearchTree::insert(val);
	if (!removeSuccess) return false; //Check for generic insert success
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode()); //primary avl balance update call
	balanceAVLTree(BinarySearchTree::getRootNode());
	return true;
}

//AVL Tree Remove
bool AVLTree::remove(BinarySearchTree::DataType val){
	bool removeSuccess = BinarySearchTree::remove(val);
	if (!removeSuccess) return false; //Check for generic remove success
	BinarySearchTree::updateNodeBalance(BinarySearchTree::getRootNode()); //primary avl balance update call
	balanceAVLTree(BinarySearchTree::getRootNode());
	return true;
}

//Single Left Rotation
void singleLeft (BinarySearchTree::Node* n){
	BinarySearchTree::DataType temp;
	temp = n->val;
	n->val=n->right->val;
	n->right->val=temp;
	
	BinarySearchTree::Node* temp1;
	temp1 = n->left;
	n->left = n->right;
	n->right = n->left->right;
	n->left->right = n->left->left;
	n->left->left = temp1; 
	
	temp1=NULL;
}

//Single Right Rotation
void singleRight (BinarySearchTree::Node* n){
	BinarySearchTree::DataType temp;
	temp = n->val;
	n->val = n->left->val;
	n->left->val = temp;
	
	BinarySearchTree::Node* temp1;
	temp1 = n->right;
	n->right = n->left;
	n->left = n->right->left;
	n->right->left = n->right->right;
	n->right->right = temp1;
	
	temp1=NULL;
}

//Double Left Right Rotation
void doubleLR (BinarySearchTree::Node* n){
	BinarySearchTree::DataType temp;
	temp = n->val;
	n->val = n->left->right->val;
	n->left->right->val = temp;
	
	BinarySearchTree::Node* temp1;
	temp1 = n->right;
	n->right = n->left->right;
	n->left->right = n->right->left;
	n->right->left = n->right->right;
	n->right->right = temp1;
	
	temp1=NULL;
}

//Double Right Left Rotation
void doubleRL (BinarySearchTree::Node* n){
	BinarySearchTree::DataType temp;
	temp = n->val;
	n->val = n->right->left->val;
	n->right->left->val = temp;
	
	BinarySearchTree::Node* temp1;
	temp1 = n->left;
	n->left = n->right->left;
	n->right->left = n->left->right;
	n->left->right = n->left->left;
	n->left->left = temp1;
	
	temp1=NULL;
}

//Function to determine which rotation (if any) to carry out to balance the tree 
void AVLTree::balanceAVLTree (BinarySearchTree::Node* n){
	if (n){
		//bottom up reccursive calls
		balanceAVLTree(n->left);
		balanceAVLTree(n->right);
		
		BinarySearchTree::updateNodeBalance(n); //repititively update node balance
		if (n->avlBalance<-1){ //Left Balance condition
			if(n->right->avlBalance<=0) singleLeft(n); //0 included because one side may contain balanced subtree
			else if (n->right->avlBalance>=1) doubleRL(n);
		}	
		else if (n->avlBalance>1){ //Right balance condition
			if(n->left->avlBalance>=0) singleRight(n); //0 included because one side may contain balanced subtree
			else if (n->left->avlBalance<=-1) doubleLR(n);
		}
	}
}
