#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"
#include "DrillingRecordComparator.h"
#include "Search.h"
#include "Sorter.h"
#include "Comparator.h"

/*
	TODO
		Determine which variables need to be declared before loop
		Make some of this separate functions
		time check
		date of first line matches original file
		retain most recently read in time data from the file
			Read files separtely and combine at the end
			linear search within file
			binary search when combining because sorted
		Sort after combining
		Make file read in separate
		Print internal tallies

*/
ResizableArray<DrillingRecord>* drillingArray = NULL;

// Only sorts unsorted part of array
void sortDrillingRecords(long unsigned int prevSize) {
	
	// Sorts by time
	DrillingRecordComparator* comparitor = new DrillingRecordComparator(1);

	long unsigned int size = drillingArray->getSize();

	// Goes through only previously unsorted part of the array to the end
	// This is where new data lies
	for (long unsigned int i = prevSize; i < size; i++) {

		// Places the new element into dR and stores time
		DrillingRecord dR = drillingArray->get(i);


		// Removes from previous place
		drillingArray->removeAt(i);

		long unsigned int j;
		// Searches older part of array for an element that is older 
		// if previously not sorted, new elements are sorted in order
		// cannot use binary search because array is not sorted
		while ((j < prevSize) && (comparitor->compare(drillingArray->get(j), dR) < 0)) {
			j++;
		}

		// Places new string in its place
		drillingArray->addAt(dR, j);
	}
}

void mergeDrillingRecords(ResizableArray<DrillingRecord>* newArray) {
	//Array dne therfore merged array is only array
	if (drillingArray == NULL) {
		drillingArray = newArray;
		sortDrillingRecords(0);
	}
	else {
		// Size of the array
		long unsigned int size = drillingArray->getSize();
		for (int i = 0; i < size; i++) {

			bool isFound = false;
			DrillingRecord dR = newArray->get(i);
			DrillingRecordComparator* comparator = new DrillingRecordComparator(1);

			long unsigned int j = 0;

			// Change to binary search
			while ((!isFound) && (j < drillingArray->getSize())) {
				// Checks to see if the times are the same
				if ((comparator->compare(dR, drillingArray->get(j))) == 0) {
					drillingArray->replaceAt(dR, j);
					isFound = true;
				}
				
				j++;
			}

			// Adds to the end if not found
			if (!isFound) {
				drillingArray->add(dR);
			}
		}

		// Sorts older part of array
		sortDrillingRecords(size);
	}
}

