#pragma once
#include <vector>

// Sorts an array in ascending order using insertion sort.
// Input: array (int*) to sort in place, length (int) number of elements.
inline void insertionSort(int array[], int length) {
	for (int i = 1; i < length; ++i) {
		int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}

// Sorts an array in ascending order using selection sort.
// Input: array (int*) to sort in place, length (int) number of elements.
inline void selectionSort(int array[], int length) {
	for (int i = 0; i < length - 1; ++i) {
		int minIndex = i;
		int minValue = array[i];
		for (int j = i + 1; j < length; ++j) {
			if (array[j] < minValue) {
				minValue = array[j];
				minIndex = j;
			}
		}
		int temp = array[i];
		array[i] = array[minIndex];
		array[minIndex] = temp;
	}
}

// Sorts an array in ascending order using radix sort (base 10, LSD).
// Input: array (int*) of non-negative ints to sort in place, size (int) number of elements.
inline void radixSort(int array[], int size) {
	if (size <= 1) return;

	int maxValue = array[0];
	for (int i = 1; i < size; i++) {
		if (array[i] > maxValue)
			maxValue = array[i];
	}

	for (int place = 1; maxValue / place > 0; place *= 10) {
		const int base = 10;
		std::vector<int> output(size);
		int count[base] = { 0 };

		for (int i = 0; i < size; i++)
			count[(array[i] / place) % 10]++;

		for (int i = 1; i < base; i++)
			count[i] += count[i - 1];

		for (int i = size - 1; i >= 0; i--) {
			output[count[(array[i] / place) % 10] - 1] = array[i];
			count[(array[i] / place) % 10]--;
		}

		for (int i = 0; i < size; i++) {
			array[i] = output[i];
		}
	}
}

// Sorts an array in ascending order using recursive merge sort.
// Input: array (int*) to sort in place, length (int) number of elements.
inline void mergeSort(int array[], int length) {
	if (length > 1) {
		int leftLength = length / 2;
		int rightLength = length - leftLength;
		std::vector<int> left(array, array + leftLength);
		std::vector<int> right(array + leftLength, array + length);

		mergeSort(left.data(), leftLength);
		mergeSort(right.data(), rightLength);

		int i = 0;
		int j = 0;
		int k = 0;
		while ((i < leftLength) && (j < rightLength)) {
			if (left[i] < right[j]) {
				array[k] = left[i];
				i += 1;
			}
			else {
				array[k] = right[j];
				j += 1;
			}
			k += 1;
		}

		while (i < leftLength) {
			array[k] = left[i];
			i += 1;
			k += 1;
		}

		while (j < rightLength) {
			array[k] = right[j];
			j += 1;
			k += 1;
		}
	}
}