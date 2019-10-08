// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "DrillingRecordComparator.h"

template <typename T>
class Sorter {
private:
    // additional member functions (methods) and variables (fields) may be added
public:
    static void sort(ResizableArray<T>& array, const Comparator<T>& comparator);
};


template<typename T>
void Sorter<T> :: sort(ResizableArray<T>& array, const Comparator<T>& comparator) {

	// Merge sort algorithm

	unsigned long i, j, k;

	unsigned long right = array.getSize() - 1;
	unsigned long middle = (right/2);

	// Temp Array
	ResizableArray<T>* tempArray = new ResizableArray<T>(array.getSize());

	i = 0;
	k = middle + 1;

	while ((i <= middle) && (k <= right)) {
		if (comparator.compare(array.get(i), array.get(k)) < 0) {
			tempArray->add(array.get(i));
			i++;
		}
		else {
			tempArray->add(array.get(k));
			k++;
		}
	}
	if (i > middle) {
		for (j = k; j <= right; j++) {
			tempArray->add(array.get(j));
		}
	}
	else {
		for (j = i; j <= middle; j++) {
			tempArray->add(array.get(j));
		}
	}
	for (j = 0; j <= right; j++) {
		array.replaceAt(tempArray->get(j), j);
	}
	delete tempArray;
}

#endif