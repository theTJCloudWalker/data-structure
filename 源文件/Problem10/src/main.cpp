#include<iostream>
#include<stdlib.h>
#include<time.h>//for clock_t用于计算时间
#include<random>//for random_device
#include<cstring>//for memcpy()用于迅速复制数组
#include<iomanip>

using namespace std;

long long int exchangeCount = 0;
long long int compareCount = 0;

//冒泡排序
template<class T>
void BubbleSort(T arr[], int length) {
	if (arr == NULL || length <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}

	exchangeCount = 0;
	compareCount = 0;

	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				exchangeCount++;
			}
			compareCount++;
		}
	}
}

template<class T>
void BubbleSort1(T arr[], int length) {
	if (arr == NULL || length <= 0) {
		cerr << "无效参数传递:" << endl;
		return;
	}

	bool exchange = true;
	for (int i = 0; i < length - 1 && exchange; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			exchange = 0;
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				exchange = 1;
				exchangeCount++;
			}
			compareCount++;
		}
	}
}

template<class T>
void BubbleSort2(T arr[], int length) {
	if (arr == NULL || length <= 0) {
		cerr << "无效参数传递:" << endl;
		return;
	}

	int lastpos = length - 1;//设第一趟初值
	for (int i = 0; i < length - 1 && lastpos; i++) {
		int k = lastpos;
		for (int j = 0; j < k; j++) {
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				lastpos = j;
				exchangeCount++;
			}
			compareCount++;
		}
	}
}

template<class T>
void BubbleSort3(T arr[], int length) {
	if (arr == NULL || length <= 0) {
		cerr << "无效参数传递:" << endl;
		return;
	}

	int tailIndex = length - 1;
	bool exchange = true;
	for (int i = 0; (i < (length / 2)) && exchange; i++) {
		exchange = false;
		for (int j = i; j < length - i - 1; j++) {
			//最大值向后冒泡
			if (arr[j] > arr[j + 1]) {
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				exchange = true;
				exchangeCount++;
			}
			//最小值向前冒泡
			int rightIndex = length - j - 1;
			if (arr[rightIndex] < arr[rightIndex - 1]) {
				T temp = arr[rightIndex];
				arr[rightIndex] = arr[rightIndex - 1];
				arr[rightIndex - 1] = temp;
				exchange = true;
				exchangeCount++;
			}
			compareCount += 2;
			/*std::cout << i << " " << j << "## ";
			for (int k = 0; k < 10; k++) {
				std::cout << arr[k] << " ";
			}
			std::cout << std::endl;*/
		}
	}
}

//选择排序
template<class T>
void SelectSort(T arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	exchangeCount = 0;
	compareCount = 0;
	for (int i = 0; i < len; i++) {
		int min = i;
		for (int j = i; j < len; j++) {
			if (arr[j] < arr[min]) {
				min = j;
				exchangeCount++;
			}
			compareCount++;
		}
		if (min != i) {
			T temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
			exchangeCount++;
		}
	}
}

//直接插入排序
template<class T>
void DirInsertSort(T arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	exchangeCount = 0;
	compareCount = 0;
	for (int i = 1; i < len; i++) {        //第一个数字必然有序
		T temp = arr[i];                 //取出第i个数，与前i-1有序列比较
		int j = i - 1;                     //1 2 3 * * * i-1(arr[j]) i(temp) * * len
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j];           //1 2 3 * * * i-1 i-1 * * len
			j--;
			exchangeCount++;
			compareCount++;
		}
		arr[j + 1] = temp;
		exchangeCount++;
	}
}

//折半插入排序
template <class T>
void BinInsertSort(T arr[], int len)
{
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}
	exchangeCount = 0;
	compareCount = 0;

	int low, high, mid;
	for (int i = 1; i < len; i++) {        //第一个数字(arr[0])必然有序
		low = 0;
		high = i - 1;
		T temp = arr[i];                 //取出第i个数，与前i-1有序列比较
		while (low <= high) {
			mid = (low + high) / 2;
			if (temp < arr[mid]) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			compareCount++;
		}
		for (int k = i - 1; k >= low; k--) {
			arr[k + 1] = arr[k];
			exchangeCount++;
		}
		arr[low] = temp;
	}
}


