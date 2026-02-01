// Binary Search Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class Node {
public:
	int key;
	Node* left;
	Node* right;
	int height;
	Node() = default;
	Node(int k, Node* l, Node* r) :key(k), left(l), right(r) {}
};
class BST {
	Node* root;
public:
	BST() = default;
	BST(Node* r) :root(r) {};
	
	Node* allocNewNode(){
		Node* pNew = new Node();
		if (pNew == NULL)
			exit(0);
		pNew->left = pNew->right = NULL;
		pNew->height = 1;
		cout << "Enter new data\n";
		cin >> pNew->key;
		return pNew;
	}
	
	void insertNode(Node* &pRoot,Node* pNew){
		if (pRoot == NULL) {
			pRoot = pNew;
			return;
		}

		if (pNew->key < pRoot->key)
			insertNode(pRoot->left, pNew);
		else if (pNew->key > pRoot->key)
			insertNode(pRoot->right, pNew);
		else
			return;

		pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;
		
		int balance = getBalance(pRoot);

		//case LL  
		if (balance > 1 && pNew->key < pRoot->left->key)
			rightRotate(pRoot);
		
		//case RR  
		else if (balance < -1 && pNew->key > pRoot->right->key)
			leftRotate(pRoot);

		//case LR
		else if (balance > 1 && pNew->key > pRoot->left->key) {
			leftRotate(pRoot->left);
			rightRotate(pRoot);
		}

		//case RL
		else if (balance < -1 && pNew->key < pRoot->right->key) {
			rightRotate(pRoot->right);
			leftRotate(pRoot);
		}
	}
	
	//void insertNode(Node *pRoot,Node *leaf,Node* pNew){	}
	
	void treeTraverse(Node *pRoot){
		if (pRoot == NULL) return;
		treeTraverse(pRoot->left);
		cout << pRoot->key << endl;
		treeTraverse(pRoot->right);
	}
	
	int countNodes(Node *pRoot) {
		if (pRoot)
		return countNodes(pRoot->left) + 1 + countNodes(pRoot->right);
		return 0;
	}
	
	int countLevels(Node *pRoot){
		if (pRoot) {
			int countLeft = countLevels(pRoot->left);
			int countRight= countLevels(pRoot->right);
			return max(countLeft, countRight) +1;
		}
		return 0;
	}
	
	void deleteNode(Node* &pRoot,int key){
		if (pRoot==NULL) return;
		if (pRoot->key > key)
			deleteNode(pRoot->left, key);
		else if (pRoot->key < key)
			deleteNode(pRoot->right, key);
		else
			removeNode(pRoot);
	}
	
	void removeNode(Node *&pRoot){
		Node* pDelete = pRoot;
		if (pRoot == NULL)return;
		if (pRoot->left == NULL) {
			pRoot = pRoot->right;
			delete pDelete;
		}
		else if (pRoot->right == NULL) {
			pRoot = pRoot->left;
			delete pDelete;
		}
		else {
			int value=getMax(pRoot);
			pRoot->key = value;
			deleteNode(pRoot->left, value);
		}
		if (pRoot ) {
			pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;

			int balance = getBalance(pRoot);


			// LL
			if (balance > 1 && getBalance(pRoot->left) >= 0)
				rightRotate(pRoot);

			// LR
			if (balance > 1 && getBalance(pRoot->left) < 0) {
				leftRotate(pRoot->left);
				rightRotate(pRoot);
			}

			// RR
			if (balance < -1 && getBalance(pRoot->right) <= 0)
				leftRotate(pRoot);

			// RL
			if (balance < -1 && getBalance(pRoot->right) > 0) {
				rightRotate(pRoot->right);
				leftRotate(pRoot);
			}
		}
	}
	
	int getMax(Node *pRoot) {
		while (pRoot->right != NULL)
			pRoot = pRoot->right;
		return pRoot->key;
	}
	
	//search
	void search(Node* pRoot, int data) {
		if (pRoot == NULL) {
			cout << "Not Found, The Tree is Empty!\n";
			return;
		}
		else if (data == pRoot->key)
			cout << "The Node U R searching is Found!\n";
		else if (data < pRoot->key)
			search(pRoot->left, data);
		else
			search(pRoot->right, data);
	}

	//check if balanced 
	int getHeight(Node* pRoot){
		if (pRoot == NULL)
			return 0;
		return pRoot->height;
	}
	int getBalance(Node* pRoot) {
		if (pRoot == NULL)
			return 0;
		return getHeight(pRoot->left) - getHeight(pRoot->right);
	}
	
	//maintain balance
	void rightRotate(Node* &pRoot){
		Node* x = pRoot->left;
		Node* T2 = x->right;

		x->right = pRoot;
		pRoot->left = T2;

		pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;
		x->height = max(getHeight(x->left), getHeight(x->right)) +1;

		pRoot = x;
	}
	void leftRotate(Node* &pRoot) {
		Node* x = pRoot->right;
		Node* T2 = x->left;

		x->left = pRoot;
		pRoot->right = T2;
	
		pRoot->height = max(getHeight(pRoot->left), getHeight(pRoot->right)) + 1;
		x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	
		pRoot = x;
	}

};
int main()
{
	BST tree;
	Node* root = nullptr;

	tree.insertNode(root, tree.allocNewNode());
	tree.insertNode(root, tree.allocNewNode());
	tree.insertNode(root, tree.allocNewNode());
	tree.insertNode(root, tree.allocNewNode());

	tree.treeTraverse(root);

	int key;
	cout << "Enter key to remove Node" << endl;
	cin >> key;
	tree.deleteNode(root, key);

	tree.treeTraverse(root);

	cout << "Enter key to Search Node" << endl;
	cin >> key;
	tree.search(root, key);
	tree.treeTraverse(root);

	cout<<tree.countNodes(root)<<endl;
}
