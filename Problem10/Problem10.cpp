#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<random>

using namespace std;

void BubbleSort(int arr[],int len) {
	//len = number of the elements
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	for (int i = 0; i < len-1 ; i++) {
		for (int j = 1; j < len - i; j++) {
			if (arr[j]<arr[j-1]) {
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void SelectSort(int arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	for (int i = 0; i < len; i++) {
		int min = i;
		for (int j = i; j < len; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void InsertSort(int arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	for (int i = 1; i < len; i++) {        //第一个数字必然有序
		int temp = arr[i];                 //取出第i个数，与前i-1有序列比较
		int j = i - 1;                     //1 2 3 * * * i-1(arr[j]) i(temp) * * len
		while (j >= 0 && arr[j] > temp) {  
			arr[j + 1] = arr[j];           //1 2 3 * * * i-1 i-1 * * len
			j--;
		}
		arr[j + 1] = temp;                
	}
}

void ShellSort(int arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}

	int j = 0;
	int temp = 0;
	int group = len / 2;

	while (group >= 1) {
		for (int i = group; i < len; ++i) {
			temp = arr[i];

			for (j = i - group; j >= 0; j -= group) {
				if (arr[j] <= temp)
					break;
				arr[j + group] = arr[j];
			}

			arr[j + group] = temp;
		}
		group = group / 2;
	}

}



void QuickSort(int L,int R,int arr[]) {
	if (L >= R || L < 0 || R < 0) {
		return;
	}
	
	int left = L, right = R - 1;
	int pivot = arr[left];        //基准柱
	while (left < right) {
		while (left < right && arr[right] >= pivot) {
			right--;
		}
		if (arr[right] < pivot) {
			arr[left] = arr[right];
		}
		while (left < right && arr[left] < pivot) {
			left++;
		}
		if (arr[left] > pivot) {
			arr[right] = arr[left];
		}
	}
	if (left >= right) {
		arr[left] = pivot;
	}
	QuickSort(L, right , arr);
	QuickSort(right + 1, R, arr);
}

void Merge(int arr[],int begin,int end) {

	int* tempArr = new int[end + 1]();
	
	int middle = (begin + end) / 2;
	int p1 = begin;
	int p2 = middle + 1;
	int p = 0;

	while (p1 <= middle && p2 <= end) {
		if (arr[p1] <= arr[p2]) {
			tempArr[p++] = arr[p1++];
		}
		else {
			tempArr[p++] = arr[p2++];
		}
	}

	while (p1 <= middle) {
		tempArr[p++] = arr[p1++];
	}
	while (p2 <= end) {
		tempArr[p++] = arr[p2++];
	}

	for (int i = 0; i <= end; i++) {
		arr[i + begin] = tempArr[i];
	}
	 
	delete[] tempArr;
	return;
}

void MergeSort(int arr[],int begin,int end) {
	if (arr == NULL || end < 0) {
		cerr << "无效参数传递" << endl;
		exit(1);
	}
		
	if (end <= begin)
		return;

	int middle = (end + begin) / 2;
	   
	MergeSort(arr, begin, middle);
	MergeSort(arr, middle + 1, end);
	
	Merge(arr, begin, end);

}


void RandomNumber(int arr[],int len) {
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int>distr(0, 2147483647);

	for (int i = 0; i < len; i++) {
		arr[i] = distr(eng);
	}

	return;
}

int main() {
	srand((unsigned)time(NULL));
	int arr[] = { 165,465,16,123,19,2123,14,54,12,1000,1,564,5,1,4,64,31,32,56,4,56,123,54 };
	//BubbleSort(arr, 22);
	//SelectSort(arr, 23);
	//InsertSort(arr, 23);
	//ShellSort(arr, 23);
	//QuickSort(0, 23, arr);
	
	int len;
	cin >> len;
	int* p = new int[len];
	RandomNumber(p,len);
	BubbleSort(p, len);
	for (int i = 0; i < len; i++)
		cout << "#" << i+1 << " " << p[i] << endl;
	return 0;
}
