// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The Lua callback prefixes a temporary retail string with the Lua argument.

#include <string.h>

struct lua_State;

extern "C" const char *lua_tostring(lua_State *state, int index);

class AsciiString
{
	friend class BFMERetailAsciiString;

	public:
	AsciiString(const char *text);
	void concat(const char *text, int length);

	private:
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private AsciiString
{
public:
	BFMERetailAsciiString(const char *text) : AsciiString(text) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

	void concat(const char *text, int length)
	{
		AsciiString::concat(text, length);
	}
};

// ?Rva002E33B0LuaStringSuffix@@YAHPAUlua_State@@@Z
int Rva002E33B0LuaStringSuffix(lua_State *state)
{
	const char *text = lua_tostring(state, 1);
	BFMERetailAsciiString message((const char *)0x010CF500);
	if (text)
		message.concat(text, (int)strlen(text));
	return 0;
}
