#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<random>

using namespace std;

void BubbleSort(int arr[], int len) {
	//len = number of the elements
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	for (int i = 0; i < len - 1; i++) {
		for (int j = 1; j < len - i; j++) {
			if (arr[j] < arr[j - 1]) {
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void ImprovedBubbleSort(int arr[], int len) {
	//len = number of the elements
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	bool exchange;
	int newPosition, position = len - 1;
	for (int i = 1; i < len ; i++) {
		exchange = false;
		newPosition = 0;
		for (int j = len - 1; j >= i; j--) {
			if (arr[j] < arr[j - 1]) {
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				exchange = true;
				newPosition = j;
			}
		}
		if (exchange == false) {
			return;
		}
		position = newPosition;
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



void QuickSort(int L, int R, int arr[]) {
	if (L >= R || L < 0 || R < 0) {
		return;
	}

	int left = L, right = R - 1;
	int pivot = arr[left];      //基准柱
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
	QuickSort(L, right, arr);
	QuickSort(right + 1, R, arr);
}

void Merge(int arr[], int begin, int end) {

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

	for (int i = 0; i <= end - begin; i++) {
		arr[i + begin] = tempArr[i];
	}

	delete[] tempArr;
	return;
}

void MergeSort(int arr[], int begin, int end) {
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

//下沉调整
void DownAdjust(int arr[], int parentIndex, int len) {
	int temp = arr[parentIndex];
	int childIndex = parentIndex * 2 + 1;

	while (childIndex < len) {
		if (childIndex + 1 < len && arr[childIndex + 1] > arr[childIndex]) {
			childIndex++;
		}

		if (temp > arr[childIndex]) {
			break;
		}

		arr[parentIndex] = arr[childIndex];
		parentIndex = childIndex;
		childIndex = 2 * parentIndex + 1;
	}

	arr[parentIndex] = temp;


}


void HeapSort(int arr[], int len) {
	for (int i = len / 2; i >= 0; i--) {
		DownAdjust(arr, i, len);
	}

	for (int i = len - 1; i > 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		DownAdjust(arr, 0, i);
	}
}

//计数排序
void CountSort(int arr[], int len, int exp) {
	int* result = new int[len];
	int bucket[10] = { 0 };

	for (int i = 0; i < len; i++) {
		bucket[(arr[i] / exp) % 10]++;
	}
	for (int i = 1; i < 10; i++) {
		bucket[i] = bucket[i] + bucket[i - 1];
	}
	for (int i = len - 1; i >= 0; i--) {
		int tempEXP = (arr[i] / exp) % 10;
		result[bucket[tempEXP] - 1] = arr[i];
		bucket[tempEXP]--;
	}
	for (int i = 0; i < len; i++) {
		arr[i] = result[i];
	}
	delete[]result;
	//memcpy(arr, result, len * sizeof(int));
}

//基数排序
void RadixSort(int arr[], int len) {
	int max = 0l;
	for (int i = 0; i < len; i++) {
		max = max > arr[i] ? max : arr[i];
	}
	for (int exp = 1; max / exp > 0; exp *= 10) {
		CountSort(arr, len, exp);
	}
}

void RandomNumber(int arr[], int len) {
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int>distr(0, 2147483647);

	for (int i = 0; i < len; i++) {
		arr[i] = distr(eng);
	}

	return;
}

void Menu() {
	cout << "**                排序算法比较                   **" << endl;
	cout << "==================================================" << endl;
	cout << "**                1 --- 冒泡排序                 **" << endl;
	cout << "**                2 --- 选择排序                 **" << endl;
	cout << "**                3 --- 直接插入排序             **" << endl;
	cout << "**                4 --- 希尔排序                 **" << endl;
	cout << "**                5 --- 快速排序                 **" << endl;
	cout << "**                6 --- 堆排序                   **" << endl;
	cout << "**                7 --- 归并排序                 **" << endl;
	cout << "**                8 --- 基数排序                 **" << endl;
	cout << "**                9 --- 退出程序                 **" << endl;
	cout << "==================================================" << endl;
}

int main() {
	system("chcp 65001");
	Menu();
	int num;
	cout << "请输入要产生的随机数的个数:";
	cin >> num;
	int* arr = new int[num];
	RandomNumber(arr, num);
	clock_t start, finish;
	start = clock();
	//ImprovedBubbleSort(arr,num);//冒泡排序
	//SelectSort(arr, num);//选择排序
	//InsertSort(arr, num);//直接插入排序
	//ShellSort(arr, num);//希尔排序
	//QuickSort(0, num, arr);//快速排序
	//HeapSort(arr, num);//堆排序
	MergeSort(arr, 0, num-1);
	//RadixSort(arr, num);
	finish = clock();
	double deltaTime = (double)((double)finish - (double)start) / CLOCKS_PER_SEC;
	std::cout << deltaTime << endl;
	/*for (int i = 0; i < num; i++) {
		cout <<i+1<<" "<< arr[i] << endl;
	}*/
	delete[]arr;
	return 0;
}