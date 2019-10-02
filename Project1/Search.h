// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"

// returns FIRST array location matching the given item (based on the comparator)
// if not found, returns -(location to insert + 1)
template <typename T>
long long binarySearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator) {
	long long middle = array.getSize() / 2;

	long long location = comparator.compare(item, array.get(middle);

	if (location == 0) {
		return middle + 1;
	}

	else if (location > 1)

		return binarySearch(array, value, left, middle - 1);

	else

		return binarySearch(array, value, middle + 1, right);
}

#endif