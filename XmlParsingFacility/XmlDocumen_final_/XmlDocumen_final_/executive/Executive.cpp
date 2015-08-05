#ifndef EXECUTIVE
#define EXECUTIVE
///////////////////////////////////////////////////////////////////////
// Executive.cpp - The entry point of the program                     //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2013                       //
// Platform:    Lenovo Y40, Win8.1                                   //
// Application: Xml Document Model, Project #2, Spring 2015          //
// Author:      Sahithi Lakshmi Desu, Syracuse University            //
//              (650)-445-8606 sldesu@syr.edu                        //
///////////////////////////////////////////////////////////////////////
//
//Module Operations:
// ==============
//* This is the entry of the project and it calls all the functions in the project.
//* This call the functions from the XDocument.
//* Required Files:
//* ==============
//* Tokenizer.cpp, XmlDocument.cpp, XmlElement.cpp, XmlElementParts.cpp
// Maintenance History :
//*--------------------
//* -first release


#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/XmlElementParts/Tokenizer.h"
#include "../XmlElementParts/XmlElementParts/xmlElementParts.h"
#include "../Display/Display.h"
#include<vector>

int main(int arg , char* argv[] )
{
	   std::string test1 = "<?xml version=\"1.0\"?><!-- top level comment -->";
		test1 += "<parent att1='val1' att2='val2'><child1 /><child2>child2 body<child1 /></child2></parent>";
		XmlProcessing::XmlDocument::sourceType scr = XmlProcessing::XmlDocument::filename;
		XmlProcessing::XmlDocument doc(argv[1], scr);
		Display dis;
		doc.BuildTree(doc.tokens_);
		dis.display_tree(doc.return_Pdoc(),1);
		XmlProcessing::XmlDocument::sPtr attribute_query_1 = doc.doc_Attribute_search(doc.return_Pdoc(), "Company", "Wintellect");
		dis.display_attributesearch(doc.select(), 1, "Company", "Wintellect");
		doc.select().clear();
		XmlProcessing::XmlDocument::sPtr attribute_query_2 = doc.doc_Attribute_search(doc.return_Pdoc(), "version", "1.0");
		dis.display_attributesearch(doc.select(), 2, "version", "1.0");
		doc.select().clear();
		XmlProcessing::XmlDocument::sPtr attribute_query_3 = doc.doc_Attribute_search(doc.return_Pdoc(), "type", "text/xsl");
		dis.display_attributesearch(doc.select(), 3, "type", "text/xsl");
		doc.select().clear();
		std::vector<XmlProcessing::XmlDocument::sPtr>tag_query = doc.Tag_Search(doc.return_Pdoc(), "title");
		dis.display_Tagsearch(tag_query, "title");
		doc.select().clear();
		bool addchild = doc.AddChildByTag("author", "< ! -- This is author comment -- >");
		dis.display_addchild(addchild, 1, "author", "< ! -- This is author comment -- >", doc.return_Pdoc());
		doc.select().clear();
		bool addprocchild = doc.AddChildByTag("comment", "< ? type1 = \"text/xsl\" href = \"style.xsl\" >");
		dis.display_addchild(addchild, 2, "comment", "< ? type1 = \"text/xsl\" href = \"style.xsl\"  >", doc.return_Pdoc());
		doc.select().clear();
		bool addtaggedchild = doc.AddChildByTag("reference", "< month value = \"Jan\" >");
		dis.display_addchild(addchild, 3, "reference", "<month value=\"Jan\">", doc.return_Pdoc());
		doc.select().clear();
		bool addchildchild = doc.AddChildByTag("DocElement", "< ! -- This is doc comment -- >");
		dis.display_addchild(addchild, 4, "DocElement", "< ! -- This is doc comment -- >", doc.return_Pdoc());
		doc.select().clear();
		bool addtextchild = doc.AddChildByTag("month", "this is month text");
		dis.display_addchild(addchild, 5, "month", "this is month text", doc.return_Pdoc());
		doc.select().clear();
		bool removechildbytag = doc.removechildbytag("author", "note");
		dis.display_removechild(removechildbytag, "author", "note", doc.return_Pdoc());
		doc.select().clear();
		bool removechildbyattri = doc.removechildbyattr("reference", "id", "ref1");
		dis.display_removechildbyattribute(removechildbyattri, "reference", "id", "ref1", doc.return_Pdoc());
		doc.select().clear();
		bool addAtrributetotag = doc.AddAttributes("reference", "id1", "ref2");
		dis.display_Add_attributes(addAtrributetotag, 1, "reference", "id", "ref1", doc.return_Pdoc());
		doc.select().clear();
		bool addAtrributetoproc = doc.AddAttributes("< ? type = \"text/xsl\" href = \"style.xsl\" ? >", "type1", "text / xsl");
		dis.display_Add_attributes(addAtrributetotag, 2, "reference", "id", "ref1", doc.return_Pdoc());
		doc.select().clear();
		bool removeattributes = doc.RemoveAttributes("id1", "ref2");
		dis.display_removeattribute(removeattributes, "id1", "ref2", doc.return_Pdoc());
		doc.select().clear();
		XmlProcessing::XmlDocument::attribute_pair attributes= doc.findAttributes("<LectureNote course = \"CSE681\" courseId = \"a\" coursename = \"yada\">");
		dis.display_attributes_from_element(attributes, "<LectureNote course = \"CSE681\" courseId = \"a\" coursename = \"yada\">");
		cout << std::endl;
		XmlProcessing::XmlDocument doc1(test1);
		doc1.BuildTree(doc1.tokens_);
		dis.display_tree(doc1.return_Pdoc(),2);
		return 0;
}
#endif