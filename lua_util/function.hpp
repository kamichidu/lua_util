#ifndef LUA_UTIL_FUNCTION_HPP_
#define LUA_UTIL_FUNCTION_HPP_

#include <string>
#include <lua.hpp>
#include "type.hpp"

namespace lua_util{

template<int N, class R, class... T>
class function{
	public:
		typedef type::number_t number_t;
		typedef type::string_t string_t;
		typedef type::boolean_t boolean_t;
		typedef type::nil_t nil_t;
	public:
		function(lua_State* lua, std::string const& func_name);
		~function();
	public:
		R operator () (T const&... args) const;
	private:
		template<class...Rest>
			void push_args(number_t const& arg, Rest const&... rests) const;
		template<class...Rest>
			void push_args(string_t const& arg, Rest const&... rests) const;
		template<class...Rest>
			void push_args(boolean_t const& arg, Rest const&... rests) const;
		template<class...Rest>
			void push_args(nil_t const& arg, Rest const&... rests) const;
		void push_args() const;
	private:
		lua_State*       _lua;
		std::string      _func_name;
};

template<int N, class R, class... T>
function<N, R, T...>::function(lua_State* lua, std::string const& func_name) : _lua(lua), _func_name(func_name){

}

template<int N, class R, class...T>
function<N, R, T...>::~function(){
	_lua=       nullptr; // 参照を持っているだけなので、deleteしない
	_func_name= "";
}

template<int N, class R, class... T>
R function<N, R, T...>::operator () (T const&... args) const{
	lua_settop(_lua, 0);
	
	lua_getfield(_lua, LUA_GLOBALSINDEX, _func_name.c_str());
	
	push_args(args...);

    // sizeof...(args)個の引数とN個の返り値で関数をコール
    int const err_code= lua_pcall(_lua, sizeof...(args), N, 0);

	switch(err_code){
		case LUA_ERRRUN:
			break;
		case LUA_ERRMEM:
			break;
		case LUA_ERRERR:
			break;
	}

	// TODO: 返り値について一考
	return 0;
}

template<int N, class R, class... T>
template<class...Rest>
void function<N, R, T...>::push_args(number_t const& arg, Rest const&... rests) const{
	lua_pushnumber(_lua, arg);
}

template<int N, class R, class... T>
template<class...Rest>
void function<N, R, T...>::push_args(string_t const& arg, Rest const&... rests) const{
	lua_pushstring(_lua, arg);
}

template<int N, class R, class... T>
template<class...Rest>
void function<N, R, T...>::push_args(boolean_t const& arg, Rest const&... rests) const{
	lua_pushboolean(_lua, arg);
}

template<int N, class R, class... T>
template<class...Rest>
void function<N, R, T...>::push_args(nil_t const& arg, Rest const&... rests) const{
	lua_pushnil(_lua);
}

template<int N, class R, class... T>
void function<N, R, T...>::push_args() const{}

}

#endif // #ifndef LUA_UTIL_FUNCTION_HPP_

