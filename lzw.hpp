#include <map>
#include <fstream>
#include <stringstream>
void lzwEncode(std::string filePathi, std::string outFileName)
{
	// open source file
	std::ifstream source(filePathi, std::ios::ate | std::ios::binary);
	if(!source.is_open())
	{
		throw std::runtime_error("failed open source file");
	}
	int length = source.tellg();
	source.seekp(0,std::ios::beg);

	// create outPut file
	std::ofstream outFile(outFileName);
	if(!outFile.is_open())
	{
		throw std::runtime_error("failed open output file");
	}
	// init Dictionaries
	std::map<std::string,int> dictionary;
	int count =0;
	for(;count<256;++count)
	{
		dictionary[std::string(1,count)] = count;
	}
	++count; // spacing out  for clear flag
	++count; // spacing out for end flag
	auto checkEntryInDict = [&dictionary](const std::string& entry)
	{
		auto itr = dictionary.find(entry);
		if(itr!=dictionary.end())
		{
			return itr->second;
		}
		return -1;
	}
	std::string prefixStr = "";
	std::string entry = "";

	std::stringstream outStrStream;
	for(int i = 0; i < length; ++i)
	{
		char tempChar;
		source.read(&tempChar,1);
		entry = prefixStr +  tempChar;
		int index = checkEntryInDict(entry);
		if(index <0 )
		{
			dict[entry] = count++;
			assert(dict.find(preFixStr)!=dict.end());
			outStrStream << dict[prefixStr];
			prefixStr = tempChar;
		}
		else
		{
			preFixStr = entry;
		}

	}
	assert(dict.find(preFixStr)!=dict.end());
	outStrStream << dict[preFixStr];
	auto outStr = outStrStream.str();
	outFile.write(outStr.c_str(), outStr.size());
	return;
}
