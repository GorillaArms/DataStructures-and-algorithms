#pragma once

template <typename T>
class DList // doubly  linked list.
{
private:
	template<typename T>
	class Node
	{
	public:
		Node(T d) 
		{
			data = d;
			next = NULL;
			prev = NULL;
		};
		~Node() {};

		const T GetData() { return data; }
		Node<T>* GetNext() { return next; }
		Node<T>* GetPrev() { return prev; }

		void SetNext(Node<T>* n) { next = n; }
		void SetPrev(Node<T>* n) { prev = n; }
	private:
		T data; // the data stored in the list. Whatever we decide template should be.
		Node<T>* next; // pointer towards the next node.
		Node<T>* prev; // pointer towards the previous node. 
	};

public:
	DList(); // doubly  linked list.();
	~DList(); // doubly  linked list.();
	void AppendNode(T n); // appending a node at the end of the list;
	bool InsertNode(T n, int index); // insert a node at the index returns true if it worked false if the index was out of range. 
	void PrintList(); // function to print out the list on the command prompt.
	bool RemoveNodeByIndex(int index); // remove node at the index position.
	bool RemoveNode(T n); // removes the in the list matching the data. 
	void Clear(); // delete the entire linked list.
	bool IsEmpty(); // returns whether or not the list list is empty.
	int	 Size(); // returns the size of the linked list.

private:
	Node<T>* head;
	Node<T>* tail;
	int size;
};


template <typename T>
DList<T>::DList()
{
	head = NULL;
	tail = NULL;
	size = 0;
}
template <typename T>
DList<T>::~DList()
{
	Node<T>* current = head;
	while (current != NULL)
	{
		Node<T>* next = current->GetNext();
		delete current;
		current = next;
	}
}

template<typename T > 
void DList<T>::AppendNode(T n) 
{
	Node<T>* node = new Node<T>(n);
	if (head == NULL && tail == NULL) // then the list is empty;
	{
		head = node;
		tail = node;
		node->SetPrev(NULL);
		node->SetNext(NULL);
		++size;
	}
	else if (tail != NULL) // insert at the end;
	{
		tail->SetNext(node);
		node->SetPrev(tail);
		node->SetNext(NULL);
		tail = node;
		++size;
	}
}

template<typename T >
bool DList<T>::InsertNode(T n, int index)
{
	Node<T>* ite = head;
	int counter = 0;
	while (ite != NULL) 
	{
		if (counter == index)
		{
			Node<T>* node = new Node<T>(n);
			if (counter == 0)// then we are inserting at the head of the list and must set a new head.
			{
				head = node;
				node->SetPrev(NULL);
				node->SetNext(ite);
				ite->SetPrev(node);
			}
			else // inserting somwhere in the middle of the list.  
			{
				node->SetNext(ite);
				node->SetPrev(ite->GetPrev());
				ite->GetPrev()->SetNext(node);
				ite->SetPrev(node);
			}
			++size;
			return true;
		}
		++counter;
		ite = ite->GetNext();
	}
	return false;


}

template<typename T>
bool DList<T>::RemoveNode(T n) 
{
	Node<T>* iterator = head;
	while (iterator != NULL) 
	{
		if (iterator->GetData() == n)
		{
			//node found, remove this node. 
			if (iterator->GetPrev() != NULL && iterator->GetNext() != NULL) // middle of the list
			{
				iterator->GetPrev()->SetNext(iterator->GetNext());
				iterator->GetNext()->SetPrev(iterator->GetPrev());
			}
			else if (iterator == head) //removing the head
			{
				iterator->GetNext()->SetPrev(NULL);
				head = iterator->GetNext();
			}
			else if (iterator == tail) // removing the tail
			{
				iterator->GetPrev()->SetNext(NULL);
				tail = iterator->GetPrev();
			}
			delete iterator;
			--size;
			return true;
		}
		iterator = iterator->GetNext();
	}
	return false;
}

template<typename T>
bool DList<T>::RemoveNodeByIndex(int index)
{
	Node<T>* iterator = head;
	int counter = 0;
	while (iterator != NULL)
	{
		if (counter == index)
		{
			//node found, remove this node. 
			if (iterator == head) // removing the head.
			{
				iterator->GetNext()->SetPrev(NULL);
				head = iterator->GetNext();
				delete iterator;
			}
			else if (iterator == tail) // removing the tail.
			{
				iterator->GetPrev()->SetNext(NULL);
				tail = iterator->GetPrev();
				delete iterator;
			}
			else // removing somewhere in the middle.
			{
				iterator->GetPrev()->SetNext(iterator->GetNext());
				iterator->GetNext()->SetPrev(iterator->GetPrev());
			}
			--size;
			return true;
		}
		counter++;
		iterator = iterator->GetNext();
	}
	return false;
}

template<typename T>
void DList<T>::PrintList() 
{
	Node<T>* iterator;
	iterator = head;
	int counter = 0;
	cout << "---------------------------------------------------------------------------" << endl;
	while (iterator != NULL) 
	{
		cout << iterator->GetData()<<" ";
		iterator = iterator->GetNext();
		++counter;
		if (counter % 15 == 0)
			cout << endl;
	}
	cout <<endl << "---------------------------------------------------------------------------" << endl;
}

template<typename T>
bool DList<T>::IsEmpty() 
{
	return size == 0;
}

template<typename T>
int DList<T>::Size() 
{
	return size;
}

template<typename T>
void DList<T>::Clear() 
{
	Node<T>* current = head;
	while (current != NULL)
	{
		Node<T>* next = current->GetNext();
		delete current;
		current = next;
	}
	head = NULL;
	tail = NULL;
	size = 0;
}