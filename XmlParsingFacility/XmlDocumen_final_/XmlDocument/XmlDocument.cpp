///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Sahithi Desu, sldesu@syr.edu                     //
//              650-445-8606                                     // 
//
//
///////////////////////////////////////////////////////////////////
//
//Module Operations:
// ==============
//* This build the Xml tree and traveres through all the elements in the tree for performing different operations in the tree
//* 
//* Required Files:
//* ==============
//* Tokenizer.cpp, XmlDocument.cpp, XmlElement.cpp, XmlElementParts.cpp
// Maintenance History :
//*--------------------
//* -first release
//



#include <iostream>
#include "XmlDocument.h"
#include <map>
#include<string>


using namespace XmlProcessing;
//constructor for intializing the xdocument class variables and passing the file to the tokenizer
XmlProcessing::XmlDocument::XmlDocument(const std::string& src, sourceType srcType)
{
	if (srcType == 1)

	{
		Toker toker(src);
		toker.setMode(Toker::xml);
		XmlParts parts(&toker);
		//  //parts.verbose();                 // uncomment to show token details
		while (parts.get())
		{
			tokens_.push_back(parts.show());
		}
		std::cout << parts.show().c_str() << std::endl;
		count = 0;
		// sPtr docelement = makeDocElement(pDocElement_);
	}
	else
	{
		Toker toker(src, false);
		toker.setMode(Toker::xml);
		XmlParts parts(&toker);
		//  //parts.verbose();                 // uncomment to show token details
		while (parts.get())
		{
			tokens_.push_back(parts.show());
		}
		std::cout << parts.show().c_str() << std::endl;
		count = 0;

	}
  
}
XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::operator=(XmlDocument&& pdoc)
{
	if (this == &pdoc) return *this;
	pDocElement_ = std::move(pdoc.pDocElement_);
	root = std::move(pdoc.root);
	pdoc.pDocElement_ = nullptr;
	found_.clear();
	found_=(std::move(pdoc.found_));
	elementStack = std::move(pdoc.elementStack);
	count = pdoc.count;
	tokens_ = std::move(pdoc.tokens_);
	return *this;

}
XmlProcessing::XmlDocument::XmlDocument(XmlDocument &&rhsdoc) :pDocElement_(std::move(rhsdoc.pDocElement_))
{
	std::cout <<std::endl<< "Performing move operation, Demonstrating req 4"<<std::endl;
	root = std::move(rhsdoc.root);
	rhsdoc.pDocElement_ = nullptr;
	rhsdoc.root = nullptr;
	rhsdoc.found_.clear();
	found_ = std::move(rhsdoc.found_);
   count = rhsdoc.count;
	elementStack = rhsdoc.elementStack;
	tokens_ = std::move(rhsdoc.tokens_);
	
	

}
//checks wether the given string is declaration or not 
bool XmlDocument::isDeclaration(std::string token)
{
	std::size_t found = token.find("? xml");
	if (found != std::string::npos)
		return true;
	else
	return false;


}
//checks wether the given string is comment or not
bool XmlDocument::isComment(std::string token)
{
	std::size_t found = token.find("< ! --");
	if (found != std::string::npos)
		return true;
	else
		return false;


}
//checks wether the given string is text element or not 
bool XmlDocument::isTextElement(std::string token)
{
	std::size_t found3 = token.find("< ");
	if (!isComment(token) && !isProcIns(token) && (found3 == std::string::npos))
		return true;
	else
		return false;
}
//checks wetheer is the given string is closing tag
bool XmlDocument::isClosingTag(std::string token)
{
	std::size_t found = token.find("< /");
	if (!isComment(token) && !isProcIns(token) && !isTextElement(token) && (found != std::string::npos))
	{
		return true;
	}
	else
		return false;
}
//checks wether the givn the given string is Proc instruction or not
bool XmlDocument::isProcIns(std::string token)
{
	std::size_t found = token.find("< ?");
	std::size_t found2 = token.find("< ? xml");
	if ((found != std::string::npos) && (found2== std::string::npos))
		return true;
	else
		return false;
}
//builds the Document tree and also calls function wch builds the root element 
void XmlDocument::BuildTree(std::vector<std::string> tokens)
{
	std::string temp = tokens[0];
	int flag = 0;
	for (int i = 0; i < tokens.size(); i++)
	{
		std::string temp = tokens[i];
		if ((isDeclaration(temp)) && (elementStack.size() == 0))
		{
		}
		else if ((isComment(temp)) && (elementStack.size() == 0))
		{
			sPtr comment_ = makeCommentElement(temp);
			if (flag == 0)
			{
				pDocElement_ = makeDocElement(comment_);
				flag = 1;

			}
			else
			{
				pDocElement_->addChild(comment_);
			}
		}
		else if ((isProcIns(temp)) && (elementStack.size() == 0))
		{
			sPtr ProcIns = makeProcInstrElement(temp);
			if (flag == 0)
			{
				pDocElement_ = makeDocElement(ProcIns);
				flag = 1;

			}
			else
			{
				pDocElement_->addChild(ProcIns);
			}
			attribute_pair attributes = findAttributes(temp);
			for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
				ProcIns->addAttrib(i->first, i->second);
		}
		else 
		{ 
			count = i;
			break;
		}
	}
	XmlDocument::sPtr root =makerootelements(tokens);
	if (flag == 0)
		pDocElement_=makeDocElement(root);
	else
		pDocElement_->addChild(root);
}
//given a string, it will find all the attributes.
XmlDocument::attribute_pair XmlDocument::findAttributes(std::string token)
{
	int found;
	attribute_pair attrib;
	std::vector<std::string> splittokens;
	
	found = token.find("=");
	if (found != std::string::npos)
	{
		int count = 0;
		char *context = NULL;
		char *s2 = (char *)alloca(token.size() + 1);
		memcpy(s2, token.c_str(), token.size() + 1);
		char* p = strtok_s(s2, " \"", &context);
		while (p != NULL)
		{

			if (count == 0)
			{
				splittokens.push_back(p);
			}
				//search_word = p;
			

			p = strtok_s(NULL, " \"", &context);
			if (p!=NULL)
			splittokens.push_back(p);
			count = count + 1;
		}
		for (int i = 0; i < splittokens.size(); i++)
		{
			if (splittokens[i] == "=")
			{
				attrib.insert(std::make_pair(splittokens[i - 1], splittokens[i + 1]));

			}
		}
	}
	return attrib;
}
// gets the tagged element value from the given string
std::string XmlDocument::get_tagged_element(std::string token)
{
	std::string tagname;
	int found;
	found = token.find("<");
	if (found != std::string::npos)
	{
		int count = 0;
		char *context = NULL;
		char *s2 = (char *)alloca(token.size() + 1);
		memcpy(s2, token.c_str(), token.size() + 1);
		char* p = strtok_s(s2, " \"", &context);
		
		while (p != NULL)
		{

			if (count == 1)
			{
				tagname = p;
				break;
			}
			//search_word = p;


			p = strtok_s(NULL, " \"", &context);
			if (p != NULL)

				count = count + 1;
		}


	}
	return tagname;
}
//checks wether the element type is of declaration type
XmlDeclarElement* XmlDocument::check_declaration_type(sPtr pnode)
{
	return dynamic_cast<XmlDeclarElement*>(pnode.get());
}
//checks wether the element type is of proc instruction type
ProcInstrElement* XmlDocument::check_proc_type(sPtr pnode)
{
	return dynamic_cast<ProcInstrElement*>(pnode.get());
}
//checks wether the element type is of comment type
CommentElement* XmlDocument::check_comment_type(sPtr pnode)
{
	return dynamic_cast<CommentElement*>(pnode.get());
}
//checks wether the element type is a text type
TextElement* XmlDocument::check_text_type(sPtr pnode)
{
	return dynamic_cast<TextElement*>(pnode.get());
}
//checks wether the element type is a tagged element type
TaggedElement* XmlDocument::check_Tagged_type(sPtr pnode)
{
	return dynamic_cast<TaggedElement*>(pnode.get());
}
//given an attribute name and value, it searches for the corresponding element from the doc element. 
//this calls the arribute_search function which searches the name and value pair from the root
XmlDocument::sPtr XmlDocument::doc_Attribute_search(sPtr pNode, std::string attribute_id, std::string value)
{
	DocElement *docptr = dynamic_cast<DocElement*>(pNode.get());
	for (auto docchild : docptr->children())
	{
		ProcInstrElement* procptr = check_proc_type(docchild);
		XmlDeclarElement *declarptr = check_declaration_type(docchild);
		TaggedElement* taggedptr = check_Tagged_type(docchild);
		CommentElement *commptr = check_comment_type(docchild);
		if (commptr!=nullptr)
		{
			continue;
		}
	 if (procptr!=nullptr)
		{
			std::vector<std::pair<std::string, std::string>>& attri_ = procptr->attributes();
			for (int i = 0; i < attri_.size(); i++)
			{
				if ((attri_[i].first == attribute_id) && (attri_[i].second == value))
				{
					found_.push_back(docchild);
					return pNode;
				}
			}
		}
		 if (declarptr!=nullptr)
		{
			 std::vector<std::pair<std::string, std::string>>& attri_ = declarptr->attributes();
			 for (int i = 0; i < attri_.size(); i++)
			 {
				 if ((attri_[i].first == attribute_id) && (attri_[i].second == value))
				 {
					 found_.push_back(docchild);
					 return pNode;
				 }
			 }
		 }
		 if (taggedptr!=nullptr)
		{
			sPtr tagged = Attribute_search( docchild, attribute_id, value);
			return tagged;
		}
	}
}

