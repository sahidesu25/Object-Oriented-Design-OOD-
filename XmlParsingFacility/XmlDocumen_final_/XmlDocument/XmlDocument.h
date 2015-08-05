#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   - XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*
* ToDo:
* -----
* This is the beginning of an XmlDocument class for Project #2.  
* It lays out a suggested design, which you are not compelled to follow.
* If it helps then use it.  If not you don't have to.
*
* Note that I've simply roughed in a design that is similar to that
* used in the .Net Framework XDocument class.
*/

#include <memory>
#include <string>
#include<stack>
#include <map>
#include "../XmlElement/XmlElement.h"
#include "../XmlElementParts/XmlElementParts/xmlElementParts.h"
#include "../XmlElementParts/XmlElementParts/Tokenizer.h"

namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;

	using attribute_pair = std::map < std::string, std::string > ;
	using attrib_pair_iter = attribute_pair::iterator;
	std::vector<std::string> tokens_;//this has to be changed later
    enum sourceType { string, filename };

    XmlDocument(const std::string& src, sourceType srcType=string);
	XmlDocument(XmlDocument&&rhsdoc);
	XmlDocument& operator=(XmlDocument&& pdoc);

    
    // queries return XmlDocument references so they can be chained, e.g., doc.element("foobar").descendents();

    XmlDocument& element(const std::string& tag);           // found_[0] contains first element (DFS order) with tag
    XmlDocument& elements(const std::string& tag);          // found_ contains all elements with tag
    XmlDocument& children(const std::string& tag = "");     // found_ contains sPtrs to children of prior found_[0] 
    XmlDocument& descendents(const std::string& tag = "");  // found_ contains sPtrs to descendents of prior found_[0]
	std::vector<sPtr>& select(){
		return found_;}
     // return reference to found_.  Use std::move(found_) to clear found_
	void BuildTree(std::vector<std::string> tokens);
	sPtr makerootelements(std::vector<std::string> tokens);
	bool isDeclaration(std::string token);
	bool isComment(std::string token);
	bool isProcIns(std::string token);
	bool isTextElement(std::string token);
	bool isClosingTag(std::string token);
	attribute_pair  findAttributes(std::string token);
	std::string get_tagged_element(std::string token);
	XmlDocument::sPtr Attribute_search(sPtr pNode, std::string attribute_id, std::string value);
	CommentElement* check_comment_type(sPtr pnode);
	TextElement* XmlDocument::check_text_type(sPtr pnode);
	ProcInstrElement* check_proc_type(sPtr pnode);
	XmlDeclarElement* check_declaration_type(sPtr pnode);
	TaggedElement* check_Tagged_type(sPtr pnode);
	std::vector<XmlDocument::sPtr> Tag_Search(sPtr pnode, std::string tag_);
	XmlDocument::sPtr doc_Attribute_search(sPtr pNode, std::string attribute_id, std::string value);
	bool AddChildByTag(std::string node,std::string tag_);
	bool checktextchild(sPtr found);
	bool AddChildtoDoc(std::string tag_);
	bool removechildbytag(std::string parent,std::string tag);
	bool removechildbyattr(std::string parent,std::string tag, std::string value);
	bool AddAttributes(std::string,std::string,std::string);
	bool RemoveAttributes(std::string attributename, std::string attributevalue);
	std::vector<XmlDocument::sPtr> Proc_Search(sPtr pnode, std::string tag_);
	
	sPtr return_Pdoc()
	{
		return pDocElement_;
	}
	sPtr return_root()
	{
		return root;
	}

  private:
    sPtr pDocElement_;  
	sPtr root;// AST that holds procInstr, comments, XML root, and more comments
    
	// query results
	std::stack<sPtr> elementStack;
	std::vector<sPtr> found_;
	int count;
	
  };
}
#endif
