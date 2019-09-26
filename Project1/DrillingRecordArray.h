#ifndef DRILLING_RECORD_ARRAY_H
#define DRILLING_RECORD_ARRAY_H

#include "DrillingRecord.h"

const unsigned int DEFAULT_ARRAY_CAPACITY = 10;         // capacity used in no arg constructor

class DrillingRecordArray {
private:
	unsigned int capacity = DEFAULT_ARRAY_CAPACITY;     // maximum capacity, in records
	unsigned int size = 0;                              // actual number of items currently in array
	DrillingRecord* data = NULL;                        // pointer to array of records
public:
	DrillingRecordArray();                              // constructs array with default capacity
	DrillingRecordArray(unsigned int capacity);         // constructs array with specified capacity
	virtual ~DrillingRecordArray();                     // frees array space as object is deleted
	void add(DrillingRecord record);                    // adds record, increments size, doubles capacity as necessary
	DrillingRecord get(unsigned int index) const;       // returns (copy of) record at index
};
#endif