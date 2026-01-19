// Binary Search Iterative.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int binarySearch(int arr[],int n,int target);
int main()
{
    int arr[] = { 1, 3, 5, 7, 9, 11, 15 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 7;
    int result = binarySearch(arr, n, target);

    if (result != -1)
        cout << "Found at index " << result;
    else
        cout << "Not found";
}
int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;   
    int mid = (low + high) / 2;
    while (low <= high) {
        if (arr[mid]==target)
            return mid;
        if (target > arr[mid])
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return -1;
}
