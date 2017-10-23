#ifndef NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND
#define NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	class SystemNotFoundException : public std::exception
	{
		protected:
			std::string _msg;
		public:

			explicit SystemNotFoundException(const char* message):			_msg(std::string("System Not Found: ") + message)	{}
			explicit SystemNotFoundException (const std::string& message):	_msg(message)	{}
	
			virtual ~SystemNotFoundException () throw () {}

			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND