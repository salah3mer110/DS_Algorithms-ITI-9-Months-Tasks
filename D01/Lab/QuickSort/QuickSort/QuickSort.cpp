// QuickSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void swap(int&, int&);
int main()
{
	int arr[] = { 8, 3, 1, 7, 0, 10, 2 };
	int n = sizeof(arr)/ sizeof(arr[0]);

	quickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}
int partition(int arr[],int low,int high) {
	int pivot = arr[high];
	int left = low - 1;
	for (int i = low;i <= high-1;i++) {
		if (arr[i] < pivot) {
				left++;
				swap(arr[i], arr[left]);
		}
	}
	swap(arr[++left], arr[high]);
	return left;
}
void quickSort(int arr[],int low,int high) {
	if (low < high) {
		int pivotIndex = partition(arr, low, high);
		quickSort(arr, low, pivotIndex-1);
		quickSort(arr, pivotIndex+1,high);
	}
}
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}
