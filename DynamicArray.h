#pragma once
template<typename T>
class DynamicArray
{
public:
	DynamicArray(int size);
	DynamicArray() : DynamicArray(16) {} // call the other constructer with a default value of 16
	~DynamicArray();
	void print();
	int size() {return lenght};
	bool isEmpty() { return size() == 0; }
	T get(int index) 
	{
		if (index > lenght)
			throw std::invalid_argument("index is out of range");
		return *(ptr + index);
	}
	void set(int index, T elem) 
	{ 
		if (index > lenght)
			throw std::invalid_argument("index is out of range");
		ptr[index] = elem; 
	}
	void clear() 
	{
		delete [] ptr;
		ptr = NULL;
		lenght = 0;
		capacity = 0;
	}
	void add(T elem) 
	{
		//time to resize
		if (lenght + 1 >= capacity)
		{
			if (capacity == 0)
				capacity = 1;
			else
				capacity *= 2; // double the capacity
			T * newArray = new T[capacity];
			for (int i = 0; i < lenght; ++i)
				newArray[i] = *(ptr +i); // put the values into the new array.
			delete[] ptr;
			ptr = newArray;
			newArray = NULL;
			delete newArray;
		}

		ptr[lenght++] = elem;
	}

	//remove the element at the specified index in the array.
	T removeAt(int remove_index);
	//removes the first instance of an element from the array no matter where it is.
	bool remove(T elm);
	// returns the first instance of an index of an element no matter were it is. 
	int indexOf(T elm);
	//returns true if the elm is found in the array, false otherwise.
	bool contains(T elm);

private:
	T *ptr; // array is just a memory location. So a pointer here works. 
	int lenght; // lenght of the array the user thinks it is. 
	int capacity; // actual size
};

template <typename T>
DynamicArray<T>::DynamicArray(int cap)
{
	if (capacity < 0)
		throw std::invalid_argument("capacity must be larger than 0");
	ptr = new T[cap];
	capacity = cap;

}


template <typename T>
DynamicArray<T>::~DynamicArray()
{
	delete [] ptr;
}

template <typename T>
void DynamicArray<T>::print()
{
	for (int i = 0; i < lenght; ++i)
		std::cout << " " << *(ptr + i);
	std::cout << std::endl;
}

template <typename T>
T DynamicArray<T>::removeAt(int remove_index) 
{
	if(remove_index >= lenght || remove_index < 0 )
		throw std::invalid_argument("remove_index must be larger than 0 || remove_index must not be longer than lenght.");
	T* newArray = new T[lenght-1];
	T dataToRemove = *(ptr + remove_index);
	for (int i = 0, j = 0; i < lenght; ++i, ++j)
	{
		if (i == remove_index)
			--j;
		else
			*(newArray+ j) = *(ptr + i);
	}
	delete [] ptr;
	ptr = newArray;
	newArray = NULL;
	delete [] newArray;
	--lenght;
	return dataToRemove;
}

template <typename T>
bool DynamicArray<T>::remove(T elm) 
{
	for (int i = 0; i < lenght; ++i) 
	{
		if (*(ptr + i) == elm)
		{
			removeAt(i);
			return true;
		}
	}

	return false;
}

template <typename T>
int DynamicArray<T>::indexOf(T elm) 
{
	for (int i = 0; i < lenght; ++i)
	{
		if (*(ptr + i) == elm)
			return i;
	}
	return -1;
}
template <typename T>
bool DynamicArray<T>::contains(T elm) 
{
	for (int i = 0; i < lenght; ++i) 
	{
		if (*(ptr + i) == elm)
			return true;
	}
	return false;
}

