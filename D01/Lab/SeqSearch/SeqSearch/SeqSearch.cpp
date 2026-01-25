// SeqSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int seqSearch(int arr[], int n, int target);
int main()
{
	int arr[] = { 1,2,3,5,6,7 };
	int n = sizeof(arr);
	cout << seqSearch(arr, n, 3) << endl;
	cout << seqSearch(arr, n, 4)<<endl;
}
int seqSearch(int arr[], int n, int target) {
	for (int i = 0; i < n;i++) {
		if (arr[i] == target)
			return i;
		if (arr[i] > target)
			return -1;
	}
	return -1;
}