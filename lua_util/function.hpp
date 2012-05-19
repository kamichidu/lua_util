#ifndef LUA_UTIL_FUNCTION_HPP_
#define LUA_UTIL_FUNCTION_HPP_

#include <string>
#include <lua.hpp>
#include "../lua_util.hpp"

namespace lua_util{

template<int N, class R, class... T>
class function{
	public:
		typedef lua::number_t number_t;
		typedef lua::string_t string_t;
		typedef lua::boolean_t boolean_t;
		typedef lua::nil_t nil_t;
	public:
		function(lua_State* lua, std::string const& func_name);
		~function();
	public:
		R operator () (T... args) const;
	private:
		void push_args(number_t const& arg, T... args) const;
		void push_args(string_t const& arg, T... args) const;
		void push_args(boolean_t const& arg, T... args) const;
		void push_args(nil_t const& arg, T... args) const;
		void push_args() const;
	private:
		lua_State*       _lua;
		std::string      _func_name;
};

template<int N, class R, class... T>
function<N, R, T...>::function(lua_State* lua, std::string const& func_name) : _lua(lua), _func_name(func_name){

}

template<int N, class R, class... T>
R function<N, R, T...>::operator () (T... args) const{
	lua_settop(_lua, 0);
	
	lua_getfield(_lua, LUA_GLOBALSINDEX, _func_name.c_str());
	
	push_args(args...);

    // sizeof...(args)個の引数とN個の返り値で関数をコール
    int res= lua_pcall(_lua, sizeof...(args), N, 0);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args(number_t const& arg, T... args) const{
	lua_pushnumber(_lua, arg);
	push_args(args...);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args(string_t const& arg, T... args) const{
	lua_pushstring(_lua, arg);
	push_args(args...);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args(boolean_t const& arg, T... args) const{
	lua_pushboolean(_lua, arg);
	push_args(args...);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args(nil_t const& arg, T... args) const{
	lua_pushnil(_lua);
	push_args(args...);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args() const{}

}

#endif // #ifndef LUA_UTIL_FUNCTION_HPP_

