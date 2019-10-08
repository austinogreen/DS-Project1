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
	
	// Parameters of binary search
	long long left = 0;
	long long right = array.getSize() - 1;
	long long middle;

	long long compare;

	// searches while left and right don't overlap
	while (left <= right) {

		middle = (right + left) / 2;

		compare = comparator.compare(item, array.get(middle));

		// item is less than the element so search in left half
		if (compare < 0) {
			right = middle - 1;
		}

		// item is greater than the element so search in right half
		else if (compare > 0) {
			left = middle + 1;
		}

		// item found
		else {
			return middle;
		}
	}
	// item not found, exit array
	return -(middle + 1);
}

#endif