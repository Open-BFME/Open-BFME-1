// ?dispatchGlobalById@Rva002E42C0Engine@@QAEXPAUlua_State@@PBURva002E32A0IdOwner@@@Z
// partial score=0.96 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Retail 0x002E42C0, 217 bytes. The body uses the object-name formatter at
// 0x002E32A0, checks the Lua global against the owner's id, and releases the
// temporary string after the Lua checks.

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" void lua_settop(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *range, int index);

struct Rva002E32A0IdOwner
{
	unsigned char m_pad00[0x74];
	int m_id;
};

class Rva002E32A0AsciiString
{
public:
	~Rva002E32A0AsciiString();

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

	private:
	void *m_text;
};


Rva002E32A0AsciiString Rva002E32A0ObjectIdAsStr(
	const Rva002E32A0IdOwner *owner);

class Rva002E42C0Engine
{
public:
	void dispatchGlobalById(lua_State *state,
		const Rva002E32A0IdOwner *owner);

	char m_pad00[8];
	lua_State *m_state;
};

void Rva002E42C0Engine::dispatchGlobalById(
	lua_State *state, const Rva002E32A0IdOwner *owner)
{
	if (!owner)
	{
		lua_pushnil(m_state);
		return;
	}

	const Rva002E32A0AsciiString &result = Rva002E32A0ObjectIdAsStr(owner);
	int ownerId = owner->m_id;
	lua_getglobal(m_state, result.str());
	int index = lua_gettop(state);
	if (lua_type(m_state, index) == 1 ||
		ownerId != (int)Rva00990030Lookup(m_state, index))
	{
		lua_settop(m_state, index);
		lua_pushnil(m_state);
	}
	return;
}
