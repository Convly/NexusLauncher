#ifndef NEXUS_LAUNCHER_ERRORS_NO_SELECTED_GAME_HPP_
#define NEXUS_LAUNCHER_ERRORS_NO_SELECTED_GAME_HPP_

#include <exception>
#include <string>

namespace nx {
	class NoSelectedWidgetException : public std::exception
	{
		protected:
			std::string _msg;
		public:
			NoSelectedWidgetException ():	_msg("There is currently no selected game")	{}
	
			virtual ~NoSelectedWidgetException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_NO_SELECTED_GAME_HPP_