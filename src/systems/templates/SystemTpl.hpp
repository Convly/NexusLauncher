#ifndef NEXUS_LAUNCHER_SYSTEM_TPL_HPP
# define NEXUS_LAUNCHER_SYSTEM_TPL_HPP

#include <string>

namespace nx {
	class SystemTpl
	{
	public:
		SystemTpl(const std::string& name) : _name(name) {};
		virtual ~SystemTpl() {};

	public:
		virtual void				init(void) = 0;
		virtual const std::string&	getName(void) const = 0;

	protected:
		const std::string			_name;
	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_TPL_HPP