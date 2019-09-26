#include "DrillingRecordArray.h"
#include "DrillingRecord.h"

DrillingRecordArray::DrillingRecordArray() {
	data = new DrillingRecord[DEFAULT_ARRAY_CAPACITY];
}
DrillingRecordArray::DrillingRecordArray(unsigned int capacity) {
	data = new DrillingRecord[capacity];
}

DrillingRecordArray::~DrillingRecordArray() {
	if (data != NULL) {
		delete[] data;
	}
	data = NULL;
	size = 0;
}

void DrillingRecordArray::add(DrillingRecord record) {
	// doubles drilling array size if capacity is reached
	if (size >= capacity) {
		DrillingRecord* newDR = new DrillingRecord[capacity * 2];

		// Copies contents of old array into the new one
		for (unsigned int i = 0; i < capacity; i++) {
			newDR[i].addString(data[i].getString(0));
			newDR[i].addString(data[i].getString(1));
			for (int j = 0; j < 16; j++) {
				newDR[i].addNum(data[i].getNum(j));
			}
		}

		// Updates the capacity
		capacity *= 2;

		// Delete old data
		delete[] data;

		// Updates old data array to new one
		data = newDR;
	}
	data[size] = record;
	size++;
}

DrillingRecord DrillingRecordArray::get(unsigned int index) const {
	return data[index];
}