// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "DrillingRecordComparator.h"

template <typename T>
class Sorter {
private:
public:
    static void sort(ResizableArray<T>& array, const Comparator<T>& comparator);
};

template<typename T>
void Sorter<T> :: sort(ResizableArray<T>& array, const Comparator<T>& comparator) {

	unsigned long i;
	long j;
	T temp;

	for (i = 1; i < array.getSize(); i++) {
		
		temp = array.get(i);
		j = i - 1;
		
		while ((j >= 0) && (comparator.compare(array.get(j), temp) > 0)) {
			array.replaceAt(array.get((unsigned long)j), j + 1);
			j--;
		}
		array.replaceAt(temp, j + 1);
	}
	return;
}

#endif