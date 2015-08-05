#ifndef DATASTORE_H
#define DATASTORE_H
//DataStore.h:.....

#include<vector>
class DataStore
{
public:
	using iterator = std::vector<std::string>::iterator;
	void save(const std::string& filespec) { store.push_back(filespec); }
	//file spec is the name of the path concatenated with file name
	void save(const std::string& filename, const std::string &path){}
	iterator begin(){ return store.begin(); }
	iterator end(){ return store.end(); }
private:
	std::vector<std::string> store;
};
#endif

