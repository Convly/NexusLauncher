/**
 * @file SystemInitException.hpp
 * @author JSX
 */

#ifndef NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT
#define NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT

#include <exception>
#include <string>

namespace nx {
	/**
	 * @class SystemInitException
	 * This exception is used for handling errors in SystemTpl initialization
	 */
	class SystemInitException : public std::exception
	{
		protected:
			std::string _msg; /**< A string containing the error message built in SystemInitException()*/
		public:
			
			/**
			 * Default constructor for SystemInitException.<br>
			 * 
			 * It will construct a message based on the error given in parameter and will be templated as 
			 * "Failed to init $SystemName system: $Error"
			 * 
			 * @param systemName The name of the system which failed to start
			 * @param message Why the Exception has been thrown
			 */
			SystemInitException (const std::string& systemName, const std::string& message):	_msg(std::string("Failed to init ") + systemName + std::string(" system: ") + message)	{}
	
			/**
			 * Default destructor for this class.
			 */
			virtual ~SystemInitException () throw () {}

			/**
			 * Give informations about why the error has been thrown
			 * 
			 * @return nx::SystemInitException::_msg (const char*)
			 */
			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_FAILED_ON_SYSTEM_INIT