//searches for the name and value pair from the root element and returns the corresponding elements
XmlDocument::sPtr XmlDocument::Attribute_search(sPtr pNode, std::string attribute_id, std::string value)
{
	TaggedElement* taggedptr = dynamic_cast<TaggedElement*>(pNode.get());
	ProcInstrElement* procptr = dynamic_cast<ProcInstrElement*>(pNode.get());
	if ((taggedptr != nullptr))
	{
		if (taggedptr->children().size() == 0)
		{
			std::vector<std::pair<std::string, std::string>>& attri_ = taggedptr->attributes();
			for (int i = 0; i < attri_.size(); i++)
			{
				if ((attri_[i].first == attribute_id) && (attri_[i].second == value))
					return pNode;
			}
			return nullptr;
		}
		for (auto pChild : taggedptr->children())
		{
			std::vector<std::pair<std::string, std::string>>& attri_ = taggedptr->attributes();
			for (int i = 0; i < attri_.size(); i++)
			{
				if ((attri_[i].first == attribute_id) && (attri_[i].second == value))
				{
					found_.push_back(pNode);
					return pNode;
				}
			}
			TextElement* checkchildtextPtr = check_text_type(pChild);
			CommentElement* checkcommenttextPtr = check_comment_type(pChild);
			if (checkchildtextPtr != nullptr)
				continue;
			if (checkcommenttextPtr != nullptr)
				continue;
			sPtr temp = Attribute_search(pChild, attribute_id, value);
			if (temp != nullptr)
				found_.push_back(temp);
		}
		return nullptr;
	}
	if (procptr != nullptr)
	{
		std::vector<std::pair<std::string, std::string>>& attri_ = procptr->attributes();
		for (int i = 0; i < attri_.size(); i++)
		{
			if ((attri_[i].first == attribute_id) && (attri_[i].second == value))
				return pNode;
		}
		return nullptr;
	}
	return nullptr;
}
// searches for the proc instruction elements in the document 
std::vector<XmlDocument::sPtr> XmlDocument::Proc_Search(sPtr pnode, std::string tag_)
{
	DocElement* docptr = dynamic_cast<DocElement*>(pnode.get());
	TaggedElement* taggedptr = dynamic_cast<TaggedElement*>(pnode.get());
	if (docptr != nullptr)
	{
		for (auto docchild : docptr->children())
		{
			ProcInstrElement* procptr = check_proc_type(docchild);
			XmlDeclarElement *declarptr = check_declaration_type(docchild);
			TaggedElement* taggedptr = check_Tagged_type(docchild);
			CommentElement *commptr = check_comment_type(docchild);
			if (commptr != nullptr)
				continue;
			else if (procptr != nullptr)
			{
				if (tag_.compare(procptr->toString()))
				found_.push_back(docchild);
			}
			else if (declarptr != nullptr)
				continue;
			else if (taggedptr != nullptr)
				Proc_Search(root, tag_);
			else
				return found_;
		}
	}

	if (taggedptr != nullptr)
	{
		for (auto pchild : taggedptr->children())
		{
			ProcInstrElement* procptr = check_proc_type(pchild);
			TaggedElement* taggedptr = check_Tagged_type(pchild);
			CommentElement *commptr = check_comment_type(pchild);
			TextElement *textptr = check_text_type(pchild);
			if (procptr != nullptr) 
			{
				if(tag_== procptr->toString())
				found_.push_back(pchild);
				continue;
			}
			if (commptr != nullptr)
				continue;
			if (textptr != nullptr)
				continue;
			if (taggedptr != nullptr)
				Proc_Search(pchild, tag_);
		}
	}
	return found_;
}

