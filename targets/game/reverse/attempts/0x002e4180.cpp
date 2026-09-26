// ?rva002E4180ClearGlobal@Rva002E4180Owner@@QAEXPAURva002E32A0IdOwner@@@Z
// partial score=0.49 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x002E4180 (247 B), EH-framed. Clears a Lua global
// that mirrors a game object, but only when the cached identity check
// (Rva00990030Lookup) still matches the object's +0x74 id. Vendored Lua
// 4.0.1 API (Code/Libraries/Source/Lua/lapi.c, lua.h): LUA_TNIL == 1.
//
// The name string is built by the already-landed Rva002E32A0ObjectIdAsStr
// (0x002E32A0) into a local Rva002E32A0AsciiString (hidden-return-by-value);
// its destructor is pinned to 0x00887940 (releaseBuffer), which is why the
// exception frame exists at all -- to run that destructor if anything
// between construction and the manual settop/pushnil/setglobal dance
// throws.
//
// this+0x08 is the lua_State used for every call but the very first
// settop, which instead reads this+0x0C (byte-proven from the retail
// push order: the value pushed closest to that call is [esi+0xc], not
// [esi+8]); identity of that second state is not recovered.

struct lua_State;

extern "C"
{
	void __cdecl lua_settop(lua_State *L, int index);
	int __cdecl lua_type(lua_State *L, int index);
	void __cdecl lua_getglobal(lua_State *L, const char *name);
	void __cdecl lua_pushnil(lua_State *L);
	void __cdecl lua_setglobal(lua_State *L, const char *name);
}

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class Rva002E32A0AsciiString;
};

class Rva002E32A0AsciiString
{
public:

	Rva002E32A0AsciiString() { m_text = 0; }

	Rva002E32A0AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	Rva002E32A0AsciiString(const Rva002E32A0AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~Rva002E32A0AsciiString();

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

private:

	void *m_text;

};

struct Rva002E32A0IdOwner
{
	unsigned char pad00[0x74];
	int m_id;
};

Rva002E32A0AsciiString Rva002E32A0ObjectIdAsStr(const Rva002E32A0IdOwner *p);
unsigned int Rva00990030Lookup(void *range, int index);

class Rva002E4180Owner
{
public:
	void rva002E4180ClearGlobal(Rva002E32A0IdOwner *owner);

private:
	unsigned char m_pad00[8];
	void *m_L;
	void *m_rootL;
};

void Rva002E4180Owner::rva002E4180ClearGlobal(Rva002E32A0IdOwner *owner)
{
	if (m_L == 0)
		return;

	lua_settop((lua_State *)m_rootL, 0);

	Rva002E32A0AsciiString text = Rva002E32A0ObjectIdAsStr(owner);
	int verify = owner->m_id;
	const char *textPtr = text.str();

	lua_getglobal((lua_State *)m_L, textPtr);

	if (lua_type((lua_State *)m_L, 1) == 1)
	{
		lua_settop((lua_State *)m_L, -2);
	}
	else
	{
		unsigned int looked = Rva00990030Lookup(m_L, 1);
		if (verify != (int)looked)
		{
			lua_settop((lua_State *)m_L, -2);
		}
		else
		{
			lua_settop((lua_State *)m_L, -2);
			lua_pushnil((lua_State *)m_L);
			lua_setglobal((lua_State *)m_L, text.str());
		}
	}
}

// @?rva002E4180ClearGlobal@Rva002E4180Owner@@QAEXPAURva002E32A0IdOwner@@@Z 0x002E4180
