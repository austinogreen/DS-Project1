#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <iomanip>
#include <vector>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"

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

int main() {

	// File name that the user wants to input
	std::string fileName;
	// File opener
	std::ifstream inputFile;

	// Initial file name input
	std::cout << "Enter data file name:" << std::endl;

	std::cin >> fileName;

	while (!(fileName.empty())) {

		inputFile.open(fileName);

		// Check if file exists
		if (inputFile.is_open()) {
			// If file exists

			// The drilling array
			ResizableArray<DrillingRecord>* drillingArray = new ResizableArray<DrillingRecord>();
			DrillingRecord* drillingRecord = new DrillingRecord();

			// Temperary string variable
			std::string tempString;

			// Time array
			std::string date;

			bool isValid = true;

			// iterator
			unsigned int i;
			// Line count for error messages and time vector
			int lineCount = 0;
			// Amount of valid data
			int dataPoints = 0;

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
					// Itterate though time vector to check if time is equal to previous times
					for (time) {
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
				std::getline(inputFile, tempString, ',');
			}
			// Close file
			inputFile.close();

		}
		else {
			// File does not exist
			std::cout << "File is not available." << std::endl;
		}

		// Reget file name
		std::cout << "Enter data file name:" << std::endl;

		inputFile >> fileName;
	}

	// File Output (Make into function)

	// Output choice
	char choice;
	// File out
	std::string fileName;
	std::ofstream outputFile;

	std::cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << std::endl;

	std::cin >> choice;

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
				while (!(outputFile.is_open()) {
					std::cout << "File is not available." << std::endl;

					// Checks for file to output to
					std::cout << "Enter output file name:" << std::endl;
					std::cin >> fileName;

					// open file
					outputFile.open("fileName");
				}

				try {
					for (int i = (dataPoints - 1); i >= 0; i--) {
						outputFile << drillingArray->get(i) << std::endl;
					}
					outputFile.close();
				}
				catch (ExceptionIndexOutOfRange e) {
					// It broke :(
				}
			}
			else {
				// Prints data (loop)
				try {
					for (int i = (dataPoints - 1); i >= 0; i--) {
						std::cout << drillingArray->get(i) << std::endl;
					}
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

			break;

		case 'f':
			// find stuff
			// columnto search
			int column;

			// Get column to search
			std::cout << "Enter search field (0-17):" << std::endl;
			std::cin >> column;

			if ((column >= 2) && (column <= 17)) {
				// Get value to sort
				double value;
				std::cout << "Enter positive field value:" << std::endl;
				std::cin >> value;

			}
			else if ((column == 0) || (column == 1)) {
				std::string value;
				std::cout << "Enter exact text on which to search:" << std::endl;
				std::cin >> value;
			}
			else {
				// invalid column
			}

			// Make sure to check if valid

			break;

		// Both these should break out of output
		case 'q':
		default:
			std::cout << "Thanks for using Driller." << std::endl;
			break;
	}
}