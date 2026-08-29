// cl: /DNDEBUG /DWIN32 /MD /O2

typedef float Real;

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

int GetClientRandomNumberReal(lua_State *state)
{
	if (lua_gettop(state) <= 1) {
		lua_pushnumber(state, 0.0);
	} else {
		Real low = (Real)lua_tonumber(state, 1);
		Real high = (Real)lua_tonumber(state, 2);
#line 1744 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\LuaScriptEngine.cpp"
		lua_pushnumber(state, GetGameClientRandomValueReal(low, high, __FILE__, __LINE__));
	}
	return 1;
}
