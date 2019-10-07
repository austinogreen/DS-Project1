// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"

template <typename T>
class Sorter {
private:
    // additional member functions (methods) and variables (fields) may be added
public:
    static void sort(ResizableArray<T>& array, const Comparator<T>& comparator);
};


template<typename T>
void Sorter<T> :: sort(ResizableArray<T>& array, const Comparator<T>& comparator) {
	T temp;
	for (int i = 0; i < n; i++) {

		for (int j = i; j < n; j++) {

			// If the element in i is less than the element in j, switches the two
			if ((comparator.compare(array[i],array[j])) < 0) {

				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	return;
}

#endif