// Performs tag serach from the doc element and returns all the elements with the matching tag.
std::vector<XmlDocument::sPtr> XmlDocument::Tag_Search(sPtr pnode, std::string tag_)
{
	DocElement* docptr = dynamic_cast<DocElement*>(pnode.get());
	TaggedElement* taggedptr = dynamic_cast<TaggedElement*>(pnode.get());
	if (docptr != nullptr)
	{
		for (auto docchild : docptr->children())
		{
			ProcInstrElement* procptr = check_proc_type(docchild);
			XmlDeclarElement *declarptr = check_declaration_type(docchild);
			TaggedElement* taggedptr = check_Tagged_type(docchild);
			CommentElement *commptr = check_comment_type(docchild);
			if (commptr != nullptr)
			{
				continue;
			}
			else if (procptr != nullptr)
			{
				continue;
			}
			else if (declarptr != nullptr)
			{
				continue;
			}
			else if (taggedptr!=nullptr)
			{
				
				Tag_Search(root, tag_);
				
			}
			else
			{
				return found_;
			}
		}
	}
	
	if (taggedptr != nullptr)
	{
		if (taggedptr->value() == tag_)
			found_.push_back(pnode);
		for (auto pchild : taggedptr->children())
		{
			Tag_Search(pchild, tag_);
		}
	}
	return found_;
}
//checks wether the text child is already present in the element, if so, it will return false, else it returns true. 
//This helps for the addchild function to deceide wether to add text element or not.
bool XmlDocument::checktextchild(sPtr found)
{
	bool maketext=true;
	TaggedElement* taggedptr = dynamic_cast<TaggedElement*>(found_.at(0).get());
	for (auto child : taggedptr->children())
	{
		TextElement* checkchildtextPtr = check_text_type(child);
		if (checkchildtextPtr != nullptr)
		{
			maketext = false;
			break;
		}
	}
	return maketext;
}
//Adds chils to doc element
bool XmlDocument::AddChildtoDoc(std::string tag_)
{ 
	if (isTextElement(tag_))
	{
		
			sPtr newelement = makeTextElement(tag_);
			return(pDocElement_->addChild(newelement));
	}
		
	else if (isComment(tag_))
	{
		sPtr newelement = makeCommentElement(tag_);
		return (pDocElement_->addChild(newelement));
	}
	else if (isProcIns(tag_))
	{
		sPtr newelement = makeProcInstrElement(tag_);
		attribute_pair attributes = findAttributes(tag_);
		for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
			newelement->addAttrib(i->first, i->second);
       return (pDocElement_->addChild(newelement));

	}
	else if (isDeclaration(tag_))
	{
		return false;
	}
	else
	{
		sPtr newelement = makeTaggedElement(tag_);
		return (pDocElement_->addChild(newelement));
	}
}


