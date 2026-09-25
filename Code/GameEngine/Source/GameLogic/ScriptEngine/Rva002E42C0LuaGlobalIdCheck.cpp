// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Retail 0x002E42C0, 217 bytes. __thiscall(lua_State *, const owner *), ret 8.
// A null owner pushes nil. Otherwise the "ObjID#%08x" name the matched
// formatter at 0x002E32A0 builds is looked up as a Lua global on the lua_State
// at this+8; when that global is nil (type 1) or its 0x00990030 value is not
// the owner's id (+0x74), the stack is reset to that index and nil is pushed.
// Owner class and method identity are unproven: address-derived names.
//
// Retail keeps the EH frame but never stores state 0 for the string, only the
// -1 before its release (same shape in sibling 0x002E4180, which calls the
// same 0x00990030 helper inside the string's lifetime). Two things reproduce
// that: the helper cannot throw from this TU (like the extern "C" lapi.c
// calls around it), and the mismatch arm leaves the string's scope through
// its own `return`, which is what keeps the frame once no call can throw.

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" void lua_settop(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *range, int index) throw();

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

class Rva002E42C0Owner
{
public:
	void rva002E42C0(lua_State *state, const Rva002E32A0IdOwner *owner);

	char m_pad00[8];
	lua_State *m_state;
};

void Rva002E42C0Owner::rva002E42C0(
	lua_State *state, const Rva002E32A0IdOwner *owner)
{
	if (!owner)
	{
		lua_pushnil(m_state);
		return;
	}

	Rva002E32A0AsciiString name = Rva002E32A0ObjectIdAsStr(owner);
	int ownerId = owner->m_id;
	lua_getglobal(m_state, name.str());
	int index = lua_gettop(state);
	if (lua_type(m_state, index) == 1 ||
		ownerId != (int)Rva00990030Lookup(m_state, index))
	{
		lua_settop(m_state, index);
		lua_pushnil(m_state);
		return;
	}
}
