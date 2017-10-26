#include "GameInfos.hpp"

nx::GameInfos::GameInfos(const std::string& jsonPath)
:
	_path(jsonPath)
{
	auto d = this->getJSONDocumentFromPath();

	if (d.HasParseError()) {
		throw nx::BadFormatGameJSONException("JSON format is incorrect");
	}

	if (d.FindMember("game") == d.MemberEnd()) {
		throw nx::BadFormatGameJSONException("Cannot access 'game' tag");
	} else if (d["game"].GetObject().FindMember("infos") == d["game"].GetObject().MemberEnd()) {
		throw nx::BadFormatGameJSONException("Cannot access 'infos' tag");		
	}

	for (const auto& item : d["game"].GetObject()["infos"].GetObject()) {
		std::string name(item.name.GetString());
		std::string value(item.value.GetString());
		bool validParam = (std::find_if(nx::GameInfos::GameInfosAttrs.begin(), nx::GameInfos::GameInfosAttrs.end(), [&](auto it){return it == name;}) != nx::GameInfos::GameInfosAttrs.end());
		if (!validParam) {
			std::string ret = "Unknown parameter: " + name;
			throw nx::BadFormatGameJSONException(ret);
		}
		this->_infos[name] = value;
	}

	this->checkInfosIntegrity();
}

nx::GameInfos::~GameInfos()
{
	
}

// TOOLS

rapidjson::Document nx::GameInfos::getJSONDocumentFromPath()
{
	std::ifstream ifs(this->_path);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);
	return d;
}

void nx::GameInfos::checkInfosIntegrity() const
{
	for (auto tag : nx::GameInfos::GameInfosAttrs) {
		if (std::find_if(this->_infos.begin(), this->_infos.end(), [&](auto it){return tag == it.first;}) == this->_infos.end()) {
			std::string ret = "Missing tag '" + tag+ "'";
			throw nx::BadFormatGameJSONException(ret);
		}
	}
}

// GETTERS

const std::string& nx::GameInfos::getPath() const
{
	return this->_path;
}

const std::unordered_map<std::string, std::string> nx::GameInfos::getInfos() const
{
	return this->_infos;
}

void nx::GameInfos::dump() const
{
	std::cerr << "_> Dumping JSON file at " << this->_path << ":" << std::endl;
	for (auto it : this->_infos) {
		std::cerr << "_> >>> " << it.first << "\t-\t" << it.second << std::endl;
	}
}