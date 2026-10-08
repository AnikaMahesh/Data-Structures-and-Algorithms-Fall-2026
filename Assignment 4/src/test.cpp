#include "pch.h"
#include "sorting_algorithms.h"
#include <vector>

// Checks insertionSort orders a typical unsorted array.
TEST(InsertionSortTests, SortsUnsortedArray) {
	std::vector<int> v = { 5, 2, 9, 1, 5, 6 };
	insertionSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{1, 2, 5, 5, 6, 9}));
}

// Checks insertionSort leaves an already sorted array unchanged.
TEST(InsertionSortTests, AlreadySortedStaysSorted) {
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	insertionSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Checks insertionSort handles empty and single-element arrays without crashing.
TEST(InsertionSortTests, EmptyAndSingleElement) {
	std::vector<int> empty;
	insertionSort(empty.data(), 0);
	EXPECT_TRUE(empty.empty());

	std::vector<int> one = { 42 };
	insertionSort(one.data(), 1);
	EXPECT_EQ(one[0], 42);
}

// Checks selectionSort orders a typical unsorted array.
TEST(SelectionSortTests, SortsUnsortedArray) {
	std::vector<int> v = { 64, 25, 12, 22, 11 };
	selectionSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{11, 12, 22, 25, 64}));
}

// Checks selectionSort correctly reverses a descending array.
TEST(SelectionSortTests, ReverseSortedInput) {
	std::vector<int> v = { 5, 4, 3, 2, 1 };
	selectionSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Checks selectionSort keeps duplicates and handles negative numbers.
TEST(SelectionSortTests, DuplicatesAndNegatives) {
	std::vector<int> v = { 3, -1, 3, 0, -1 };
	selectionSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{-1, -1, 0, 3, 3}));
}

// Checks radixSort orders non-negative numbers with mixed digit counts.
TEST(RadixSortTests, SortsMixedDigitLengths) {
	std::vector<int> v = { 170, 45, 75, 90, 802, 24, 2, 66 };
	radixSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{2, 24, 45, 66, 75, 90, 170, 802}));
}

// Checks radixSort keeps duplicate values and handles zeros.
TEST(RadixSortTests, DuplicatesAndZeros) {
	std::vector<int> v = { 0, 10, 0, 10, 5, 5 };
	radixSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{0, 0, 5, 5, 10, 10}));
}

// Checks radixSort handles empty and single-element arrays without crashing.
TEST(RadixSortTests, EmptyAndSingleElement) {
	std::vector<int> empty;
	radixSort(empty.data(), 0);
	EXPECT_TRUE(empty.empty());

	std::vector<int> one = { 7 };
	radixSort(one.data(), 1);
	EXPECT_EQ(one[0], 7);
}

// Checks mergeSort orders an array with an even number of elements.
TEST(MergeSortTests, SortsEvenLengthArray) {
	std::vector<int> v = { 38, 27, 43, 3, 9, 82 };
	mergeSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{3, 9, 27, 38, 43, 82}));
}

// Checks mergeSort orders an array with an odd length, duplicates, and negatives.
TEST(MergeSortTests, SortsOddLengthWithDuplicatesAndNegatives) {
	std::vector<int> v = { 4, -2, 4, 0, 1 };
	mergeSort(v.data(), (int)v.size());
	EXPECT_EQ(v, (std::vector<int>{-2, 0, 1, 4, 4}));
}

// Checks mergeSort handles empty and single-element arrays without crashing.
TEST(MergeSortTests, EmptyAndSingleElement) {
	std::vector<int> empty;
	mergeSort(empty.data(), 0);
	EXPECT_TRUE(empty.empty());

	std::vector<int> one = { 99 };
	mergeSort(one.data(), 1);
	EXPECT_EQ(one[0], 99);
}