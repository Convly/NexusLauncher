#ifndef NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_
# define NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_

#include "SystemTpl.hpp"

namespace nx {
	class GamesSystem : public nx::SystemTpl
	{
	public:
		GamesSystem(nx::Launcher&);
		~GamesSystem();

	public:
		virtual void				init(void);
		virtual int					run(void);
	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_GAMES_HPP_
