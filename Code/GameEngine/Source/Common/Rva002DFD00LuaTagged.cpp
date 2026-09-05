// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lua tagged-value setter. switch(lua_type) writes this+0x04 float (kind 1),
// this+0x10 AsciiString (kind 4), this+0x08 bool via type-6 lookup (kind 2),
// or this+0x0C object-id via table lookup (kind 3). Type 6 is EA's
// Boolean tag (lobject.h); the retail header has no LUA_TBOOLEAN macro.
// Owning class not recovered; RVA-derived name.

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &other);

private:
	StringBase(const T *text);
	void releaseBuffer();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { releaseBuffer(); }
	void set(const AsciiString &other)
	{
		StringBase<char>::set(static_cast<const StringBase<char> &>(other));
	}
};

unsigned Rva00990030Lookup(lua_State *range, int index);
unsigned Rva00990210Lookup(lua_State *range, int index);

class Rva002DFD00Value
{
public:
	void setFromLua(lua_State *state, int index);

private:
	int m_pad00;
	float m_number;
	bool m_bool;
	unsigned m_object;
	AsciiString m_string;
	int m_kind;
};

void Rva002DFD00Value::setFromLua(lua_State *state, int index)
{
	switch (lua_type(state, index))
	{
	case 2:
		m_number = (float)lua_tonumber(state, index);
		m_kind = 1;
		break;
	case 3:
		{
			AsciiString text(lua_tostring(state, index));
			AsciiString *slot = &m_string;
			slot->set(text);
			m_kind = 4;
		}
		break;
	case 6:
		m_bool = Rva00990210Lookup(state, index) != 0;
		m_kind = 2;
		break;
	case 4:
		m_object = Rva00990030Lookup(state, index);
		m_kind = 3;
		break;
	default:
		m_kind = 0;
		break;
	}
}
