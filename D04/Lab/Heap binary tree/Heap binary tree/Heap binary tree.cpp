// Heap binary tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>

using namespace std;
class Node {
public:
	int key;
	Node* pLeft;
	Node* pRight;
	Node* pParent;

	Node() = default;
	Node(int k, Node* l, Node* r) :key(k), pLeft(l), pRight(r){}
};
class HBT {
	Node* root;
public:
	HBT():root(nullptr){}

	Node* allocNewNode(){
		Node* pNew = new Node();
		if (pNew == NULL)
			exit(0);
		
		pNew->pLeft = pNew->pRight =pNew->pParent= nullptr;	

		cout << "Enter key" << endl;
		cin >> pNew->key;

		return pNew;
	}

	void insertNode(Node*& pRoot,Node* pNew){
		if (pRoot == nullptr) {
			pRoot = pNew;
			return;
		}

		queue<Node*> q;
		q.push(pRoot);
		
		while (!q.empty()) {
		
			Node* temp = q.front();
			q.pop();

			if (!temp->pLeft) {
				temp->pLeft = pNew;
				pNew->pParent = temp;
				break;
			}
			else
				q.push(temp->pLeft);

			if (!temp->pRight) {
				temp->pRight = pNew;
				pNew->pParent = temp;
				break;
			}
			else
				q.push(temp->pRight);
		}
		heapifyUp(pNew);
	}

	void heapifyUp(Node* node){
		while (node->pParent && node->key < node->pParent->key) {
			swap(node->key, node->pParent->key);
			node = node->pParent;
		}
	}

	void deleteNode(Node*& pRoot) {
		if (pRoot == NULL)
			return;

		Node* lastNode = getLastNode(pRoot);

		if (pRoot == lastNode)
		{
			delete pRoot;
			pRoot = NULL;
			return;
		}

		pRoot->key = lastNode->key;

		if (lastNode->pParent->pLeft == lastNode)
			lastNode->pParent->pLeft = NULL;
		else
			lastNode->pParent->pRight = NULL;


		delete lastNode;

		heapifyDown(pRoot);
	}


	void heapifyDown(Node* node) {
		while (node) {
			Node* min = node;
			if (node->pLeft && node->pLeft->key < min->key)
				min = node->pLeft;
			if (node->pRight && node->pRight->key < min->key)
				min = node->pRight;

			if (node != min) {
				swap(node->key, min->key);
				node = min;
			}
			else
				break;

		}

	}

	Node* getLastNode(Node* pRoot) {
		if (pRoot == NULL)
			return NULL;

		queue<Node*> q;
		q.push(pRoot);

		Node* temp = nullptr;

		while (!q.empty()) {
			temp = q.front();
			q.pop();

			if (temp->pLeft) q.push(temp->pLeft);
			if (temp->pRight) q.push(temp->pRight);
		}
		return temp;
	}

	void view(Node*pRoot) {
		if (pRoot == NULL) return;

		queue<Node*> q;
		q.push(pRoot);

		while (!q.empty()) {
			Node* temp = q.front();
			q.pop();

			cout << temp->key << endl;

			if (temp->pLeft) q.push(temp->pLeft);
			if (temp->pRight) q.push(temp->pRight);
		}
	}
};

int main() {
	HBT heap;
	Node* root = nullptr;
	heap.insertNode(root, heap.allocNewNode());
	heap.insertNode(root, heap.allocNewNode());
	heap.insertNode(root, heap.allocNewNode());
	heap.insertNode(root, heap.allocNewNode());
	heap.insertNode(root,heap.allocNewNode());
	
	cout << "\nHeap\n";
	heap.view(root);


	heap.deleteNode(root);
	cout << "\nHeap\n";
	heap.view(root);


	return 0;
}

