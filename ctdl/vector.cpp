#include <iostream>

using namespace std;

template <typename T>

class Vector {
public:
	// Vector initialization.
	// Time complexity: O(1)
	Vector(int initCapacity = 16)
	{
		size = 0;
		capacity = initCapacity;
		array = new T[capacity];
	}

	// Destructor
	// Time complexity: O(1)
	~Vector()
	{
		delete[] array;
	}
	
	// Return vector capacity.
	// Time complexity: O(1)
	int getCapacity() {
		return capacity;
	}

	// Return vector size.
	// Time complexity: O(1)
	int getSize()
	{
		return size;
	}

	// Truncate the vector.
	// Time complexity: O(1)
	void truncate() {
		capacity = size;
	}

	// Return true if the vector is empty, and vice versa.
	// Time complexity: O(1)
	bool isEmpty() {
		return (size == 0);
	}

	// Linear search
	// Time complexity: O(n)
	bool LinearSearch(int tmp) {
		for (int i = 0; i < size; i++) {
			if (tmp == array[i]) {
				return true;
			}
		}

		return false;
	}

	// Binary search
	// Time complexity: O(log n)
	bool BinarySearch(int tmp) {
		int left = 0, right = size - 1;

		while (left <= right) {
			int mid = (left + right) / 2;
			if (array[mid] == tmp) {
				return true;
			} else if(array[mid] < tmp) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}

		return false; 
	}

	// index is the element that we need to access.
	// Time complexity: O(1)
	T & operator[](int index)
	{
		return array[index];
	}

	// Sorting function.
	// Use insertion sort because this one is stable for small datasets. The vector
	// provided isn't large, so no need to use Quick Sort as they are not stable.
	// Time complexity: O(n^2) at worst.
	void sortVec() {
		for (int i = 1; i < size; i++) {
			int key = array[i];
			int j = i - 1;

			while (j >= 0 && key < array[j]) {
				array[j + 1] = array[j];
				j = j - 1;
			}

			array[j + 1] = key;
		}
	}

	// Delete from range
	// Time complexity: O(n)
    	void rangeDelete(int pos1, int pos2) {
	        if (pos1 < 0 || pos2 >= size || pos1 > pos2) {
	            // Handle invalid input
	            return;
	        }
	
	        // Shift elements to the left to overwrite the deleted range
	        int j = pos2 + 1;
	        for (int i = pos1; i < size - (pos2 - pos1 + 1); i++) {
	            array[i] = array[j];
	            j++;
	        }
	
	        // Update the size of the vector
	        size -= (pos2 - pos1 + 1);
    	}


	// newElement will be pushed to the last element in the array.
	// Time complexity: O(1)
	void pushBack(T newElement)
	{
		if (size == capacity) {
			expand (2 * capacity);
		}

		array[size] = newElement;

		// Update.
		size++;
	}

	// pos is the position of the newElement to land on.
	// Time complexity: O(n)
	void insert(int pos, T newElement)
	{
		// Expands the storage 2 times if the current one is full.
		if (size == capacity) {
			expand(2 * capacity);
		}

		for (int i = size; i > pos; i--) {
			array[i] = array [i - 1];
		}

		array[pos] = newElement;

		// Update.
		size++;
	}

	// Remove the last element in the array.
	// Time complexity: O(1)
	void popBack()
	{
		size--;
	}

	// pos is the position of the element that needs to be deleted.
	// Time complexity: O(n)
	void erase(int pos)
	{
		for (int i = pos; i < size; i++) {
			array[i] = array[i + 1];
		}

		// Resize.
		size--;
	}

	// Print.
	// Time complexity: O(n)
	void print()
	{
		for (int i = 0; i < size; i++) {
			cout << " " << array[i];
		}
		cout << endl;
	}

	private:
		int size;     // Vector size
		int capacity; // Vector capacity
		T * array;	  // The pointer

		// This function will assist in some cases of the insertion operation.
		// newCapacity is the new capacity (must be larger than size).
		void expand(int newCapacity)
		{
			if (newCapacity <= size) {
				return;
			}

			T * old = array;
			array = new T[capacity];

			for (int i = 0; i < size; i++) {
				array[i] = old[i];
			}

			delete[] old;
			capacity = newCapacity;
		}
};

int main()
{
	Vector<int> v;
	int x, pos1, pos2; // Su dung de tim kiem, de xoa theo pos1 -> pos2

	// Push
	v.pushBack(6);
	v.pushBack(2);
	v.pushBack(9);
	v.pushBack(1);
	v.pushBack(8);

	// In dung luong cua vector len man hinh
	cout << "Dung luong cua vector la: " << v.getCapacity() << endl;

	// Cat bo phan dung luong du thua cua vector
	cout << "\nDang thuc thi lenh Truncate." << endl;
	v.truncate();

	// In kich thuoc va dung luong cua vector xem co bang nhau hay khong
	cout << "\nKich thuoc cua vector: " << v.getSize() << endl;
	cout << "Dung luong cua vector: " << v.getCapacity() << endl;

	if (v.getSize() == v.getCapacity())
		cout << "Kich thuoc bang voi dung luong cua vector." << endl;
	else
		cout << "Kich thuoc khong bang voi dung luong cua vector." << endl;

	// In tat ca cac phan tu cua vector len man hinh
	cout << "\nCac phan tu cua vector:";
	v.print();

	// Tim kiem tuan tu tren vector
	cout << "Tim kiem tuan tu. Nhap phan tu de tim kiem: ";
	cin >> x;

	if (v.LinearSearch(x) == true) {
		cout << "Phan tu " << x << " xuat hien trong vector." << endl;
	} else {
		cout << "Phan tu " << x << " khong xuat hien trong vector." << endl;
	}

	// Tim kiem nhi phan tren vector (hay tao mot vector khac chua cac phan tu sap xep tang dan)
	cout << "\nTruoc khi tim kiem nhi phan thi mang can phai duoc sap xep lai." << endl;
	cout << "Vector truoc khi duoc sap xep:";
	v.print();
	cout << "Vector sau khi duoc sap xep:";
	v.sortVec();
	v.print();

	cout << "\nTim kiem nhi phan. Nhap phan tu de tim kiem: ";
	cin >> x;

	if (v.BinarySearch(x) == true) {
		cout << "Phan tu " << x << " xuat hien trong vector." << endl;
	} else {
		cout << "Phan tu " << x << " khong xuat hien trong vector." << endl;
	}

	// Xoa cac phan tu nam o cac vi tri tu pos1 den pos2 tren vector
	cout << "\nNhap vi tri pos1: ";
	cin >> pos1;
	cout << "Nhap vi tri pos2: ";
	cin >> pos2;
	
	cout << "Cac phan tu trong mang sau khi duoc xoa:";
	v.rangeDelete(pos1, pos2);
	v.print();

	// The vector will be destroyed when it reached this point. See the destructor function.
	return 0;
}