//adds attributes to the proc instruction and the tagged element 
bool XmlDocument::AddAttributes(std::string tagname, std::string attributename, std::string attributevalue)
{
	if (isProcIns(tagname))
	{
		found_ = Proc_Search(pDocElement_, tagname);
		if (found_.size() != 0)
			return (found_[0]->addAttrib(attributename, attributevalue));
		else
			return false;
	}
	else
	{
		found_ = Tag_Search(pDocElement_, tagname);
		if (found_.size() != 0)
			return (found_[0]->addAttrib(attributename, attributevalue));
		else
			return false;
	}
}
// remove attributes from the tagged element and Proc instruction element
bool XmlDocument::RemoveAttributes(std::string attributename, std::string attributevalue)
{
	sPtr search = doc_Attribute_search(pDocElement_,attributename, attributevalue);
	if (found_.size() != 0)
		return(found_[0]->removeAttrib(attributename));
	else
		return false;
}

// adding a child to the given tag .	
bool XmlDocument::AddChildByTag(std::string node_to_add,std::string tag_)
{
	if (node_to_add == "DocElement")
		return(AddChildtoDoc(tag_));
	bool maketext = true;
	found_ = Tag_Search(pDocElement_, node_to_add);
	if (found_.size() != 0)
	{
		maketext = checktextchild(found_[0]);
		if (isTextElement(tag_))
		{
			if (maketext)
			{
				sPtr newelement = makeTextElement(tag_);
				found_.at(0)->addChild(newelement);
				return true;
			}
			else
				return false;
		}
		else if (isComment(tag_))
		{
			sPtr newelement = makeCommentElement(tag_);
			return (found_.at(0)->addChild(newelement));
		}
		else if (isProcIns(tag_))
		{
			sPtr newelement = makeProcInstrElement(tag_);
			attribute_pair attributes = findAttributes(tag_);
			for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
				newelement->addAttrib(i->first, i->second);
			return (found_.at(0)->addChild(newelement));
		}
		else if (isDeclaration(tag_))
			return false;
		else
		{
			std::string temp = get_tagged_element(tag_);
			sPtr newelement = makeTaggedElement(temp);
			attribute_pair attributes = findAttributes(tag_);
			for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
				newelement->addAttrib(i->first, i->second);
			return (found_.at(0)->addChild(newelement));
		}
	}
	else
		return false;
}
// removing the child from the given tag 
bool XmlDocument::removechildbytag(std::string parent, std::string tag)
{
	std::vector<sPtr> ptr = Tag_Search(root, tag);
	select().clear();
	std::vector<sPtr> parentnode = Tag_Search(root, parent);
	return parentnode[0]->removeChild(ptr[0]);

}
//removes the child element given a name value pait of attribute
bool XmlDocument::removechildbyattr(std::string parent,std::string tag, std::string value)
{
	std::vector<sPtr> parentnode = Tag_Search(root, parent);
	select().clear();
	sPtr search = Attribute_search(root, tag, value);
	bool b=false;
	for (int i = 0; i < parentnode.size();i++)
	{ 
		b=parentnode[i]->removeChild(found_[0]);
		if (b == true)
			break;
	}
		
	return b;
}


