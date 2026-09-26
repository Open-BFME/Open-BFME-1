// cl: /MD
// Lua's tostring binding uses EA's boolean tag value 6 in its type switch.

#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"

int luaB_tostring(lua_State *L)
{
    char buff[64];

    switch (lua_type(L, 1)) {
    case LUA_TNUMBER:
    case 6:
        lua_pushstring(L, lua_tostring(L, 1));
        return 1;
    case LUA_TSTRING:
        lua_pushvalue(L, 1);
        return 1;
    case LUA_TTABLE:
        sprintf(buff, "table: %p", lua_topointer(L, 1));
        break;
    case LUA_TFUNCTION:
        sprintf(buff, "function: %p", lua_topointer(L, 1));
        break;
    case LUA_TUSERDATA:
        sprintf(buff, "userdata(%d): %p", lua_tag(L, 1), lua_touserdata(L, 1));
        break;
    case LUA_TNIL:
        lua_pushstring(L, "nil");
        return 1;
    default:
        luaL_argerror(L, 1, "value expected");
    }
    lua_pushstring(L, buff);
    return 1;
}
