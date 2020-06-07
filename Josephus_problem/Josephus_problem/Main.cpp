#include <iostream>
#include "circleList.h"

using namespace std;

int getSize2();

int getNumber();

int main() {
	// 3 6 9 4 8 5 2 7 1
	int size = 9;//getSize2();
	int number = 3;// getNumber();

	CircleList<int> list;
	list.insertFirst(1);
	CircleListElem<int>* ptr = list.getStart();

	for (int i = 1; i < size; i++) {//creating start from 2 to 13
		list.insertAfter(ptr, i + 1);
		ptr = ptr->getNext();
	}
	cout << list;
	//list.setStart();

	//int counter = 0;
	//for (int i = 0; counter < size; i++) {
	//	if ((i + 1) % (number - 1) == 0) {
	//		cout << ptr->getNext()->getData() << ' ';
	//		list.deleteAfter(ptr);
	//		counter++;
	//	}
	//	ptr = ptr->getNext();
	//}
	return 0;
}


int getSize2() {
	int size;
	cout << "enter number of people:";
	cin >> size;
	return size;
}

int getNumber() {
	int number;
	cout << "enter frequency of killing:";
	cin >> number;
	return number;
}
