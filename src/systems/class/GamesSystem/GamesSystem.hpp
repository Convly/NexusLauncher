#ifndef NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_
# define NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_

#include <string>
#include <algorithm>

#include "SystemTpl.hpp"
#include "Crawler.hpp"
#include "GameInfos.hpp"

namespace nx {
	class GamesSystem : public nx::SystemTpl
	{
	public:
		GamesSystem(nx::Launcher&);
		~GamesSystem();

	public:
		virtual void				init(void);
		virtual int					run(void);

	public:
		const std::vector<nx::GameInfos>&	getGames(void) const;
		const std::string&					getGamesPath(void) const;
		const std::vector<nx::GameInfos>&	update(void);
		const std::pair<bool, fs::path> is_launcherArchValid();

	public:
		static bool is_validGameDirectory(const std::string&);
		static bool is_validGameConfiguration(const std::string&);

	private:
		std::vector<nx::GameInfos>	_games;
		const std::string			_binaryPath;
		nx::Crawler					_crawler;
		std::string					_gamesPath;
	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_
