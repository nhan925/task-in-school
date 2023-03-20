#include <iostream>
#include <memory>
using namespace std;

void alloc2D(void*** a, int m, int n, int szItem) {
	void* buf = malloc(12 + m * sizeof(void*) + m * n * szItem);
	if (buf == nullptr) return;
	*((int*)buf) = m;
	*((int*)buf + 1) = n;
	*((int*)buf + 2) = szItem;
	buf = (char*)buf + 12;
	*a = (void**)buf;
	buf = (char*)buf + m * sizeof(void*);
	*(*a) = buf;
	for (int i = 1; i < m; i++) {
		buf = (char*)buf + n * szItem;
		*(*a + i) = buf;
	}
}

void free2D(void** a) {
	if (a != nullptr) free((char*)a - 12);
}

int nRow(void** a) {
	return *(int*)((char*)a - 12);
}

int nCol(void** a) {
	return *(int*)((char*)a - 8);
}

void arr2D_Input(int**& a) {
	int m = nRow((void**)a), n = nCol((void**)a);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
}

void resize2D(void*** a, int m, int n) {
	if (*a == nullptr || m <= 0 || n <= 0) return;
	int m_old = nRow(*a), n_old = nCol(*a), sz_old = *(int*)((char*)*a - 4);
	void** anew = nullptr;
	alloc2D(&anew, m, n, sz_old);
	if (anew == nullptr) return;
	for (int i = 0; i < m_old && i < m; i++)
		for (int j = 0; j < n_old && j < n; j++) {
			char* src = ((char*)(*(*a + i)) + j * sz_old);
			char* dest = ((char*)(*(anew + i)) + j * sz_old);
			memmove(dest, src, sz_old);
		}
	free2D(*a);
	*a = anew;
}

void arr2D_Output(int** const& a) {
	int m = nRow((void**)a), n = nCol((void**)a);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
}

int main() {
	int m = 0, n = 0;
	int** a = nullptr;
	cout << "Nhap so dong & cot: ";
	cin >> m >> n;
	alloc2D(((void***)&a), m, n, sizeof(int));
	if (a == nullptr) return 0;
	cout << "Nhap cac phan tu: ";
	arr2D_Input(a);
	arr2D_Output(a);
	cout << "Nhap lai kich thuoc moi: ";
	cin >> m >> n;
	resize2D(((void***)&a), m, n);
	cout << "Nhap cac phan tu: ";
	arr2D_Input(a);
	arr2D_Output(a);
	free2D((void**)a);
	return 0;
}