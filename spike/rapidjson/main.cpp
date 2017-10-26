//
// Made by Marco
//

#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string					getStringFromFile(const std::string & path)
{
	std::string				output;
	std::string				line;
	std::ifstream			file(path.c_str());

	if (file.is_open())
	{
		while (getline(file, line))
			output += line;
		file.close();
	}
	else
		std::cout << "Unable to open file" << std::endl;
	return (output);
}

int							main(void)
{
	std::string				tmp = getStringFromFile("./test.json");

	if (tmp.size() <= 0)
		return (1);
	const char* json = tmp.c_str();
	rapidjson::Document d;

	d.Parse(json);

	for (const auto& item : d["game"].GetObject())
	{
		std::cout << item.name.GetString() << std::endl;
		for (const auto& info : d["game"].GetObject()[item.name.GetString()].GetObject())
		{
			std::cout << "  - " << info.name.GetString() << std::endl;
			if (info.value.IsString())
				std::cout << "     " << info.value.GetString() << std::endl;
		}
	}

	std::cout << "Hello world" << std::endl;
	while (1);
	return (0);
}
