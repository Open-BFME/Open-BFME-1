// BFME's print binding sends its separators and text through the game logger.

struct lua_State;

extern "C" {
int lua_gettop(lua_State *state);
void lua_getglobal(lua_State *state, const char *name);
void lua_pushvalue(lua_State *state, int index);
void lua_rawcall(lua_State *state, int nargs, int nresults);
const char *lua_tostring(lua_State *state, int index);
void lua_settop(lua_State *state, int index);
void lua_error(lua_State *state, const char *message);
}

extern void bfmeLogMsg574(const char *message);

extern "C" int luaB_print(lua_State *state)
{
    int count = lua_gettop(state);
    int index;

    lua_getglobal(state, "tostring");
    for (index = 1; index <= count; index++) {
        const char *text;

        lua_pushvalue(state, -1);
        lua_pushvalue(state, index);
        lua_rawcall(state, 1, 1);
        text = lua_tostring(state, -1);
        if (text == 0)
            lua_error(state, "`tostring' must return a string to `print'");
        if (index > 1)
            bfmeLogMsg574("\t");
        bfmeLogMsg574(text);
        lua_settop(state, -2);
    }
    bfmeLogMsg574("\n");
    return 0;
}
