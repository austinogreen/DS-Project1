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
	// Goes through only previously unsorted part of the array to the end
	// This is where new data lies
	for (int i = prevSize; i < drillingArray->getSize(); i++) {

		// Places the new element into dR and stores time
		DrillingRecord dR = drillingArray->get(i);
		std::string time = dR.getString(1);

		int j;
		// Searches while it is smaller than previous size and less than time
		// if previously not sorted, new elements are sorted in order
		for (j = 0; ((j < prevSize) && (time.compare(drillingArray->get(j).getString(1))) < 1); j++) {}

		// Places new string in its place
		drillingArray->addAt(dR, j);
		// Removes from previous place
		drillingArray->removeAt(i);
	}
}

#endif