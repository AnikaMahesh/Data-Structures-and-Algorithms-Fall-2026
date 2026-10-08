#include <algorithm>
#include <chrono>
#include <cstdio>
#include <functional>
#include <random>
#include <string>
#include <vector>
#include "sort.h"

using Clock = std::chrono::steady_clock;
struct Algo {
	std::string name;
	std::function<void(int*, int)> run;
};

// Builds a vector of n random non-negative ints (radix sort needs >= 0).
// Input: n (int) element count, seed (unsigned) so every algorithm sees the same data.
std::vector<int> makeRandom(int n, unsigned seed) {
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dist(0, 1000000);
	std::vector<int> v(n);
	for (int& x : v) x = dist(gen);
	return v;
}

// Times one sort on a copy of the data and returns milliseconds, or -1 if the result is not sorted.
// Input: algo (Algo) the sort to run, data (vector<int>) the unsorted numbers.
double timeSort(const Algo& algo, std::vector<int> data) {
	auto start = Clock::now();
	algo.run(data.data(), (int)data.size());
	auto end = Clock::now();
	if (!std::is_sorted(data.begin(), data.end())) return -1.0;
	return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
	const int trials = 5;
	const std::vector<int> sizes = { 100, 1000, 10000, 50000, 100000 };
	std::vector<Algo> algos = {
		{"insertion", [](int* a, int n) { insertionSort(a, n); }},
		{"selection", [](int* a, int n) { selectionSort(a, n); }},
		{"radix",     [](int* a, int n) { radixSort(a, n); }},
		{"merge",     [](int* a, int n) { mergeSort(a, n); }},
		{"std::sort", [](int* a, int n) { std::sort(a, a + n); }},
	};
	std::printf("Average runtime in ms over %d trials\n\n", trials);
	std::printf("%-10s", "size");
	for (const Algo& algo : algos) std::printf("%14s", algo.name.c_str());
	std::printf("\n");
	for (int n : sizes) {
		std::printf("%-10d", n);
		for (const Algo& algo : algos) {
			double total = 0.0;
			bool correct = true;
			for (int t = 0; t < trials; ++t) {
				double ms = timeSort(algo, makeRandom(n, n * 100 + t));
				if (ms < 0) { correct = false; break; }
				total += ms;
			}
			if (correct) std::printf("%14.3f", total / trials);
			else         std::printf("%14s", "WRONG");
		}
		std::printf("\n");
	}
	return 0;
}