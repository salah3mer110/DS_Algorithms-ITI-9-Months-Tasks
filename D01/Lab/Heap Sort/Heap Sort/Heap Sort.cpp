// Heap Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
void swap(int&, int&);
void makeHeap(int arr[], int n, int i);
void heapSort(int arr[], int n);
int main()
{
	int arr[] = {9, 4, 3, 8, 10, 2, 5};
	int n = sizeof(arr) / sizeof(arr[0]);
	heapSort(arr,n);

	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
}
void makeHeap(int arr[], int n, int root) {
	int max = root;

	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < n && arr[max] < arr[left])
		max = left;
	if (right < n && arr[max] < arr[right])
		max = right;

	if (max != root) {
		swap(arr[max], arr[root]);
		makeHeap(arr, n, max);
	}
}
void heapSort(int arr[],int n){
	for (int i = n / 2 - 1; i >= 0; i--)
		makeHeap(arr, n, i);

	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		makeHeap(arr, i, 0);
	}
}

void swap(int&x, int&y) {
	int temp = x;
	x = y;
	y = temp;
}