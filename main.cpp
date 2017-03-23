
#include <cstdlib>
#include <iostream>

#include "LinkedList.h"

using namespace std;

int main(int nArgs, char** czArgs) {

	LinkedList<int> list {1, 2, 3, 4};
	LinkedList<int>* l1 = new LinkedList<int> {1, 2, 3, 4};

	for (int i = 0; i < 10; i++) {
		list.add(5*i - 2);
		l1->add(5*i - 2);
	}

	for (int i = 0; i < 10; i++) {
		list.add(3);
	}

	cout << *l1 << endl << l1->size() << endl;
	cout << l1->remove(l1->size() - 1) << endl;
	cout << *l1 << endl;

	cout << list << endl << list.size() << endl;
	cout << list.remove(0) << endl;

	list[3] = -50;
	cout << list.lastIndexOf(3) << endl;

	list.removeAll();
	cout << list << endl;

	delete l1;
	return 0;

}
