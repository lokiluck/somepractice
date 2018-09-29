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

void lzwDecode(std::string sourceFile, std::string outputFile)
{
	int bitSize = 8;
	std::ifstream source(sourceFile);
	if(!source.is_open())
	{
		throw std::runtime_error("decode _ open source file failed");
	}

	//init dictionary
	std::map<int, std::string> dict;
	int count =0;
	for(; count < 256; ++count)
	{
		dict[count] = std::string(1,count);
	}
	++count; // spaceing out for end flag ,,,,  clear flag  256
	auto checkEntryInDict = [&dictionary](int index)
	{
		auto itr = dict.find(index);
		if(itr!=dictionary.end())
		{
			return itr->second;
		}
		return "";
	}
	std::string prefixStr = "";
	std::string entryStr = "";
	std::stringstream outStrStream;
	while(!source.eof())
	{
		char tempChar[200];
		source.read(&tempChar,bitSize);
		entryStr = prefixStr + tempChar;
		auto  str = checkEntryInDict(entryStr);
		if(str.empty())
		{
			
		}
		else
		{
			prefixStr = entryStr;
		}

	}


}
