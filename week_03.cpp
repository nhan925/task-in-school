#include <iostream>
#include <memory>
using namespace std;

const int HeaderSize = sizeof(int) * 2;

struct COMPLEX_NUM {
	float real, img;
};

int MemSize(int nItem, int SizeOfItem) {
	return HeaderSize + nItem * SizeOfItem;
}

void* Origin_Address(void* Data_Address) {
	if (Data_Address != nullptr)
		return (char*)Data_Address - HeaderSize;
	return nullptr;
}

void* Data_Address(void* Origin_Address) {
	if (Origin_Address != nullptr)
		return (char*)Origin_Address + HeaderSize;
	return nullptr;
}

void* SizeItemAddress(void* Data_Address) {
	if (Data_Address != nullptr)
		return (char*)Data_Address - sizeof(int);
	return nullptr;
}

int ArraySize(void* Data_Address) {
	if (Data_Address != nullptr)
		return *(int*)(Origin_Address(Data_Address));
	return 0;
}

int ItemSize(void* Data_Address) {
	if (Data_Address != nullptr)
		return *(int*)(SizeItemAddress(Data_Address));
	return 0;
}

void FreeArray(void* Data_Address) {
	if (Data_Address != nullptr)
		free(Origin_Address(Data_Address));
}

void* AllocArray(int nItem, int ItemSize) {
	int Size = MemSize(nItem, ItemSize);
	void* origin_address = malloc(Size);
	if (origin_address != nullptr) {
		memset(origin_address, 0, Size);
		void* data_address = Data_Address(origin_address);
		*(int*)(origin_address) = nItem;
		*(int*)(SizeItemAddress(data_address)) = ItemSize;
		return data_address;
	}
	return nullptr;
}

void* ResizeArray(void* data_address, int nItem) {
	if (data_address == nullptr || nItem < 0)
		return nullptr;
	void* origin_address = Origin_Address(data_address);
	int item_size = ItemSize(data_address);
	int size = MemSize(nItem, item_size);
	void* new_array = realloc(origin_address, size);
	if (new_array != nullptr) {
		data_address = Data_Address(new_array);
		*(int*)(new_array) = nItem;
		return data_address;
	}
	return nullptr;
}

bool ArrPushback(void** data_address, void* x) {
	int nItem = ArraySize(*data_address), item_size = ItemSize(*data_address);
	void* new_array = ResizeArray(*data_address, nItem + 1);
	if (new_array != nullptr) {
		memmove((char*)new_array + nItem * item_size, x, item_size);
		*data_address = new_array;
		return 1;
	}
	return 0;
}

void* ArrPopback(void** data_address) {
	int nItem = ArraySize(*data_address), item_size = ItemSize(*data_address);
	void* x = malloc(item_size);
	if (*data_address != nullptr && nItem > 0) {
		nItem--;
		memmove(x, (char*)(*data_address) + nItem * item_size, item_size);
		void* new_array = ResizeArray(*data_address, nItem);
		if (new_array != nullptr)
			*data_address = new_array;
	}
	return x;
}

istream& operator >> (istream& inDev, COMPLEX_NUM& x) {
	inDev >> x.real >> x.img;
	return inDev;
}

COMPLEX_NUM* ArrInput() {
	COMPLEX_NUM* array = (COMPLEX_NUM*)AllocArray(0, sizeof(COMPLEX_NUM));
	COMPLEX_NUM x = { 0, 0 };
	while (cin >> x)
		ArrPushback((void**)&array, &x);
	cin.clear();
	return array;
}

ostream& operator << (ostream& outDev, COMPLEX_NUM& x) {
	outDev << x.real;
	if (x.img < 0)
		outDev << " - " << abs(x.img) << "i";
	else if (x.img > 0)
		outDev << " + " << x.img << "i";
	return outDev;
}

void ArrOutput(COMPLEX_NUM* data_address) {
	int nItem = ArraySize(data_address);
	for (int i = 0; i < nItem; i++)
		cout << *(data_address + i) << "\n";
}

void main() {
	cout << "Input complex items:\n";
	COMPLEX_NUM* B = ArrInput();
	COMPLEX_NUM* x = (COMPLEX_NUM*)ArrPopback((void**)&B);
	cout << "After pop:\n";
	ArrOutput(B);
	cout << "Popped element: " << *x << "\n";
	free(x);
	FreeArray(B);
}