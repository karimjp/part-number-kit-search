/**
 * @file Kit.cpp
 * @author  Karim Jana <karimjana@gmail.com>
 * @date	July, 2015.
 * @version 1.0
 * @details Proffesor Doug Ferguson - C++ class
 *
 * @brief This is the implementation file for Kit.
 */

#include "Kit.h"
Kit::Kit()
{
	setKitName("");
	setPartNumber("");
	setQuantity("");
	setDescription("");
	setAttributes("", "");

}//end Kit()

const std::string& Kit::getKitName() const
{
	return kitName;
}//end getKitName()

void Kit::setKitName(const std::string& kitName)
{
	this->kitName = kitName;
}//end setKitName()

const std::array<std::string, 2>& Kit::getAttributes() const
{
	return attributes;
}//end getAttributes()

void Kit::setAttributes(std::string quantity, std::string description)
{
	std::array<std::string, 2> attributes;
	attributes[0] = quantity;
	attributes[1] = description;

	this->attributes = attributes;
}//end setAttributes()

const std::string& Kit::getDescription() const
{
	return description;
}//end getDescription()

void Kit::setDescription(const std::string& description)
{
	this->description = description;
}//end setDescription()

const std::string& Kit::getPartNumber() const
{
	return partNumber;
}//end getPartNumber()

void Kit::setPartNumber(const std::string& partNumber)
{
	this->partNumber = partNumber;
}//end setPartNumber()

const std::map<std::string, std::array<std::string, 2> >& Kit::getParts() const
{
	return parts;
}//end getParts()

void Kit::setParts(
		const std::map<std::string, std::array<std::string, 2>>& parts)
{
	this->parts = parts;
}//end setParts()

const std::string& Kit::getQuantity() const
{
	return quantity;
}//end getQuantity()

void Kit::setQuantity(const std::string& quantity)
{
	this->quantity = quantity;
}//setQuantity()

void Kit::ingestCsvInput(std::vector<std::vector<std::string>> csvFieldList)
{
	std::vector<std::string> csvField;
	std::string firstField;
	std::string quantity;
	std::string partNumber;
	std::string description;
	int line;

	for (int i = 0; i < csvFieldList.size(); i++)
	{

		line = i;
		csvField = csvFieldList[i];

		if (line == 0)
		{
			firstField = csvField[0];
			setKitName(firstField);
		}

		//checks if field is size 3 and if not header
		if (csvField.size() >= 3 && csvField[0] != "Qty")
		{
			quantity = csvField[0];
			partNumber = csvField[1];
			description = csvField[2];
			setQuantity(quantity);
			setPartNumber(partNumber);
			setDescription(description);
			setAttributes(getQuantity(), getDescription());
			addParts();
		}
	}
}//end ingestCsvInput()

void Kit::addParts()
{

	std::map<std::string, std::array<std::string, 2>> parts = getParts();
	//check for key existence before inserting

	if (parts.count(getPartNumber()) == 0)
	{
		parts[getPartNumber()] = getAttributes();
		setParts(parts);
	} else
	{
		std::cout << "Warning: Overwriting part number " << getPartNumber()
				<< " in " << getKitName() << std::endl;
		//std::exit(0);
	}

}//end addParts()

void Kit::printParts()
{
	std::map<std::string, std::array<std::string, 2>> parts = getParts();
	std::string partNumber;
	std::string quantity;
	std::string description;
	std::cout << "Kit Name: " << getKitName() << std::endl;
	for (auto elem : parts)
	{
		partNumber = elem.first;
		quantity = elem.second[0];
		description = elem.second[1];
		std::cout << "Part Number: " << partNumber << std::endl;
		std::cout << "Quantity: " << quantity << std::endl;
		std::cout << "Description: " << description << std::endl;
	}
	std::cout << std::endl;
}//end printParts()

