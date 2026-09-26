// ?updateObjectGlobal@Rva002E4030LuaHost@@QAEXPAURva002E32A0IdOwner@@@Z
// partial score=0.95 date=2026-09-06
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline

// Lua object-global refresh at retail RVA 0x002E4030.
// The host stores Lua state pointers at this+0x08 and this+0x0c and receives an Object pointer.

struct lua_State;
struct Rva00990030Range;
struct BfmeStateUPC;

template <typename T> class Rva002E4030StringBase
{
protected:
	Rva002E4030StringBase() throw() : m_data(0) {}
	Rva002E4030StringBase(const Rva002E4030StringBase &that) throw()
		: m_data(that.m_data) {}
	~Rva002E4030StringBase() throw();

	void *m_data;
};

class Rva002E32A0AsciiString : private Rva002E4030StringBase<char>
{
public:
	Rva002E32A0AsciiString() throw() : Rva002E4030StringBase<char>() {}
	Rva002E32A0AsciiString(const Rva002E32A0AsciiString &that) throw()
		: Rva002E4030StringBase<char>(that) {}
	~Rva002E32A0AsciiString() throw() {}

	const char *str() const
	{
		return m_data != 0 ? (const char *)m_data + 8 : "";
	}
};

extern "C" void lua_settop(lua_State *state, int index);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_setglobal(lua_State *state, const char *name);

unsigned Rva00990030Lookup(Rva00990030Range *range, int index);
void bfmeGoUPC(BfmeStateUPC *state, int objectId);
struct Rva002E4030Template;

struct Rva002E32A0IdOwner
{
	char m_unknown00[4];
	Rva002E4030Template *m_template;
	char m_unknown08[0x74 - 0x08];
	int m_id;
	char m_unknown78[0x204 - 0x78];
	void *m_ai;
};

__declspec(nothrow) Rva002E32A0AsciiString Rva002E32A0ObjectIdAsStr(const Rva002E32A0IdOwner *owner);

class BfmeAskResult
{
	public:
	char m_unknown00[0x4c8];
	unsigned char m_ready;
};

class BfmeSubBIA
{
public:
	BfmeAskResult *lastNode00087A80();
};

struct Rva002E4030Template
{
	char m_unknown00[4];
	BfmeSubBIA *m_nextOverride;
	char m_unknown08[0x4c8 - 0x08];
	unsigned char m_ready;
};

class Rva002E4030LuaHost
{
public:
	void updateObjectGlobal(Rva002E32A0IdOwner *object);

	char m_unknown00[8];
	lua_State *m_state;
	lua_State *m_stackState;
};

void Rva002E4030LuaHost::updateObjectGlobal(Rva002E32A0IdOwner *object)
{
	if (object->m_ai == 0)
	{
		Rva002E4030Template *objectTemplate = object->m_template;
		if (objectTemplate != 0)
		{
			BfmeSubBIA *overrideNode = objectTemplate->m_nextOverride;
			if (overrideNode != 0)
				objectTemplate = (Rva002E4030Template *)overrideNode->lastNode00087A80();
		}
		if (objectTemplate->m_ready == 0)
			return;
	}

	lua_settop(m_stackState, 0);
	const Rva002E32A0AsciiString objectName = Rva002E32A0ObjectIdAsStr(object);
	int objectId = object->m_id;
	lua_getglobal(m_state, objectName.str());
	if (lua_type(m_state, 1) != 1 &&
		(unsigned)objectId == Rva00990030Lookup((Rva00990030Range *)m_state, 1))
	{
		lua_settop(m_state, -2);
		return;
	}
	lua_settop(m_state, -2);
	bfmeGoUPC((BfmeStateUPC *)m_state, objectId);
	lua_setglobal(m_state, objectName.str());
}
