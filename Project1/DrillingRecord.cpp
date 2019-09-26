#include "DrillingRecord.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record) {
	os << record.getString(0) + ";";
	os << record.getString(1) + ";";
	os << std::fixed;
	os << std::setprecision(2);

	for (int i = 0; i < 15; i++) {
		os << record.getNum(i) << ";";
	}
	// ensures that there isn't a semicolon at end of line
	os << record.getNum(15);
	return os;
}

void DrillingRecord::addNum(double num) {
	nums[numCtr] = num;
	if (numCtr == 15) {

		numCtr = 0;
	}
	else {
		numCtr++;
	}
	return;
}

void DrillingRecord::addString(std::string string) {
	strings[strCtr] = string;
	if (strCtr == 0) {
		strCtr++;
	}
	else {
		strCtr = 0;
	}
	return;
}

double DrillingRecord::getNum(unsigned int index) const {
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) const {
	return strings[index];
}