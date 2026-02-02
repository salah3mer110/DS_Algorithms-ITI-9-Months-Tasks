// Dynamic Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class DynamicArray {
    int size;
    int capacity;
    int* objects;
protected:
    void resize(int newCapacity){
        if (newCapacity < size)
            return;
        int* newArr = new int[newCapacity];

        for (int i = 0;i < size;i++)
            newArr[i] = objects[i];
        
        delete []objects;
        
        capacity = newCapacity;
        objects = newArr;
    }
    void shrink(){
        if (size < capacity)
            resize(size);
    }
public:
    DynamicArray() :size(0), capacity(1), objects(new int[1]) {};
    DynamicArray(int s, int c, int* arr) :size(s), capacity(c), objects(arr) {};
    DynamicArray(DynamicArray& arr) {
        size = arr.size;
        capacity = arr.capacity;
        objects = new int[capacity];

        for (int i = 0;i < size;i++)
            objects[i] = arr.objects[i];
    }

    DynamicArray & operator=(DynamicArray & arr){
        if (this != &arr) {
            delete[]objects;
            size = arr.size;
            capacity = arr.capacity;
            objects = new int[capacity];

            for (int i = 0;i < size;i++)
                objects[i] = arr.objects[i];
        }
        return *this;
    }

    int & operator[](int index){
        if (index > size)
            throw out_of_range("out of range!");
        return objects[index];
    }

    void addEl(int value){
        if (size >= capacity) {
            resize(capacity * 2);
        }
        objects[size++] = value;
    }
    int deleteEl() {
        if (size == 0)
            throw runtime_error("Array is empty");
        return objects[--size];
    }
    void displayAll(){
        if (size == 0){
            cout << "Empty array!" << endl;
            return;
        }


        for (int i = 0;i < size;i++)
            cout << objects[i] << " ";
        cout << endl;
    }

    int getCapacity() {
        return capacity;
    }
    int getSize(){
        return size;
    }
    ~DynamicArray() {
        delete[]objects;
    }
};


int main()
{
        DynamicArray arr;

        arr.addEl(10);
        arr.addEl(20);
        arr.addEl(30);
        arr.addEl(40);

        cout << "Array elements: ";
        arr.displayAll();

        cout << "Size: " << arr.getSize() << endl;
        cout << "Capacity: " << arr.getCapacity() << endl;

        cout << "Element at index 2: " << arr[2] << endl;

        arr[2] = 99;
        cout << "After modification: ";
        arr.displayAll();

        int removed = arr.deleteEl();
        cout << "Removed element: " << removed << endl;

        cout << "After deletion: ";
        arr.displayAll();

        DynamicArray copyArr(arr);
        cout << "Copied array: ";
        copyArr.displayAll();

        DynamicArray assignedArr;
        assignedArr = arr;
        cout << "Assigned array: ";
        assignedArr.displayAll();

        return 0;
    }

