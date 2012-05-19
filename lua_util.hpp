#ifndef LUA_UTIL_LUA_HPP_
#define LUA_UTIL_LUA_HPP_

#include "lua_util/type.hpp"
#include "lua_util/function.hpp"
#include "lua_util/exception.hpp"

namespace lua_util{

class lua{
	public:
		lua();
		~lua();
	public:
		template<int N, class R, class... T>
			function<N, R, T...> define_function(std::string const& func_name);
	public:
		static int at_panic(lua_State* lua);
	private:
		lua_State* _lua;
};

lua::lua() : _lua(nullptr){
	_lua= lua_open();
	
	if(!_lua)
		throw exception("cannot open lua.");
	luaL_openlibs(_lua);
}

lua::~lua(){
	lua_settop(_lua, 0);
	
	lua_close(_lua);
	_lua= nullptr;
}

template<int N, class R, class... T>
function<N, R, T...> lua::define_function(std::string const& func_name){
	return function<N, R, T...>(_lua, func_name);
}

int lua::at_panic(lua_State* lua){
	std::string const mes= lua_tostring(lua, -1);
	
	lua_pop(lua, 1);

	return 0; // num of return values is 0
}

}

#endif // #ifndef LUA_UTIL_LUA_HPP_

