#include <iostream>
#include "a3_binary_search_tree.hpp"
using namespace std;

//Node Constructor
BinarySearchTree::Node::Node(DataType newval){
	val=newval;
	left=NULL;
	right=NULL;
	avlBalance=0;
}

// Default constructor to initialize the root.
BinarySearchTree::BinarySearchTree(){
	root_=NULL;
	size_=0;
}

//Helper Function: Post Order Memory Deallocation 
void destroyTree(BinarySearchTree::Node* leaf){
	if (leaf){
		destroyTree(leaf->left);
		destroyTree(leaf->right);
		delete leaf;
	}
}
// Destructor of the class BinarySearchTree. It deallocates the memory 
// space allocated for the binary search tree. 
BinarySearchTree::~BinarySearchTree(){
	destroyTree(root_);
}

// Returns the number of nodes in the tree. 
unsigned int BinarySearchTree::size() const{
	return size_;
}

// Returns the maximum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::max() const{
	Node* currNode= root_;
	while (currNode->right){
		currNode= currNode->right;
	}
	return currNode->val;
}

// Returns the minimum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::min() const{
	Node* currNode=root_;
	while (currNode->left){
		currNode= currNode->left;
	}
	return currNode->val;
}

//Reccursive Depth Return
BinarySearchTree::DataType treeDepth(BinarySearchTree::Node* topNode){
	if (topNode==NULL) return -1;
	else return 1+ max(treeDepth(topNode->left), treeDepth(topNode->right));
}

// Returns the maximum depth of the tree. A tree with only the root node has a 
// depth of 0.
unsigned int BinarySearchTree::depth() const{
	return treeDepth(root_); //depth helper function call
}

//Helper Function: In Order Print Call
void printTree(BinarySearchTree::Node* treeRoot){
	if (treeRoot == NULL) return;
	printTree(treeRoot->left);
	cout<< treeRoot->val<<endl;
	printTree(treeRoot->right);
}

//Tree print function
void BinarySearchTree::print() const{
	printTree(root_); //Helper function Call
}

// Returns true if a node with the value val exists in the tree; otherwise, 
// it returns false.
bool BinarySearchTree::exists(DataType val) const{
	if (size_==0) return false;
	BinarySearchTree::Node* visitNode = root_;
	while (visitNode){
		if (visitNode->val==val) return true;
		else if (visitNode->val<val) visitNode= visitNode->right;
		else visitNode= visitNode->left;
	}
	if (visitNode==NULL) return false;
	if (visitNode->val==val) return true;
	else return false;
	 
}

// Returns a pointer to the root node
BinarySearchTree::Node* BinarySearchTree::getRootNode(){
	return root_;
}

// Returns the root node pointer address
BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress(){
	return &root_;
}

// Inserts the value val into the tree. Returns false if val already exists in 
// the tree, and true otherwise.
bool BinarySearchTree::insert(DataType val){
	BinarySearchTree::Node* key= new BinarySearchTree::Node(val);
	if (root_==NULL){ //Empty tree insert case
		root_=key;
		size_++;
		key=NULL;
		return true;
	}
	BinarySearchTree::Node* visitNode = root_;
	BinarySearchTree::Node* visitParent = NULL;
	while (visitNode){
		if (visitNode->val==val) return false; //exit if value already exists in tree
		else if (visitNode->val>val) {
			visitParent=visitNode;
			visitNode=visitNode->left; //Moving visitNode pointer left
		}
		else{
			visitParent=visitNode;
			visitNode=visitNode->right; //moving visitNode pointer right
		}
	}
	if (visitParent->val>val) visitParent->left=key; //left insert condition
	else visitParent->right=key; //right insert condition
	size_++; 
	key=NULL;
	visitParent=NULL;
	return true;		
}

// Removes the node with the value val from the tree. Returns true if successful, 
// and false otherwise.
bool BinarySearchTree::remove(DataType val){
	if ((size_==0)||(size_==1 && root_->val!=val)) return false;
	BinarySearchTree::Node* visitNode = root_;
	BinarySearchTree::Node* visitParent = visitNode;
	while ((visitNode)&&(visitNode->val!=val)&&(visitNode->left || visitNode->right)){ //Iterate through tree to check for existance of required node
		visitParent=visitNode;
		if (visitNode->val>val) visitNode=visitNode->left;
		else visitNode= visitNode->right;
	}
	if (!visitNode) return false;
	if (val!=visitNode->val) return false; //exit function if desired node does not exist in tree
	if (visitNode->left==NULL && visitNode->right==NULL){ //Case 1: If desired Node if a leaf Node
		if (visitNode==root_) root_=NULL;
		else if (visitParent->left==visitNode) visitParent->left = NULL;
		else visitParent->right=NULL;
		delete visitNode;
	} //Case 2: If desired node has only one child
	else if (visitNode->left!=NULL && visitNode->right==NULL){ //Case 2 a)
		if (visitNode==root_) root_=root_->left;
		else if(visitParent->left==visitNode) visitParent->left= visitNode->left;
		else visitParent->right=visitNode->left;
		visitNode->left=visitNode->right;
		delete visitNode;
	}
	else if (visitNode->left==NULL && visitNode->right!=NULL){ //Case 2 b)
		if (visitNode==root_) root_=root_->right;
		else if(visitParent->right==visitNode) visitParent->right= visitNode->right;
		else visitParent->left=visitNode->right;
		visitNode->right=visitNode->left;
		delete visitNode;
	}
	else { //Case 3: The desired node has two child nodes
		BinarySearchTree::Node* maxNode = visitNode->left;
		visitParent = maxNode;
		while (maxNode->right){
			visitParent=maxNode;
			maxNode=maxNode->right;
		}
		if (maxNode->left==NULL){
			visitParent->right=NULL; 
			visitNode->val=maxNode->val; 
			if (visitNode->left==maxNode) visitNode->left=NULL; //if the max value in the left subtree of the desired node is the node left of the desired node itself
		}
		else { //if maxNode has a child
			if (visitParent==maxNode) visitNode->right = visitParent->right; //if the max value in the left subtree of the desired node is the node left of the desired node itself
			else visitParent->right=maxNode->left;
			visitNode->val=maxNode->val;
		}
		delete maxNode;
		maxNode=NULL;
	}
	visitNode=NULL;
	visitParent=NULL;
	size_--;
	return true;
}

// Update the avlBalance starting at node n reccursively
void BinarySearchTree::updateNodeBalance(Node* n){
	if (n){	
		n->avlBalance = (treeDepth(n->left)-treeDepth(n->right));
		updateNodeBalance(n->left);
		updateNodeBalance(n->right);
	}
}


