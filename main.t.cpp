#include <lua_util.hpp>
#include <iostream>

int main(int argc, char* argv[]){
	lua_util::lua lua;

	auto print= lua.define_function<0, int, lua_util::type::string_t>("print");
	auto abs=   lua.define_function<1, lua_util::type::number_t, lua_util::type::number_t>("math.abs");

	print("hello?");
	std::cout << abs(-30.5) << std::endl;

	return 0;
}

