#include "DrillingRecordComparator.h"
#include "Comparator.h"
#include "DrillingRecord.h"
DrillingRecordComparator::DrillingRecordComparator(unsigned int column) {
	column = column;
}

// returns -1 if item1 < item2, 0 if item1 == item2, +1 if item1 > item2
int DrillingRecordComparator :: compare(const DrillingRecord& item1, const DrillingRecord& item2) const {
	
}