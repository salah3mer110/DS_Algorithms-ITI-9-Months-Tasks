// Binary Search Iterative.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int binarySearch(int arr[], int low, int high, int target);
int main()
{
    int arr[] = { 1, 3, 5, 7, 9, 11, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 7;
    int result = binarySearch(arr, 0,n, target);

    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";
}
int binarySearch(int arr[], int low,int high, int target) {
    int mid = (low + high) / 2;
        if (arr[mid] == target)
            return mid;
        if (target > arr[mid])
            binarySearch(arr, mid + 1, high, target);
        else
            binarySearch(arr, low,mid -1 , target);
    return -1;
}