int main() {

	// File name that the user wants to input
	std::string fileName;
	// File opener
	std::ifstream inputFile;

	ResizableArray<DrillingRecord>* tempArray;
	int dataLines = 0;
	int validEntries = 0;

	// Initial file name input
	std::cout << "Enter data file name:" << std::endl;

	std::cin >> fileName;

	while (!(fileName.empty())) {

		inputFile.open(fileName);

		// Check if file exists
		if (inputFile.is_open()) {
			// If file exists

			// The drilling array
			DrillingRecord* drillingRecord = new DrillingRecord();

			DrillingRecordComparator* comparitor;

			// Temperary string variable
			std::string tempString;

			// Time array
			std::string date;

			bool isValid = true;

			// iterator
			unsigned int i;

			int lineCount = 0;

			tempArray = new ResizableArray<DrillingRecord>();
			
			// Throws away first line
			std::getline(inputFile, tempString);

			// Puts date in date variable
			std::getline(inputFile, tempString, ',');
			date = tempString;

			// While not at end of file
			while (!(inputFile.eof())) {
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

				std::getline(inputFile, tempString, ',');
				// If data is still valid
				if (isValid) {

					comparitor = new DrillingRecordComparator(1);

					drillingRecord->addString(tempString);

					// Itterate though time vector to check if time is equal to previous times
					if (binarySearch(*drillingRecord, *tempArray, *comparitor) > 0) {
						std::cout << "Duplicate timestamp " << tempString << " at line " << lineCount + 1 << "." << std::endl;
						isValid = false;
						break;
					}

					// adds new time to time array
					if (isValid) {
					}
				}

				// puts data in data array
				// gets first 15 data points that are separated by commas
				for (i = 0; i < 15; i++) {
					std::getline(inputFile, tempString, ',');

					drillingRecord->addNum(std::stof(tempString));
				}
				// gets final data point with newline
				std::getline(inputFile, tempString);
				drillingRecord->addNum(std::stof(tempString));

				// checks if data is valid
				for (i = 0; i < 16; i++) {
					if ((drillingRecord->getNum(i) <= 0) && isValid) {
						std::cout << "Invalid floating-point data at line " << lineCount + 1 << "." << std::endl;
						isValid = false;
						break;
					}
				}

				// If valid, increment dataPoints and add object to array
				if (isValid) {
					validEntries++;
					tempArray->add(*drillingRecord);
				}
				// If not valid, delete object and recreate it
				else {
					delete drillingRecord;
					drillingRecord = new DrillingRecord();
				}

				// Get next date parameter
				std::getline(inputFile, tempString, ',');

				dataLines++;
			}
			// Close file
			inputFile.close();

			// Merge files
			mergeDrillingRecords(tempArray);

		}
		else {
			// File does not exist
			std::cout << "File is not available." << std::endl;
		}

		// Re-get file name
		std::cout << "Enter data file name:" << std::endl;

		inputFile >> fileName;
	}

	// Output choice
	char choice;
	// File out
	std::ofstream outputFile;

	std::cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << std::endl;

	std::cin >> choice;
	while (choice != 'q') {
		switch (choice) {
		case 'o':
			// Checks for file to output to
			std::cout << "Enter output file name:" << std::endl;
			std::cin >> fileName;

			// Output to chosen file
			if (!(fileName.empty())) {
				// open file
				outputFile.open("fileName");

				// Loops until valid file is entered
				while (!(outputFile.is_open())) {
					std::cout << "File is not available." << std::endl;

					// Checks for file to output to
					std::cout << "Enter output file name:" << std::endl;
					std::cin >> fileName;

					// open file
					outputFile.open("fileName");
				}

				try {
					for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
						outputFile << drillingArray->get(i) << std::endl;
					}

					// Outputs internal tallies
					std::cout << "Data lines read: " << dataLines
						<< "; Valid drilling records: " << validEntries
						<< "; Drilling records in memory: " << drillingArray->getSize()
						<< std::endl;

					outputFile.close();
				}
				catch (ExceptionIndexOutOfRange e) {
					// It broke :(
				}
			}

			else {
				// Prints data (loop)
				try {
					for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
						outputFile << drillingArray->get(i) << std::endl;
					}

					// Outputs internal tallies
					std::cout << "Data lines read: " << dataLines
						<< "; Valid drilling records: " << validEntries
						<< "; Drilling records in memory: " << drillingArray->getSize()
						<< std::endl;
				}
				catch (ExceptionIndexOutOfRange e) {
					// It broke :(
				}
			}
			break;
		case 's':
			// sort stuff
			// column to sort
			int column;

			// Get column to sort
			std::cout << "Enter sort field (0-17):" << std::endl;
			std::cin >> column;

			// Make sure to check if valid
			if ((column < 0) && (column > 17)) {

				// invalid column
				// returns to loop
			}

			// Sorts data
			else {

				DrillingRecordComparator* comparitor = new DrillingRecordComparator(column);

				Sorter<DrillingRecord>::sort(*drillingArray, *comparitor);
			}

			break;

		case 'f':
			// find stuff
			// column to search

			// Get column to search
			std::cout << "Enter search field (0-17):" << std::endl;
			std::cin >> column;

			// Make sure to check if valid
			if ((column < 0) && (column > 17)) {

				// invalid column
			}

			// searches data
			else {
				int count = 0;
				if ((column >= 2) && (column <= 17)) {
					// Get value to sort
					double value;
					std::cout << "Enter positive field value:" << std::endl;
					std::cin >> value;

					// Searches through the array to get count
					for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
						if (value == drillingArray->get(i).getNum(column - 2)) {
							count++;
						}
					}

					std::cout << "Drilling records found: " << count << std::endl;

				}
				else if ((column == 0) || (column == 1)) {
					std::string value;
					std::cout << "Enter exact text on which to search:" << std::endl;
					std::cin >> value;

					// Searches through the array to get count
					for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
						if (value.compare(drillingArray->get(i).getString(column)) == 0) {
							count++;
						}
					}

					std::cout << "Drilling records found: " << count << std::endl;
				}
			}

			break;

			// Both these should break out of output

		case 'q':
		default:
			std::cout << "Thanks for using Driller." << std::endl;
			break;
			}
		}
}