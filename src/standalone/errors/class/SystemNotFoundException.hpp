/**
 * @file SystemNotFoundException.hpp
 * @author JSX
 */

#ifndef NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND
#define NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND

#include <exception>
#include <string>

namespace nx {
	/**
	 * @class SystemNotFoundException
	 * This exception is used for handling errors thrown when a system is not found during a research
	 */
	class SystemNotFoundException : public std::exception
	{
		protected:
			std::string _msg; /**< A string containing the error message built in SystemNotFoundException()*/
		public:
			/**
			 * Default constructor for SystemNotFoundException.<br>
			 * 
			 * It will construct a message based on the error given in parameter and will be templated as 
			 * "System $SystenName not found!"
			 * 
			 * @param systemName The name of the unknown system
			 */
			SystemNotFoundException (const std::string& systemName):	_msg(std::string("System ") + systemName + std::string(" not found!"))	{}
	
			/**
			 * Default destructor for this class.
			 */
			virtual ~SystemNotFoundException () throw () {}

			/**
			 * Give informations about why the error has been thrown
			 * 
			 * @return nx::SystemNotFoundException::_msg (const char*)
			 */
			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_SYSTEM_NOT_FOUND