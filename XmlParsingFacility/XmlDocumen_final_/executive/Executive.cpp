#ifndef EXECUTIVE
#define EXECUTIVE
///////////////////////////////////////////////////////////////////////
// Executive.cpp - The entry point of the program                    //
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
		XmlProcessing::XmlDocument newdoc(std::move(doc));
		XmlProcessing::XmlDocument::sPtr attribute_query_2 = newdoc.doc_Attribute_search(newdoc.return_Pdoc(), "version", "1.0");
		dis.display_attributesearch(newdoc.select(), 2, "version", "1.0");
		XmlProcessing::XmlDocument newdoc1(std::move(newdoc));
		XmlProcessing::XmlDocument::sPtr attribute_query_3 = doc.doc_Attribute_search(newdoc1.return_Pdoc(), "type", "text/xsl");
		dis.display_attributesearch(newdoc1.select(), 3, "type", "text/xsl");
		XmlProcessing::XmlDocument newdoc2(std::move(newdoc1));
		std::vector<XmlProcessing::XmlDocument::sPtr>tag_query = newdoc2.Tag_Search(newdoc2.return_Pdoc(), "title");
		dis.display_Tagsearch(tag_query, "title");
		XmlProcessing::XmlDocument newdoc3(std::move(newdoc2));
		bool addchild = newdoc3.AddChildByTag("author", "< ! -- This is author comment -- >");
		dis.display_addchild(addchild, 1, "author", "< ! -- This is author comment -- >", newdoc3.return_Pdoc());
		XmlProcessing::XmlDocument newdoc4(std::move(newdoc3));
		bool addprocchild = newdoc4.AddChildByTag("comment", "< ? type1 = \"text/xsl\" href = \"style.xsl\" >");
		dis.display_addchild(addchild, 2, "comment", "< ? type1 = \"text/xsl\" href = \"style.xsl\"  >", newdoc4.return_Pdoc());
		XmlProcessing::XmlDocument newdoc5(std::move(newdoc4));
		bool addtaggedchild = newdoc5.AddChildByTag("reference", "< month value = \"Jan\" >");
		dis.display_addchild(addchild, 3, "reference", "<month value=\"Jan\">", newdoc5.return_Pdoc());
		XmlProcessing::XmlDocument newdoc6(std::move(newdoc5));
		bool addchildchild = newdoc6.AddChildByTag("DocElement", "< ! -- This is doc comment -- >");
		dis.display_addchild(addchild, 4, "DocElement", "< ! -- This is doc comment -- >", newdoc6.return_Pdoc());
		XmlProcessing::XmlDocument newdoc7(std::move(newdoc6));
		bool addtextchild = newdoc7.AddChildByTag("month", "this is month text");
		dis.display_addchild(addchild, 5, "month", "this is month text", newdoc7.return_Pdoc());
		XmlProcessing::XmlDocument newdoc8(std::move(newdoc7));
		bool removechildbytag = newdoc8.removechildbytag("author", "note");
		dis.display_removechild(removechildbytag, "author", "note", newdoc8.return_Pdoc());
		XmlProcessing::XmlDocument newdoc9(std::move(newdoc8));
		bool removechildbyattri = newdoc9.removechildbyattr("reference", "id", "ref1");
		dis.display_removechildbyattribute(removechildbyattri, "reference", "id", "ref1", newdoc9.return_Pdoc());
		XmlProcessing::XmlDocument newdoc10(std::move(newdoc9));
		bool addAtrributetotag = newdoc10.AddAttributes("reference", "id1", "ref2");
		dis.display_Add_attributes(addAtrributetotag, 1, "reference", "id", "ref1", newdoc10.return_Pdoc());
		XmlProcessing::XmlDocument newdoc11(std::move(newdoc10));
		bool addAtrributetoproc = newdoc11.AddAttributes("< ? type = \"text/xsl\" href = \"style.xsl\" ? >", "type1", "text / xsl");
		dis.display_Add_attributes(addAtrributetotag, 2, "reference", "id", "ref1", newdoc11.return_Pdoc());
		XmlProcessing::XmlDocument newdoc12(std::move(newdoc11));
		bool removeattributes = newdoc12.RemoveAttributes("id1", "ref2");
		dis.display_removeattribute(removeattributes, "id1", "ref2", newdoc12.return_Pdoc());
		XmlProcessing::XmlDocument newdoc13(std::move(newdoc12));
		XmlProcessing::XmlDocument::attribute_pair attributes= newdoc13.findAttributes("<LectureNote course = \"CSE681\" courseId = \"a\" coursename = \"yada\">");
		dis.display_attributes_from_element(attributes, "<LectureNote course = \"CSE681\" courseId = \"a\" coursename = \"yada\">");
		cout << std::endl;
		XmlProcessing::XmlDocument doc1(test1);
		doc1.BuildTree(doc1.tokens_);
		dis.display_tree(doc1.return_Pdoc(),2);
		return 0;
}
#endif