// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-
// Lua 4.0.1 lua_Debug layout and errorfb formatting family; BFME logger adaptation.
// The engine's Lua error reporter formats one debug frame and sends each
// fragment to the BFME logger.  The address-derived name is intentional: the
// retail body has no recovered source-level owner, while the Lua debug layout
// and both stack arguments are directly established by the calls below.

struct lua_State;

struct lua_Debug
{
	const char *event;
	int currentline;
	const char *name;
	const char *namewhat;
	int nups;
	int linedefined;
	const char *what;
	const char *source;
	char short_src[60];
	struct lua_TObject *_func;
};

extern "C" int lua_getinfo(lua_State *state, const char *options,
	lua_Debug *activation);
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *buffer, const char *format, ...);
extern void __cdecl bfmeLogMsg574(const char *message);

// ?Rva002E51C0LuaErrorFrame@@YAXPAUlua_State@@PAUlua_Debug@@@Z
void __cdecl Rva002E51C0LuaErrorFrame(lua_State *state, lua_Debug *activation)
{
	char buffer[120];

	lua_getinfo(state, "Snl", activation);
	switch (*activation->namewhat)
	{
	case 'g':
	case 'l':
		sprintf(buffer, "function `%.50s'",
			activation->name);
		break;
	case 'f':
		sprintf(buffer, "method `%.50s'",
			activation->name);
		break;
	case 't':
		sprintf(buffer, "`%.50s' tag method",
			activation->name);
		break;
	default:
	{
		if (*activation->what == 'm')
			sprintf(buffer, "main of %.70s",
				activation->short_src);
		else if (*activation->what == 'C')
			sprintf(buffer, "%.70s",
				activation->short_src);
		else
			sprintf(buffer, "function <%d:%.70s>",
				activation->linedefined, activation->short_src);
		activation->source = 0;
		break;
	}
	}

	bfmeLogMsg574(buffer);
	if (activation->currentline > 0)
	{
		sprintf(buffer, " at line %d",
			activation->currentline);
		bfmeLogMsg574(buffer);
	}
	if (activation->source)
	{
		sprintf(buffer, " [%.70s]",
			activation->short_src);
		bfmeLogMsg574(buffer);
	}
	bfmeLogMsg574("\n");
}