//builds the tree from the root. This function is called by build tree
XmlDocument::sPtr XmlDocument::makerootelements(std::vector<std::string> tokens)
{
	for (int i = count; i < tokens.size(); i++)
	{
		std::string temp = tokens[i];
		if (!isComment(temp) && (!isProcIns(temp)))
		{
			if (i == count)
			{
				 root = makeTaggedElement(get_tagged_element(temp));
				 attribute_pair attributes = findAttributes(temp);
				 for (attrib_pair_iter i = attributes.begin(); i != attributes.end()&& attributes.size()>0; i++)
					 root->addAttrib(i->first, i->second);
				 elementStack.push(root);
			}
			else
			{
				if (isTextElement(temp))
					elementStack.top()->addChild(makeTextElement(temp));
				else
				{
					if (isClosingTag(temp))
						elementStack.pop();
					else
					{
						sPtr tagged = makeTaggedElement(get_tagged_element(temp));
						elementStack.top()->addChild(tagged);
						attribute_pair attributes = findAttributes(temp);
						for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
							tagged->addAttrib(i->first, i->second);
						elementStack.push(tagged);
					}
				}
			}
		}
		if (isComment(temp))
			elementStack.top()->addChild(makeCommentElement(temp));
		if (isProcIns(temp))
		{
			 sPtr ProcIns = makeProcInstrElement(temp);
			elementStack.top()->addChild(ProcIns);
			attribute_pair attributes = findAttributes(temp);
			for (attrib_pair_iter i = attributes.begin(); i != attributes.end() && attributes.size()>0; i++)
				ProcIns->addAttrib(i->first, i->second);
		}
	}
	return root;
}


