#include <lua_util.hpp>
#include <iostream>
#include <lua_util/function.hpp>

int main(int argc, char* argv[]){
	lua_util::lua lua;

	auto const print= lua_util::function<lua_util::type::number_t(lua_util::type::string_t)>(lua, "print");
	auto const abs=   lua_util::function<lua_util::type::number_t(lua_util::type::number_t)>(lua, "math.abs");

	print("hello?");
	std::cout << abs(-30.5) << std::endl;

	return 0;
}

