
#include <iostream>
using namespace std;
struct Employee {
	int key;
	//int salary;
	//string name;
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
public:
	Node* pStart;
	Node* pEnd;
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
	Node* allocNewNode() {
		Employee e;

		//cout << "Enter Name \n";
		//cin >> e.name;
		cout << "Enter Key \n";
		cin >> e.key;
		//cout << "Enter salary \n";
		//cin >> e.salary;

		Node* pNew = new Node(e);

		if (pNew == NULL) exit(0);

		return pNew;
	}

	void insertNode(Node* pNew) {
		if (pStart == NULL) {
			pStart = pEnd = pNew;
			return;
		}
		pStart->pPrev = pNew;
		pNew->pNext = pStart;
		pStart = pNew;
	}

	void deleteNode(int id) {

		if (pStart == NULL) {
			cout << "List is Empty" << endl;
			return;
		}

		Node* temp = pStart;

		while (temp && temp->data.key != id)
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

	Node* searchNode(int id) {
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

	void displayNode(int id) {
		Node* temp = searchNode(id);
		if (!temp) {
			cout << "Not Found!\n";
			return;
		}
		//cout << "Name: " << temp->data.name << endl;
		cout << "Key: " << temp->data.key << endl;
		//cout << "Salary: " << temp->data.salary << endl;
	}

	void displayAll() {
		Node* temp = pStart;
		while (temp != NULL) {
			//cout << temp->data.name << endl;
			cout << temp->data.key << endl;
			//cout << temp->data.salary << endl;
			temp = temp->pNext;
		}
	}

	int nodeNum() {
		Node* temp = pStart;
		int count = 0;
		while (temp) {
			count++;
			temp = temp->pNext;
		}
		return count;

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

class StackDLL:public DLL {
public:
	void push(Node* pNew){
		if (pStart == NULL) {
			pStart = pEnd = pNew;
			return;
		}
		pStart->pPrev = pNew;
		pNew->pNext = pStart;
		pStart = pNew;
	}
	Node* pop() {
		if (pStart == NULL)
			return NULL;
		Node* temp = pStart;
		pStart = pStart->pNext;
		if (pStart)
			pStart->pPrev = NULL;
		else
			pEnd = NULL; 

		temp->pNext = NULL;

		return temp;
	}
	Node* peak(){
		return pStart;
	}
};


int main()
{
	StackDLL st;

	cout << "PUSH 3 EMPLOYEES\n";
	st.push(st.allocNewNode());
	st.push(st.allocNewNode());
	st.push(st.allocNewNode());

	cout << "DISPLAY ALL\n";
	st.displayAll();

	cout << "PEAK\n";
	Node* top = st.peak();
	if (top) {
		cout << top->data.key << endl;
	}

	cout << "POP\n";
	Node* popped = st.pop();
	if (popped) {
		cout << popped->data.key << endl;
		delete popped;
	}

	cout << "DISPLAY AFTER POP\n";
	st.displayAll();

	cout << "POP ALL\n";
	while (st.peak()) {
		Node* n = st.pop();
		delete n;
	}

	cout << "STACK SIZE\n";
	cout << st.nodeNum() << endl;

	return 0;
}

