#include "generator.h"
#include <algorithm>
#include <iostream>

int Factorial(int n) {
	int f = 1;
	for (int b = 2; b <= n; b++)
	{
		f *= b;
	}
	return f;
}

void Generator::pushx() {
	for (int i = 0; i < n; i++)
	{
		x[i]++;
	}

	result.push_back(x);

	for (int i = 0; i < n; i++)
	{
		x[i]--;
	}
}

Generator::Generator(int m, int n) {
	this->n = n;
	this->m = m - n;
	x.resize(n);
}

bool Generator::next() {
	int j = n - 1;
	int s = 0;

	// 0 0 0 0
	// 0 9 9
	// 1 0 0 

	while (x[j] + 1 > m || s == 0) { 
		s += x[j];
		j--;
		if (j < 0) return false;
	}
	x[j]++;

	// 0 0 6
	// 0 1 5
	// 0 2 4
	// ...
	// 0 6 0
	// 1 0 5


	s--;
	for (int i = n - 1; j < i; i--) {					
		x[i] = s;
		s = 0;
	}
	return true;
}

void Generator::GenerateAll() {
	x[n-1] = m;
	
	int i=n-2;
	while (i >= 0) {
		x[i] = 0;
		i--;
	}
	pushx();
	while (next() && getCount() < 1000000) pushx();
}

std::vector<int>& Generator::GetResult(int idx) {
	return result[idx];
}

int Generator::getCount() {
	return result.size();
}

void Generator::GenerateRecursive() {
	recursiveNext(0, m);
}

void Generator::recursiveNext(int i, int s) { // i - индекс, s - сумма
	if (i == n - 1) { // последний элемент
		x[i] = s;
		pushx();
		return;
	}

	if (s == 0) {
		for (int j = i; j < n; j++) {
			x[j] = 0;
		}
		pushx();
		return;
	}

	if (s < 0) return;

	for (int j = 0; j <= s; j++) { // j - первое слагаемое
		x[i] = j;
		recursiveNext(i + 1, s - j);
	}
}