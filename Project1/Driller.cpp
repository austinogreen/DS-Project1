#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"

int main() {

	// The drilling array
	ResizableArray<DrillingRecord>* drillingArray = new ResizableArray<DrillingRecord>();
	DrillingRecord* drillingRecord = new DrillingRecord();

	// Temperary string variable
	std::string tempString;

	// Time array
	std::string date;
	std::vector<std::string> time;

	bool isValid = true;

	// iterator
	unsigned int i;
	// Line count for error messages and time vector
	int lineCount = 0;
	// Amount of valid data
	int dataPoints = 0;

	// Throws away first line
	std::getline(std::cin, tempString);

	// Puts date in date variable
	std::getline(std::cin, tempString, ',');
	date = tempString;

	// While not at end of file
	while (!tempString.empty()) {
		// preps the valid flag to true
		isValid = true;

		// Check if date is the same
		if (tempString.compare(date) != 0) {
			std::cout << "Non-matching date stamp " << tempString << " at line " << lineCount + 1 << "." << std::endl;
			isValid = false;
		}
		if (isValid) {
			drillingRecord->addString(tempString);
		}

		std::getline(std::cin, tempString, ',');
		// If data is still valid
		if (isValid) {
			// Itterate though time vector to check if time is equal to previous times
			for (std::string s : time) {
				// gives error if so
				if (tempString.compare(s) == 0) {
					std::cout << "Duplicate timestamp " << tempString << " at line " << lineCount + 1 << "." << std::endl;
					isValid = false;
					break;
				}
			}

			// adds new time to time array
			if (isValid) {
				drillingRecord->addString(tempString);
			}
		}
		time.push_back(tempString);

		// puts data in data array
		// gets first 15 data points that are separated by commas
		for (i = 0; i < 15; i++) {
			std::getline(std::cin, tempString, ',');

			drillingRecord->addNum(std::stof(tempString));
		}
		// gets final data point with newline
		std::getline(std::cin, tempString);
		drillingRecord->addNum(std::stof(tempString));

		// checks if data is valid
		for (i = 0; i < 16; i++) {
			if ((drillingRecord->getNum(i) <= 0) && isValid) {
				std::cout << "Invalid floating-point data at line " << lineCount + 1 << "." << std::endl;
				isValid = false;
				break;
			}
		}

		// Incrememnt line count
		lineCount++;
		
		// If valid, increment dataPoints and add object to array
		if (isValid) {
			dataPoints++;
			drillingArray->add(*drillingRecord);
		}
		// If not valid, delete object and recreate it
		else {
			delete drillingRecord;
			drillingRecord = new DrillingRecord();
		}

		// Get next date parameter
		std::getline(std::cin, tempString, ',');
	}

	// Prints data (loop)
	for (int i = (dataPoints - 1); i >= 0; i--) {
		try {
			std::cout << drillingArray->get(i) << std::endl;
		}
		catch (ExceptionIndexOutOfRange e) {
			// It broke :(
		}
	}
}