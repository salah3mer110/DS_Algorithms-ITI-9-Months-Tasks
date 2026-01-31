// Bubble Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

void swap(int&, int&);
void bubbleSort(int arr[],int n){
	bool isSorted;
	for(int i=0;(i<n&&!isSorted);i++){
		isSorted=false;
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				swap(arr[j],arr[j+1]);
				isSorted=true;
			}
		}
	}
}

int main()
{
int arr[]={5, 1, 4, 2, 8, 6, 3, 7};

int n=sizeof(arr)/sizeof(arr[0]);
bubbleSort(arr,n);
for (int i = 0; i < n; i++)
{
cout<<" "<<arr[i];
}
cout<<endl;

}
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}
