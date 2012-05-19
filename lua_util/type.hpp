#ifndef LUA_UTIL_TYPE_HPP_
#define LUA_UTIL_TYPE_HPP_

#include <lua.hpp>

namespace lua_util{
namespace type{

class nil{
};

typedef lua_Number  number_t;
typedef char const* string_t;
typedef bool        boolean_t;
typedef nil         nil_t;

}
}

#endif // #ifndef LUA_UTIL_TYPE_HPP_


