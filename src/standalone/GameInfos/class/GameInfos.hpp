#ifndef NEXUS_LAUNCHER_STANDALONE_GAMEINFOS_HPP
# define NEXUS_LAUNCHER_STANDALONE_GAMEINFOS_HPP

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "BadFormatGameJSONException.hpp"

namespace nx {
	class GameInfos
	{
		std::vector<std::string>	GameInfosAttrs = {
			"title",
			"version",
			"author",
			"icon",
			"cover",
			"description",
			"url",
			"remote"
		};

	public:
		GameInfos(const std::string& = ".");
		virtual ~GameInfos();

	public:
		const std::string&									getPath(void) const;
		const std::unordered_map<std::string, std::string>	getInfos(void) const;
		void dump(void) const;
		void checkInfosIntegrity(void) const;
		rapidjson::Document getJSONDocumentFromPath();		

	private:
		std::string										_path;
		std::unordered_map<std::string, std::string>	_infos;
	};
}

#endif // NEXUS_LAUNCHER_STANDALONE_GAMEINFOS_HPP