//希尔排序
template<class T>
void ShellSort(T arr[], int len) {
	if (arr == NULL || len <= 0) {
		cerr << "无效参数传递" << endl;
		return;
	}

	exchangeCount = 0;
	compareCount = 0;

	int j = 0;
	T temp = 0;
	int group = len / 2;//设置步长

	while (group >= 1) {
		compareCount++;

		for (int i = group; i < len; ++i) {
			temp = arr[i];

			for (j = i - group; j >= 0; j -= group) {
				if (arr[j] <= temp)
					break;
				arr[j + group] = arr[j];

				exchangeCount++;
				compareCount++;
			}

			arr[j + group] = temp;

			exchangeCount++;
		}
		group = group / 2;
	}

}

//快速排序
template<class T>
void QuickSort(int L, int R, T arr[]) {
	if (L >= R || L < 0 || R < 0) {
		return;
	}

	int left = L, right = R - 1;
	T pivot = arr[left];      //基准柱
	while (left < right) {
		while (left < right && arr[right] >= pivot) {
			compareCount += 2;
			right--;
		}
		compareCount++;
		if (arr[right] < pivot) {
			arr[left] = arr[right];
			exchangeCount++;
		}
		while (left < right && arr[left] < pivot) {
			compareCount += 2;

			left++;
		}
		compareCount++;
		if (arr[left] > pivot) {
			arr[right] = arr[left];
			exchangeCount++;
		}
	}
	compareCount++;
	if (left >= right) {
		arr[left] = pivot;
		exchangeCount++;
	}
	QuickSort(L, right, arr);
	QuickSort(right + 1, R, arr);
}



template<class T>
void Merge(T arr[], int begin, int end) {

	T* tempArr = new T[end - begin + 1]();

	int middle = (begin + end) / 2;
	int p1 = begin;
	int p2 = middle + 1;
	int p = 0;

	while (p1 <= middle && p2 <= end) {
		compareCount += 3;
		exchangeCount++;

		if (arr[p1] <= arr[p2]) {
			tempArr[p++] = arr[p1++];
		}
		else {
			tempArr[p++] = arr[p2++];
		}

	}

	while (p1 <= middle) {
		compareCount++;
		exchangeCount++;
		tempArr[p++] = arr[p1++];
	}
	compareCount++;
	while (p2 <= end) {
		compareCount++;
		exchangeCount++;
		tempArr[p++] = arr[p2++];
	}
	compareCount++;//退出上次循环进行的比较

	for (int i = 0; i <= end - begin; i++) {
		arr[i + begin] = tempArr[i];
		exchangeCount++;
	}

	delete[] tempArr;
	return;
}

template<class T>
void MergeSort(T arr[], int begin, int end) {
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
template<class T>
void DownAdjust(T arr[], int parentIndex, int len) {
	T temp = arr[parentIndex];
	int childIndex = parentIndex * 2 + 1;

	while (childIndex < len) {
		if (childIndex + 1 < len && arr[childIndex + 1] > arr[childIndex]) {
			childIndex++;
			compareCount += 2;
		}
		compareCount++;

		compareCount++;
		if (temp > arr[childIndex]) {
			break;
		}

		arr[parentIndex] = arr[childIndex];
		exchangeCount++;
		parentIndex = childIndex;
		childIndex = 2 * parentIndex + 1;
	}

	arr[parentIndex] = temp;
	exchangeCount++;

}

template<class T>
void HeapSort(T arr[], int len) {
	for (int i = len / 2; i >= 0; i--) {
		DownAdjust(arr, i, len);
	}

	for (int i = len - 1; i > 0; i--) {
		T temp = arr[0];
		arr[0] = arr[i];
		exchangeCount++;
		arr[i] = temp;
		DownAdjust(arr, 0, i);
	}
}

//计数排序
template<class T>
void CountSort(T arr[], int len, int exp) {
	T* result = new T[len];
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
		exchangeCount++;
		bucket[tempEXP]--;
	}
	for (int i = 0; i < len; i++) {
		arr[i] = result[i];
		exchangeCount++;
	}
	delete[] result;
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
	cout << "**                4 --- 布尔排序                 **" << endl;
	cout << "**                5 --- 快速排序                 **" << endl;
	cout << "**                6 --- 堆排序                   **" << endl;
	cout << "**                7 --- 归并排序                 **" << endl;
	cout << "**                8 --- 基数排序                 **" << endl;
	cout << "**                9 --- 退出程序                 **" << endl;
	cout << "==================================================" << endl;
}

