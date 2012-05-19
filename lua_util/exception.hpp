#ifndef LUA_UTIL_EXCEPTION_HPP_
#define LUA_UTIL_EXCEPTION_HPP_

#include <string>

namespace lua_util{

class exception{
	public:
		exception(std::string const& error_message);
		virtual ~exception();
	public:
		std::string const& what() const;
	private:
		std::string _what;
};

inline
exception::exception(std::string const& error_message) : _what(error_message){}

inline
exception::~exception(){
	_what= "";
}

inline
std::string const& exception::what() const{
	return _what;
}

}

#endif // #ifndef LUA_UTIL_EXCEPTION_HPP_


