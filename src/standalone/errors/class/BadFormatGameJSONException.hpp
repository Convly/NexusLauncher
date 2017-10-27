/**
 * @file BadFormatGameJSONException.hpp
 * @author JSX
 */

#ifndef NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_
#define NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace nx {
	/**
	 * @class BadFormatGameJSONException
	 * This exception is used for handling errors in JSON parsing
	 */
	class BadFormatGameJSONException : public std::exception
	{
		protected:
			std::string _msg; /**< A string containing the error message built in BadFormatGameJSONException(const std::string& error)*/
		public:
			/**
			 * Default constructor for this class. <br>
			 * It will construct a message based on the error given in parameter and will be prefixed by 
			 * "Error while parsing the game configuration file: "
			 * @param error contains the information about what happened
			 */
			BadFormatGameJSONException (const std::string& error):	_msg(std::string("Error while parsing the game configuration file: ") + error)	{}
	
			/**
			 * Default destructor for this class.
			 */
			virtual ~BadFormatGameJSONException () throw () {}

			/**
			 * Give informations about why the error has been thrown
			 * 
			 * @return nx::BadFormatGameJSONException::_msg (const char*)
			 */
			virtual const char* what() const throw () { return this->_msg.c_str(); }
	};
}

#endif // !NEXUS_LAUNCHER_ERRORS_BAD_FORMAT_GAME_JSON_EXCEPTION_HPP_