template<class T>
void PrintArr(T arr[], int length) {
	for (int i = 0; i < length; i++) {
		cout << "#" << i + 1 << " " << arr[i] << endl;
	}
}

//对10^index个随机数不同排序算法进行横向对比
void table(int Index) {

	int size = pow(10, Index);
	int* arr = new int[size];
	RandomNumber(arr, size);
	clock_t start, finish;
	double deltaTime;

	std::cout << "随机数个数:" << size << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "**                     随机序列                       **" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "算法                  时间        比较次数      移动次数" << std::endl;


	int* temp = new int[size];
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	BubbleSort3(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "BubbleSort    "
		<< setiosflags(std::ios::right) << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	cout << resetiosflags(ios::left);

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	SelectSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "SelectSort    " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	DirInsertSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "DirInsertSort " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	BinInsertSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "HalfInsertSort" << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	ShellSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "ShellSort     " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	HeapSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "HeapSort      " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	RadixSort(temp, size);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "RadixSort     " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;

	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	MergeSort(temp, 0, size - 1);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "MergeSort     " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;


	exchangeCount = compareCount = 0;
	memcpy(temp, arr, sizeof(int) * size);
	start = clock();
	QuickSort(0, size, temp);
	finish = clock();
	deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << "QuickSort     " << setw(12) << deltaTime << "s"
		<< setw(14) << compareCount
		<< setw(14) << exchangeCount << std::endl;
	std::cout << "========================================================" << std::endl;

	delete[] arr;
	delete[] temp;
	std::cout << std::endl;
}

int main() {
#ifdef WIN32
	system("chcp 65001");//解决windows控制台代码页936的报错问题(字符编码问题)
#endif
	Menu();
	int num;
	cout << "请输入要产生的随机数的个数:";
	cin >> num;
	int* arr = new int[num];
	RandomNumber(arr, num);

	bool con = true;

	while (con) {
		std::cout << "请选择排序算法：";
		char option;
		std::cin >> option;
		int* temp = new int[num];
		memcpy(temp, arr, sizeof(int) * num);
		switch (option) {
			//冒泡排序 
		case '1': {
			clock_t start, finish;
			start = clock();
			BubbleSort3(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "冒泡排序:";
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "         比较次数:" << compareCount << std::endl;
			std::cout << "         交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			//PrintArr(temp,num);
			break;
		}
				//选择排序   
		case '2': {
			clock_t start, finish;
			start = clock();
			SelectSort(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//直接插入排序    
		case '3': {
			clock_t start, finish;
			start = clock();
			DirInsertSort(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//布尔排序
		case '4': {
			clock_t start, finish;
			start = clock();
			ShellSort(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//快速排序  
		case '5': {
			clock_t start, finish;
			start = clock();
			QuickSort(0, num, temp);//快速排序
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//堆排序 
		case '6': {
			clock_t start, finish;
			start = clock();
			HeapSort(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//归并排序
		case '7': {
			clock_t start, finish;
			start = clock();
			MergeSort(temp, 0, num - 1);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//基数排序
		case '8': {
			clock_t start, finish;
			start = clock();
			RadixSort(temp, num);
			finish = clock();
			double deltaTime = (double)(finish - start) / CLOCKS_PER_SEC;
			std::cout << "消耗时间:" << deltaTime << endl;
			std::cout << "比较次数:" << compareCount << std::endl;
			std::cout << "交换次数:" << exchangeCount << std::endl;
			std::cout << std::endl;
			break;
		}
				//exit()/opt/
		case '9': {
			con = false;
			break;
		}

		default: {
			std::cout << "Error input" << std::endl;
			break;
		}
		}
		delete[]temp;
	}
	for (int i = 3; i <= 5; i++) {
		std::cout << "10^" << i << "个随机数不同排序横向比较(冒泡排序较为费时)" << std::endl;
		table(i);
	}
	delete[]arr;
	system("pause");
	return 0;
}
