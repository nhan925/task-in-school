#include <iostream>
using namespace std;

struct Fraction {
	int tu, mau;

	bool operator < (Fraction b) {
		return tu * b.mau < b.tu * mau;
	}

	bool operator > (Fraction b) {
		return tu * b.mau > b.tu * mau;
	}

	friend ostream& operator << (ostream& outDev, Fraction& a) {
		outDev << a.tu << "/" << a.mau;
		return outDev;
	}
};

template<class T>
bool increase(T a, T b) {
	return a > b;
}

template<class T>
bool decrease(T a, T b) {
	return a < b;
}

template<class T>
void Sort(T* a, const int n, bool(*condition)(T, T)) {
	T temp;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (condition(a[i], a[j])) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
}

template<class T>
void PrintArr(T* const arr, const int& n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << "\n";
}

int main() {
	int a[] = { 1, 2, 0, -1, 9, 8, 4 };
	//float a[] = { 0.1f, 0.5f, -1.4f, 10.0f, 9.0f, -8.1f };
	//string a[] = { "hello", "xin chao", "bonjour" };
	//Fraction a[] = { {1, 2}, {2, 3}, {4, 7}, {3, 5} };
	int n = sizeof(a) / sizeof(a[0]);
	Sort(a, n, increase);
	PrintArr(a, n);
	Sort(a, n, decrease);
	PrintArr(a, n);
}