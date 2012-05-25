#ifndef LUA_UTIL_FUNCTION_HPP_
#define LUA_UTIL_FUNCTION_HPP_

#include <string>
#include <lua.hpp>
#include "type.hpp"

namespace lua_util{

template<class> class function;

template<class R, class...ArgTypes>
class function<R(ArgTypes...)>{
	public:
		typedef type::number_t number_t;
		typedef type::string_t string_t;
		typedef type::boolean_t boolean_t;
		typedef type::nil_t nil_t;
	public:
		function(lua_State* lua, std::string const& func_name);
		~function();
	public:
		R operator () (ArgTypes const&... args) const;
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
		void pop_return_value(number_t& dest) const;
		void pop_return_value(string_t& dest) const;
		void pop_return_value(boolean_t& dest) const;
	private:
		lua_State*       _lua;
		std::string      _func_name;
};

template<class R, class...ArgTypes>
inline
function<R(ArgTypes...)>::function(lua_State* lua, std::string const& func_name) : _lua(lua), _func_name(func_name){

}

template<class R, class...ArgTypes>
inline
function<R(ArgTypes...)>::~function(){
	_lua=       nullptr; // 参照を持っているだけなので、deleteしない
	_func_name= "";
}

template<class R, class...ArgTypes>
inline
R function<R(ArgTypes...)>::operator () (ArgTypes const&... args) const{
	int constexpr ret_values= 1; // 現状1つの返り値のみに対応

	lua_settop(_lua, 0);
	
	lua_getfield(_lua, LUA_GLOBALSINDEX, _func_name.c_str());
	
	push_args(args...);

    // sizeof...(args)個の引数とN個の返り値で関数をコール
    int const err_code= lua_pcall(_lua, sizeof...(args), ret_values, 0);

	switch(err_code){
		case LUA_ERRRUN:
			break;
		case LUA_ERRMEM:
			break;
		case LUA_ERRERR:
			break;
	}

	R ret;

	pop_return_value(ret);

	return ret;
}

template<class R, class...ArgTypes>
template<class...Rest>
inline
void function<R(ArgTypes...)>::push_args(number_t const& arg, Rest const&... rests) const{
	lua_pushnumber(_lua, arg);
}

template<class R, class...ArgTypes>
template<class...Rest>
inline
void function<R(ArgTypes...)>::push_args(string_t const& arg, Rest const&... rests) const{
	lua_pushstring(_lua, arg);
}

template<class R, class...ArgTypes>
template<class...Rest>
inline
void function<R(ArgTypes...)>::push_args(boolean_t const& arg, Rest const&... rests) const{
	lua_pushboolean(_lua, arg);
}

template<class R, class...ArgTypes>
template<class...Rest>
inline
void function<R(ArgTypes...)>::push_args(nil_t const& arg, Rest const&... rests) const{
	lua_pushnil(_lua);
}

template<class R, class...ArgTypes>
inline
void function<R(ArgTypes...)>::push_args() const{}

template<class R, class...ArgTypes>
inline
void function<R(ArgTypes...)>::pop_return_value(number_t& dest) const{
	dest= lua_tonumber(_lua, -1);
}

template<class R, class...ArgTypes>
inline
void function<R(ArgTypes...)>::pop_return_value(string_t& dest) const{
	dest= lua_tostring(_lua, -1);
}

template<class R, class...ArgTypes>
inline
void function<R(ArgTypes...)>::pop_return_value(boolean_t& dest) const{
	dest= lua_toboolean(_lua, -1);
}

}

#endif // #ifndef LUA_UTIL_FUNCTION_HPP_

