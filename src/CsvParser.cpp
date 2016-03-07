/**
 * @file CsvParser.cpp
 * @author  Karim Jana <karimjana@gmail.com>
 * @date	June, 2015.
 * @version 1.0
 * @details Proffesor Doug Ferguson - C++ class
 *
 * @brief This is CsvParser implemmentation file.
 * The core of this file is the string tokenizer that can return each csv line as fields.
 *
 */
#include "CsvParser.h"
#include "dirent.h"
#include <string>
#include <algorithm>

CsvParser::CsvParser()
{
	setEndOfLineDelimiter('\r');
	//setEndOfLineDelimiter('\n');
	setCsvDelimeter(",");

} // end CsvParser()

/**
 * tokenizeString
 * This function tokenizes any string with a defined delimiter.
 * http://stackoverflow.com/questions/9823263/string-tokenization-in-c-including-delimiter-characters
 * @param str
 * @param delimiters
 * @return tokens
 */
std::vector<std::string> CsvParser::tokenizeString(const std::string& str,
		const std::string& delimiters)
{
	std::string field;
	std::vector<std::string> tokens;
	// Skip delimiters at beginning.
	std::string::size_type escapePos = str.find_first_of('"');
	escapePos += 1;
	std::string::size_type endEscapePos = str.find_first_of('"', escapePos);

	std::string::size_type lastPos = str.find_first_not_of(delimiters);
	// Find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{ // Found a token, add it to the vector.
		bool escape;
		bool endOfString;
		std::string::size_type pos1;
		field = cleanField(str.substr(lastPos, pos - lastPos));
		tokens.push_back(field);
		// Skip delimiters.  Note the "not_of"
		escapePos = str.find_first_of('"');
		escapePos += 1;
		endEscapePos = str.find_first_of('"', escapePos);
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
		escape = bool(
				std::string::npos != escapePos
						&& std::string::npos != endEscapePos);
		endOfString = bool(
				std::string::npos != pos || std::string::npos != lastPos);

		if (escape && endOfString)
		{
			if (escapePos < pos && escapePos < endEscapePos)
			{
				pos = lastPos;
				// Skip delimiters.  Note the "not_of"
				lastPos = str.find_first_not_of('"', pos);
				// Find next "non-delimiter"
				pos = str.find_first_of('"', lastPos);
			}
		}
	}
	return tokens;
} // end tokenizeString()

std::vector<std::string> CsvParser::listFiles(const char* path)
{
	std::vector<std::string> fileList;
	DIR* dirFile = opendir(path);
	if (dirFile)
	{
		struct dirent* hFile;
		errno = 0;
		while ((hFile = readdir(dirFile)) != NULL)
		{
			if (!strcmp(hFile->d_name, "."))
				continue;
			if (!strcmp(hFile->d_name, ".."))
				continue;

			// dirFile.name is the name of the file. Do whatever string comparison
			// you want here. Something like:
			if (strstr(hFile->d_name, ".csv"))
				fileList.push_back(hFile->d_name);
		}
		closedir(dirFile);
	}
	return fileList;
}//end listFiles()

void CsvParser::setEndOfLineDelimiter(char endOfLineDelimiter)
{
	this->endOfLineDelimiter = endOfLineDelimiter;
} // end setEndOfLineDelimeter()

char CsvParser::getEndOfLineDelimiter()
{
	return this->endOfLineDelimiter;
} // end getEndOfLineDelimiter()

void CsvParser::setCsvDelimeter(std::string csvDelimiter)
{
	this->csvDelimiter = csvDelimiter;
} // end setCsvDelimeter()

std::string CsvParser::getCsvDelimiter()
{
	return this->csvDelimiter;
} // end getCsvDelimiter()

std::string CsvParser::cleanField(std::string field)
{
	std::vector<char> remove { '\n', };
	for (int i = 0; i < remove.size(); i++)
	{
		field.erase(std::remove(field.begin(), field.end(), remove[i]),
				field.end());
	}
	return field;

}//end cleanField()
