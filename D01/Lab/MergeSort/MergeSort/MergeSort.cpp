// MergeSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void merge(int arr[], int low, int mid, int high);
void mergeSort(int arr[], int low, int high);

int main()
{
	int arr[] = {38, 27, 43, 10};
	int n = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void merge(int arr[], int low, int mid, int high) {
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int* L = new int[n1];
	int* R = new int[n2];

	for (int i = 0; i < n1;i++)	L[i] = arr[low + i];
	for (int i = 0; i < n1;i++)	R[i] = arr[mid + i + 1];
	

	int i = 0, j=0,k=low;
	while (i < n1 && j < n2) {
		if (L[i] < R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
	while (i < n1)
		arr[k++] = L[i++];
	while (j < n2)
			arr[k++] = R[j++];
	delete[]L;
	delete[]R;

}
void mergeSort(int arr[], int low, int high) {
	if (low >= high)return;
	int mid = (low + high) / 2;

	mergeSort(arr, low, mid);
	mergeSort(arr, mid+1, high);
	merge(arr, low, mid, high);
}

