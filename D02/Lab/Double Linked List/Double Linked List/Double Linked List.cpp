// Double Linked List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
struct Employee {
	int key;
	int salary;
	string name;
};

class Node {
public:
	Employee data;
	Node* pNext;
	Node* pPrev;
	Node() = default;
	Node(Employee d) :pNext(nullptr), pPrev(nullptr), data(d) {}
};

class DLL {
	Node* pStart;
	Node* pEnd;
public:
	DLL() :pStart(nullptr), pEnd(nullptr) {};
	DLL(DLL& other) {
		pStart = pEnd = nullptr;
		Node* temp = other.pStart;
		while (temp) {
			Node* newNode = new Node(temp->data); // copy Employee data
			insertNode(newNode);                   // insert at head
			temp = temp->pNext;
		}
	}

	DLL(DLL&& other) {
		pStart = other.pStart;
		pEnd = other.pEnd;
		pStart = pEnd = NULL;
	}

	Node* allocNewNode(){
		Employee e;

		
		
		cout << "Enter Name \n";
		cin >> e.name;
		cout << "Enter Key \n";
		cin >> e.key;
		cout << "Enter salary \n";
		cin >> e.salary;

		Node* pNew = new Node(e);

		if (pNew == NULL) exit(0);

		return pNew;
	}

	void insertNode(Node* pNew){
		if (pStart == NULL) {
			pStart = pEnd = pNew;
			return;
		}
		pStart->pPrev = pNew;
		pNew->pNext = pStart;
		pStart = pNew;
	}

	void deleteNode(int id){

		if (pStart == NULL) {
			cout << "List is Empty" << endl;
			return;
		}

		Node* temp = pStart;

		while (temp && temp->data.key!=id) 
			temp = temp->pNext;

		if (!temp) {
			cout << "Node not found\n";
			return;
		}

		if (temp == pStart) {
				pStart = temp->pNext;
				if (pStart)
					pStart->pPrev = NULL;
				else
					pEnd = NULL;
		}
		else if (temp == pEnd) {
			pEnd = temp->pPrev;
			if (pEnd)
				pEnd->pNext = NULL;
			else
				pStart = NULL;
		}
		else {
			temp->pPrev->pNext = temp->pNext;
			temp->pNext->pPrev = temp->pPrev;
		}
		delete temp;
	}

	Node* searchNode(int id){
		if (pStart == NULL) {
			cout << "List is Empty" << endl;
			return NULL;
		}
		Node* temp = pStart;
		while (temp != NULL) {
			if (temp->data.key == id) {
				cout << "Found" << endl;
				return temp;
			}
			temp = temp->pNext;
		}
		return NULL;
	}
	
	void displayNode(int id){
		Node* temp = searchNode(id);
		if (!temp) {
			cout << "Not Found!\n";
			return;
		}
		cout << "Name: " << temp->data.name << endl;
		cout << "Key: " << temp->data.key << endl;
		cout << "Salary: " << temp->data.salary << endl;
	}
	
	void displayAll(){
		Node* temp = pStart;
		while (temp != NULL) {
			cout << temp->data.name << endl;
			cout << temp->data.key << endl;
			cout << temp->data.salary << endl;
			temp = temp->pNext;
		}
	}
	
	int nodeNum(){
		Node* temp = pStart;
		int count = 0;
		while (temp) {
			count++;
			temp = temp->pNext;
		}
		return count;

	}

	DLL& operator= (DLL& newDLL) {
		if (this == &newDLL)
			return *this;


		Node* temp = pStart;
		while (temp) {
			Node* next = temp->pNext;
			delete temp;
			temp = next;
		}
		pStart = pEnd = NULL;

		Node* temp = newDLL.pStart;

		while (temp) {
			insertNode(new Node(temp->data));
			temp = temp->pNext;
		}
		return *this;
	}

	DLL& operator= (DLL&& newDLL) {
		if (this == &newDLL)
			return *this;


		Node* temp = pStart;
		while (temp) {
			Node* next = temp->pNext;
			delete temp;
			temp = next;
		}
		pStart = pEnd = NULL;

		pStart = newDLL.pStart;
		pEnd = newDLL.pEnd;

		newDLL.pStart = newDLL.pEnd = NULL;

		return *this;
	}

	int& operator[](int index) {
		if (index < 0)
			throw out_of_range("Index out of range");

		
		Node* temp = pStart;
		int i = 0;
		while (temp && i < index) {
			temp = temp->pNext;
			i++;
		}

		if(!temp)
			throw out_of_range("Index out of range");

		return temp->data.key;
	}

	~DLL() {
		Node* temp = pStart;
		while (temp) {
			Node* next = temp->pNext; 
			delete temp;
			temp = next;              
		}
		pStart = pEnd = nullptr;
	}
};

int main() {
	DLL list;

	// Insert some nodes
	Node* n1 = list.allocNewNode();
	list.insertNode(n1);

	Node* n2 = list.allocNewNode();
	list.insertNode(n2);

	Node* n3 = list.allocNewNode();
	list.insertNode(n3);

	cout << "\nAll nodes in the list:\n";
	list.displayAll();

	// Delete a node
	int keyToDelete;
	cout << "\nEnter key of node to delete: ";
	cin >> keyToDelete;
	list.deleteNode(keyToDelete);

	cout << "\nList after deletion:\n";
	list.displayAll();

	// Search a node
	int keyToSearch;
	cout << "\nEnter key of node to search: ";
	cin >> keyToSearch;
	Node* found = list.searchNode(keyToSearch);
	if (found) {
		cout << "Found Node: " << found->data.name << " "
			<< found->data.key << " " << found->data.salary << endl;
	}
	else {
		cout << "Node not found\n";
	}

	cout << "\nTotal nodes in the list: " << list.nodeNum() << endl;

	return 0;
}


