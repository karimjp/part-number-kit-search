/**
 * @file Kit.h
 * @author  Karim Jana <karimjana@gmail.com>
 * @date	July, 2015.
 * @version 1.0
 * @details Proffesor Doug Ferguson - C++ class
 *
 * @brief This is the class file for Kit.
 */

#ifndef KIT_H_
#define KIT_H_
#include <iostream>
#include <map>
#include <array>
#include <vector>

class Kit
{
public:
	Kit();
	const std::array<std::string, 2>& getAttributes() const;
	void setAttributes(std::string quantity, std::string description);
	const std::string& getDescription() const;
	void setDescription(const std::string& description);
	const std::string& getPartNumber() const;
	void setPartNumber(const std::string& partNumber);
	const std::map<std::string, std::array<std::string, 2> >& getParts() const;
	void setParts(
			const std::map<std::string, std::array<std::string, 2> >& parts);
	const std::string& getQuantity() const;
	void setQuantity(const std::string& quantity);
	void ingestCsvInput(std::vector<std::vector<std::string>> csvFieldList);
	void addParts();
	const std::string& getKitName() const;
	void setKitName(const std::string& kitName);
	void printParts();

private:
	std::string kitName;
	std::string partNumber;
	std::string description;
	std::string quantity;
	std::array<std::string, 2> attributes;
	std::map<std::string, std::array<std::string, 2> > parts;
};//end class Kit

#endif /* KIT_H_ */
