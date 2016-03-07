/**
 * @file main.cpp
 * @author  Karim Jana <karimjana@gmail.com>
 * @date	July, 2015.
 * @version 1.0
 * @details Proffesor Doug Ferguson - C++ class
 *
 * @brief Main program. Search of part number occurs here and
 * creation of search structure from files.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include "CsvParser.h"
#include "Kit.h"
using namespace std;

int main()
{
	CsvParser parser;
	std::vector<std::string> fileList;
	string rootPath = "csvFile/";
	fileList = parser.listFiles(rootPath.c_str());
	//File names to read: auto populated
	std::vector<std::string> csvFileNames = fileList;
	ifstream readFileStream;
	string fileName;
	string line;
	std::vector<std::string> csvField;
	std::vector<std::vector<std::string>> csvFieldList;
	int lineNumber = 0;

	//for testing selected files purposes
	bool test = false;
	if (test)
	{
		csvFileNames.clear();
		csvFileNames.push_back(fileList[0]);
	} //end testing clause

	//Iterate for each of the fileNames
	for (int i = 0; i < csvFileNames.size(); ++i)
	{
		//Kit kit;
		fileName = rootPath + csvFileNames[i];
		readFileStream.open(fileName);
		if (!readFileStream)
		{
			cout << "Couldn't open: " << fileName << endl;
			return -1;
		}

		if (readFileStream.peek() == std::ifstream::traits_type::eof())
		{
			cout << "Warning: (Skipping) File  is empty:" << endl;
			cout << fileName << endl;
			continue;
		}

		//print file name to be process
		cout << "File: " << fileName << endl;
		//read each line until end of file is reach
		while (getline(readFileStream, line, parser.getEndOfLineDelimiter()))
		{
			lineNumber++;

			//cout <<line<<endl;
			csvField = parser.tokenizeString(line, parser.getCsvDelimiter());

			if (lineNumber == 1 && csvField.size() == 0)
			{
				cout << "Warning: (Skipping) Csv File  is empty:" << endl;
				cout << fileName << endl;
				break;
			}
			csvFieldList.push_back(csvField);
		}
		kit.ingestCsvInput(csvFieldList);
		kits.push_back(kit);
		lineNumber = 0;
		csvFieldList.clear();
		readFileStream.close();
	}

	//create search structure
	for (auto kit : kits)
	{
		std::string partNumber;
		for (auto element : kit.getParts())
		{
			partNumber = element.first;
			searchKitStruct[partNumber].push_back(kit);
		}
	}

	//search partNumbers
	for (auto searchTerm : partNumbersToSearch)
	{
		std::vector<Kit> resultKits = searchKitStruct[searchTerm];
		for (auto kit : resultKits)
		{
			cout << "KitName: " << kit.getKitName() << std::endl;
			cout << "PartName: " << kit.getParts().find(searchTerm)->first
					<< std::endl;
			cout << "Quantity: " << kit.getParts().find(searchTerm)->second[0]
					<< std::endl;
			cout << "Description: "
					<< kit.getParts().find(searchTerm)->second[1] << std::endl;
		}
	}
	return 0;
}//end main()
