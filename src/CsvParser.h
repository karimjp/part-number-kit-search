/**
 * @file CsvParser.h
 * @author  Karim Jana <karimjana@gmail.com>
 * @date	June, 2015.
 * @version 1.0
 * @details Proffesor Doug Ferguson - C++ class
 *
 * @brief This is my CsvParser definition file.
 *
 */
#include <iostream>
#include <vector>

#ifndef CSVPARSER_H_
#define CSVPARSER_H_
class CsvParser
{
public:
	CsvParser();
	std::vector<std::string> tokenizeString(const std::string& str,
			const std::string& delimiters);
	std::vector<std::string> listFiles(const char* path);
	std::string cleanField(std::string field);
	void setEndOfLineDelimiter(char endOfLineDelimiter);
	char getEndOfLineDelimiter();
	void setCsvDelimeter(std::string csvDelimiter);
	std::string getCsvDelimiter();
private:
	char endOfLineDelimiter;
	std::string csvDelimiter;
};//end class CsvParser

#endif /* CSVPARSER_H_ */
