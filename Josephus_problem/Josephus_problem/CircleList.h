#pragma once
#include <conio.h>

using namespace std;

class CircleListException {

};

template<class T> class CircleListElem {
	T data;
	CircleListElem* next;

public:
	CircleListElem(const T& adata, CircleListElem* anext);

	const T& getData() const;
	CircleListElem<T>* getNext();

	template<class> friend class CircleList;
};

template<class T> class CircleList {

	CircleList(const CircleList& list);
	//CircleList& operator =(const CircleList& list);
	CircleListElem<T>* start;

public:
	CircleList();
	~CircleList<T>();

	CircleListElem<T>* getStart();

	void setStart();
	void deleteFirst();
	void deleteAfter(CircleListElem<T>* ptr);
	void insertFirst(const T& data);
	void insertAfter(CircleListElem<T>* ptr, const T& data);
	int getSize();

	template<class> friend ostream& operator<<(ostream& out, CircleList& list);
};

template<class T> CircleListElem<T>::CircleListElem(const T& adata, CircleListElem<T>* anext) {
	data = adata;
	next = anext;
}

template<class T> CircleListElem<T>* CircleList<T>::getStart() {
	return start;
}

template<class T> const T& CircleListElem<T>::getData() const {
	return data;
}

template<class T> CircleListElem<T>* CircleListElem<T>::getNext() {
	return next;
}


template<class T> CircleList<T>::CircleList() {
	start = 0;
}
//check there
template<class T> CircleList<T>::~CircleList<T>() {
	cout << "launch destructor" << endl;
	cout << "list deleted";
}

template<class T> void CircleList<T>::deleteFirst() {

	if (start) {
		CircleListElem<T>* temp = start->next;
		delete start;
		start = temp;
	}
	else throw CircleListException();
}

template<class T> void CircleList<T>::insertFirst(const T& data) {
	CircleListElem<T>* second = start;
	start = new CircleListElem<T>(data, second);
}

template<class T> void CircleList<T>::deleteAfter(CircleListElem<T>* ptr) {
	if (ptr && ptr->next) {
		CircleListElem<T>* temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
	}
	else throw CircleListException();
}

template<class T> void CircleList<T>::insertAfter(CircleListElem<T>* ptr, const T& data) {
	if (ptr) {
		CircleListElem<T>* temp = ptr->next;
		ptr->next = new CircleListElem<T>(data, temp);
	}
}

template<class T> int CircleList<T>::getSize() {
	int counter = 1;
	CircleListElem<T>* ptr = getStart();
	ptr = ptr->getNext();
	if (!ptr) {
		throw CircleListException();
	}
	else {
		while (ptr && ptr != getStart()) {
			ptr = ptr->getNext();
			counter++;
		}
	}
	return counter;
}
//check there
template<class T> ostream& operator<<(ostream& out, CircleList<T>& list) {
	CircleListElem<T>* ptr = list.getStart();
	if (!ptr)
		out << "EMPTY ";
	else {
		out << "point start= " << ptr << endl;
		out << "adr start=" << &ptr << endl;
		out << "adr1=" << list.getStart() << " data1=" << ptr->getData() << endl;
		ptr = ptr->getNext();
		int i = 2;
		while (ptr && ptr != list.getStart()) {
			//out <<ptr<<' '<< ptr->getData() << ' '<<endl;
			out << "adr" << i << "=" << ptr << ' ' << "data" << i << "=" << ptr->getData() << ' ' << endl;
			i++;
			ptr = ptr->getNext();
		}
	}
	return out;
}
//check there
template<class T> void CircleList<T>::setStart() {
	CircleListElem<T>* ptr = start;
	while (ptr) {
		cout << ptr->data << " " << ptr << endl;
		_getch();
		ptr = ptr->next;

	}
	cout << ptr->data << " " << ptr << endl;

	ptr->next = start;
	//if (ptr) {
	//	CircleListElem<T>* temp = ptr;
	//	ptr->next = new CircleListElem<T>(temp->getData(), start);
	//	temp->next = temp->next->next;
	//}
}

