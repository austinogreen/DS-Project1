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

using namespace std;

ResizableArray<DrillingRecord>* drillingArray = NULL;

// string to dump bad data
string garbage;

void mergeDrillingRecords(ResizableArray<DrillingRecord>* newArray) {
	//Array dne therfore merged array is only array
	if (drillingArray == NULL) {
		drillingArray = new ResizableArray<DrillingRecord>();

		unsigned long size = newArray->getSize();
		for (unsigned int i = 0; i < size; i++) {
			drillingArray->add(newArray->get(i));
		}
	}
	else {
		// Size of the array
		long unsigned int size = newArray->getSize();
		for (long unsigned int i = 0; i < size; i++) {

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
	}

	// Sorts older part of array
	DrillingRecordComparator* comparator = new DrillingRecordComparator(1);

	Sorter<DrillingRecord>::sort(*drillingArray, *comparator);
}

int main() {

	// File name that the user wants to input
	string fileName;
	// File opener
	ifstream inputFile;

	ResizableArray<DrillingRecord>* tempArray;
	int dataLines = 0;
	int validEntries = 0;

	bool hasOpened = false;

	// Initial file name input
	cout << "Enter data file name: ";

	getline(cin, fileName);

	while (!(fileName.empty())) {

		inputFile.open(fileName);

		// Check if file exists
		if (inputFile.is_open()) {
			// If file exists
			hasOpened = true;

			// The drilling array
			DrillingRecord* drillingRecord = new DrillingRecord();

			// Temperary string variable
			string tempString;

			// Time array
			string date;

			bool isValid = true;

			// iterator
			unsigned int i;

			int lineCount = 0;

			tempArray = new ResizableArray<DrillingRecord>();
			
			// Throws away first line
			getline(inputFile, garbage);

			// Puts date in date variable
			getline(inputFile, tempString, ',');
			date = tempString;

			// While not at end of file
			while (!(inputFile.eof())) {
				// preps the valid flag to true
				isValid = true;

				// Check if date is the same
				if (tempString.compare(date) != 0) {
					cout << "Non-matching date stamp " << tempString << " at line " << lineCount + 1 << "." << endl;
					isValid = false;
				}
				if (isValid) {
					drillingRecord->addString(tempString);
				}

				getline(inputFile, tempString, ',');
				// If data is still valid
				if (isValid) {

					drillingRecord->addString(tempString);

					// Itterate though time vector to check if time is equal to previous times
					for (unsigned long i = 0; i < tempArray->getSize(); i++) {
						if (tempArray->get(i).getString(1).compare(tempString) == 0) {
							cout << "Duplicate timestamp " << tempString << " at line " << lineCount + 1 << "." << endl;
							isValid = false;
							break;
						}
					}
				}

				// puts data in data array
				// gets first 15 data points that are separated by commas
				for (i = 0; i < 15; i++) {
					getline(inputFile, tempString, ',');

					drillingRecord->addNum(stod(tempString));
				}
				// gets final data point with newline
				getline(inputFile, tempString);
				drillingRecord->addNum(stod(tempString));

				// checks if data is valid
				for (i = 0; i < 16; i++) {
					if ((drillingRecord->getNum(i) <= 0) && isValid) {
						cout << "Invalid floating-point data at line " << lineCount + 1 << "." << endl;
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
				getline(inputFile, tempString, ',');

				lineCount++;
				dataLines++;
			}
			// Close file
			inputFile.close();

			// Merge files
			mergeDrillingRecords(tempArray);

			delete tempArray;

		}
		else {
			// File does not exist
			cout << "File is not available." << endl;
		}

		// Re-get file name
		cout << "Enter data file name: ";

		getline(cin, fileName);
	}

	// if there is a valid input
	if (hasOpened) {

		// Output choice
		char choice;
		string temp;
		// File out
		ofstream outputFile;
		// Column the data is currently sorted by
		int sortedColumn = 1;

		// comparator
		DrillingRecordComparator* comparator;

		// Temp Drilling Record
		DrillingRecord* tempDR = new DrillingRecord();

		cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << endl;

		cin >> choice;
		getline(cin, temp);

		while (choice != 'q') {
			switch (choice) {
			case 'o':
				// Checks for file to output to
				cout << "Enter output file name: ";
				getline(cin, fileName);

				// Output to chosen file
				if (!(fileName.empty())) {
					// open file
					outputFile.open(fileName);

					// Loops until valid file is entered
					while (!(outputFile.is_open())) {
						cout << "File is not available." << endl;

						// Checks for file to output to
						cout << "Enter output file name: ";
						getline(inputFile, fileName);

						// open file
						outputFile.open(fileName);
					}

					try {
						for (long unsigned int i = 0; i < drillingArray->getSize(); i++) {
							outputFile << drillingArray->get(i) << endl;
						}

						// Outputs internal tallies
						outputFile << "Data lines read: " << dataLines
							<< "; Valid drilling records read: " << validEntries
							<< "; Drilling records in memory: " << drillingArray->getSize()
							<< endl;

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
							cout << drillingArray->get(i) << endl;
						}

						// Outputs internal tallies
						cout << "Data lines read: " << dataLines
							<< "; Valid drilling records read: " << validEntries
							<< "; Drilling records in memory: " << drillingArray->getSize()
							<< endl;
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
				cout << "Enter sort field (0-17):" << endl;
				cin >> column;
				getline(cin, garbage);

				// Make sure to check if valid
				if ((column < 0) && (column > 17)) {

					// invalid column
					// returns to loop
				}

				// Sorts data
				else {

					comparator = new DrillingRecordComparator(column);

					Sorter<DrillingRecord>::sort(*drillingArray, *comparator);

					sortedColumn = column;
				}

				break;

			case 'f':
				// Get column to search
				cout << "Enter search field (0-17):" << endl;
				cin >> column;
				getline(cin, garbage);

				// whether data is sorted by indicated column to choose which search to preform
				bool isSorted = (column == sortedColumn);

				// Make sure to check if valid
				if ((column < 0) && (column > 17)) {

					// invalid column
				}

				// Column is the sorted column therefore can use binary search
				else {
					if ((column >= 2) && (column <= 17)) {
						// Get value to sort
						double value;
						cout << "Enter positive field value: " << endl;
						cin >> value;
						getline(cin, garbage);
						tempDR->setNum(value, column - 2);
					}
					else if ((column == 0) || (column == 1)) {
						string value;
						cout << "Enter exact text on which to search: " << endl;
						getline(cin, value);
						tempDR->setString(value, column);
					}

					comparator = new DrillingRecordComparator(column);

					ResizableArray<long long>* idxArray = search(*tempDR, *drillingArray, isSorted, *comparator);

					unsigned long count = idxArray->getSize();

					// idx is negative therefore element dne
					if (isSorted && (idxArray->get(0) < 0)) {
						count = 0;
					}
					else {
						for (unsigned long i = 0; i < count; i++) {
							cout << drillingArray->get((unsigned long) idxArray->get(i)) << endl;
						}
					}

					cout << "Drilling records found: " << count << endl;
				}

				break;
			}

			cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << endl;
			cin >> choice;
			getline(cin, garbage);
		}
		cout << "Thanks for using Driller." << endl;
		return 0;
	}
}