#ifdef TEST_XMLDOCUMENT
int main()
{
  title("Testing XmlDocument class");
  //XmlDocument::sourceType scr = XmlDocument::filename;
  std::string test1 = "<?xml version=\"1.0\" encoding=\"utf - 8\"?><!--XML test case -->< ? type = \"text/xsl\" href = \"style.xsl\" ? ><LectureNote course = \"CSE681\" courseId = \"a\" coursename = \"yada\"><title>XML Example #1< / title>";
	  test1 += "<reference>";
	  test1 += "<title>Programming Microsoft.Net< / title>";
	  test1 += "<author id = \"ref1\">Jeff Prosise <note Company = \"Wintellect\">< / note>< / author>";
	  test1 += "< ? type1 = \"text/xsl\" href = \"style.xsl\" ? >";
	  test1 += "<publisher>Microsoft Press< / publisher>";
	  test1 += "<date>2002< / date>";
	  test1 += "<page>608< / page>";
	 test1 += " < / reference>";
    test1 += "<comment>Description of PCDATA< / comment>";
test1 += "< / LectureNote>";
  
  XmlDocument doc(test1);
  doc.BuildTree(doc.tokens_);
  XmlDocument::sPtr attribute_query= doc.doc_Attribute_search(doc.return_Pdoc(), "Company", "Wintellect");
  //XmlDocument::sPtr attribute_query = doc.Attribute_search(doc.return_root(), "Company","Wintellect");
  std::cout << "\n\n";
  if (doc.select().size() != 0)
	  std::cout << doc.select().at(0)->toString();
  else
	  std::cout << "Element not found";
  doc.select().clear();
  std::cout << std::endl;
  std::vector<XmlDocument::sPtr>tag_query=doc.Tag_Search(doc.return_Pdoc(), "LectureNote");
  for (auto tag : tag_query)
  {
	  std::cout << "Tagname" <<std::endl<< tag->value() << std::endl;
  }
  doc.select().clear();
  
  bool addchild = doc.AddChildByTag("author", "< ! -- This is author comment -- >");
  std::cout << std::endl;
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  bool addchildtodoc = doc.AddChildByTag("DocElement", "< ! -- This is doc comment-- >");
  std::cout << std::endl;
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  bool addtagchild = doc.AddChildByTag("author", "< authorName >");
  std::cout << std::endl;
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  bool removechildbytag = doc.removechildbytag("author","note");
  std::cout << std::endl;
  std::cout << doc.return_Pdoc()->toString();
  bool removechildbyattri = doc.removechildbyattr("reference","id", "ref1");
  std::cout << std::endl;
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  bool addAtrribute = doc.AddAttributes("author","id1", "ref2");
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  bool removeattributes = doc.RemoveAttributes("id1", "ref2");
  std::cout << doc.return_Pdoc()->toString();
  doc.select().clear();
  std::cout << "-----------------------------------------------";
  std::vector<XmlDocument::sPtr>Proc_query = doc.Proc_Search(doc.return_Pdoc(),"  < ? type1 = \"text/xsl\" href = \"style.xsl\" ? >");
  if (Proc_query.size() != 0)
  {
	  for (auto result : Proc_query)
	  {
		  std::cout << result->toString();
		  std::cout << std::endl;
	  }
  }
  
 std::cout << "\n\n";

 
}
#endif