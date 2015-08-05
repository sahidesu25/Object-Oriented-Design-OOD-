#ifndef DISPLAY
#define DISPLAY
///////////////////////////////////////////////////////////////////////
// Display.h -Displays output based on the calls from the Executive  //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: XMLDocumentModel, Project #2, Spring 2015            //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//Module Operations:
// ==============
//*  Has all the functions which displays the operations performed on the XmlDocument
//*  These are called by the Executive.
//*
//*Required Files
//*--------------------
//* Executive.cpp
//*
//* Maintaiance History
//*--------------------
//* -first release

#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/XmlElementParts/Tokenizer.h"
#include "../XmlElementParts/XmlElementParts/xmlElementParts.h"
using namespace std;

class Display
{
	
public:

	void display_tree(XmlProcessing::XmlDocument::sPtr docelement,int option)
	{
		if (option == 1)
		{
			std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
			std::cout << "Demonstrating Xml tree buildingwith file as input" << std::endl;
			std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
		}
		if (option == 2)
		{
			std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
			std::cout << "Demonstrating Xml tree building with string as input" << std::endl;
			std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;

		}
		std::cout<<docelement->toString();
	}
	void display_attributesearch(std::vector<XmlProcessing::XmlDocument::sPtr> arrtibresult,int option,std::string name,std::string value)
	{
		    std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
			std::cout << "Demonstrating ArrtibuteSearch which returns a smart pointer to the found attribute name and value pair" << std::endl;
			std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		if (option == 1)
		{
			std::cout << "\t" << "1)" << "Returning a smart pointer for the tagged value" << std::endl;
			std::cout << "\t" << "\t" << "name : " << name << " " << "value : " << value;
		}
		if (option == 2)
		{
			std::cout << "\t" << std::endl << "2)" << "Returning a smart pointer for the delaration " << std::endl;
			std::cout << "\t" << "\t" << "name : " << name << " " << "value : " << value;
		}
		if (option == 3)
		{
			std::cout << "\t" << std::endl << "3)" << "Returning a smart pointer for the processing Instruction " << std::endl;
			std::cout << "\t" << "\t" << "name : " << name << " " << "value : " << value;
		}
		if (arrtibresult.size() != 0)
		{ if (option==1)
			std::cout << std::endl << "\t" << " " << " " << " " << "The Search Result : " << arrtibresult.at(0)->value();
		    else
				std::cout << std::endl << "\t" << " " << " " << " " << "The Search Result : " << arrtibresult.at(0)->toString();
		}
		else
			std::cout << "Element not found";
	}
	void display_Tagsearch(std::vector<XmlProcessing::XmlDocument::sPtr> tagresult, std::string tag_name)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demonstrating TagSearch which returns a smart pointer to the found tag name" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		if (tagresult.size() != 0)
		{
			cout << "The given tag : " << tag_name << " " << "has occured " << tagresult.size() << " " <<" times";
			for (auto tag : tagresult)
			{
				std::cout << std::endl<<"Tagname" << ":" << tag->value();
			}

		}
		else
		{
			cout << std::endl << "Tags are not found for the specified value" << std::endl;
		}
		

	}

	void display_addchild(bool result, int option, std::string parent, std::string child, XmlProcessing::XmlDocument::sPtr docelement)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demonstrating Add child to the elements which can have child references" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		if (option == 1)
		{
			std::cout << "\t" << "1)" << "Add Commentchild"<<" "<<child<<" "<<" to the tagged element"<<" "<<parent<< std::endl;
		}
		if (option == 2)
		{
			std::cout << "\t" << std::endl << "2)" << "Adding ProcInstruction child"<<" "<<child<< "to the tagged element "<<" "<<parent << std::endl;
		}
		if (option == 3)
		{
			std::cout << "\t" << std::endl << "3)" << "Adding tagged Elementchild"<<" "<<child<<" to the tagged element " <<" "<<parent<< std::endl;
		}
		if (option == 4)
		{
			std::cout << "\t" << std::endl << "4)" << "Adding child "<<" "<<child<<"to the doc element "<<" "<<parent << std::endl;
		}
		if (option == 5)
		{
			std::cout << "\t" << std::endl << "4)" << "Adding text child" << " " << child << "to the tagged element which has no child " << " " << parent << std::endl;

		}
		if (result)
		{
			cout << "Result of the tree after adding " << std::endl;
			std::cout << docelement->toString();

		}
		else
			std::cout << "Addition of child was not sucessful";
	}
	void display_removechild(bool result, std::string parent, std::string node_to_remove, XmlProcessing::XmlDocument::sPtr docelement)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demostrating Remove child given a parent tag" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t" << std::endl<< "Removing Elementchild" << " " << node_to_remove << " from parent " << " " << parent << std::endl;
		if (result)
		{
			cout << "Result of the tree after removing " << std::endl;
			std::cout << docelement->toString();

		}
		else
			std::cout << "Addition of child was not sucessful";

	}
	void display_removechildbyattribute(bool result, std::string parent, std::string attribute_name,std::string attribute_value,  XmlProcessing::XmlDocument::sPtr docelement)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demostrating Remove child based on given attribute name and attribute value" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t" << std::endl << "Removing Elementchild with attribute name" << " " << attribute_name <<" "<<"and attribute value"<<" "<<attribute_value<< " from parent " << " " << parent << std::endl;
		if (result)
		{
			cout << "Result of the tree after removing " << std::endl;
			std::cout << docelement->toString();

		}
		else
			std::cout << "Addition of child was not sucessful";

	}

	void display_Add_attributes(bool result,int option,std::string elementname, std::string attributename, std::string attributevalue, XmlProcessing::XmlDocument::sPtr docelement)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demostrating Addition of attributename"<<" "<<attributename<<" "<<"and"<<" "<<attributevalue<<" "<<" for the elementname"<<" "<<elementname << std::endl;
	    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		if (option == 1)
		{
			std::cout << "\t" << "1)" << "Adding attributes to the tag element" << std::endl;
		}
		if (option == 2)
		{
			std::cout << "\t" << std::endl << "2)" << "Adding attributes to the Processinstruction" << std::endl;
		}
	   if (result)
		{
			cout << "Result of the tree after adding attributes " << std::endl;
		    std::cout << docelement->toString();

		}
		else
			std::cout << "Addition of child was not sucessful";

	}

	void display_removeattribute(bool result, std::string attribute_name, std::string attribute_value, XmlProcessing::XmlDocument::sPtr docelement)
	{
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demostrating Remove attribute based on given attribute name and attribute value" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "\t" << std::endl << "Removing attribute name value "<<" "<<attribute_name<<" "<<"and attribute value"<<" "<<attribute_value<<std::endl;
		if (result)
		{
			cout << "Result of the tree after removing " << std::endl;
			std::cout << docelement->toString();

		}
		else
			std::cout << "Addition of child was not sucessful";

	}
	void display_attributes_from_element(XmlProcessing::XmlDocument::attribute_pair attributes, std::string element)
	{ 
		std::cout << std::endl << "-----------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Demostrating of getting attributes from a given element" << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
		cout << "Attributes pair for the given element " << " " << element << "are :" << std::endl;
		for (XmlProcessing::XmlDocument::attrib_pair_iter attrib_pair_iter = attributes.begin(); attrib_pair_iter != attributes.end() && attributes.size() > 0; attrib_pair_iter++)
		{
			std::cout << "1 : " << (attrib_pair_iter->first) << "\t" << attrib_pair_iter->second << std::endl;
		}

	}






};
#endif