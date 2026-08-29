// cl: /DNDEBUG /MD /EHsc
//
// A flag lookup landed as a relocation-blind twin of the findFlag in
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineClearFlag.cpp
// (0x00344E10).  It differs from the model in one callee and in its own EH
// table; the key building, the tree probe and the header comparison that
// stands in for end() are all the same.
//
// The declarations are the model's, renamed so the two do not collide.

class AsciiString;

template<class T> class StringBase
{
private:
	friend class AsciiString;
	struct Data
	{
		int refs;
		int length;
		T data[1];
	};

	Data *m_data;
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	void __cdecl format(AsciiString format, ...);
	const char *str() const { return m_data ? m_data->data : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void clearFlag(const AsciiString &name);
};

// Retail's helper name is unknown, so keep the proven this/by-value ABI local
// instead of assigning an unsupported canonical identity to its 0x00344E10 body.
class Open2FlagName344B20
{
public:
	Open2FlagName344B20(const AsciiString &canonical, const AsciiString &name) :
		m_canonical(canonical), m_name(name) {}
	~Open2FlagName344B20();

private:
	AsciiString m_canonical;
	AsciiString m_name;
};

struct Open2FlagNode344B20
{
	void *m_treeLinks[4];
	Open2FlagName344B20 m_key;
	bool m_value;
};

struct Open2FlagMap344B20
{
	Open2FlagNode344B20 *m_header;
	__declspec(nothrow) Open2FlagNode344B20 *find(const Open2FlagName344B20 &name);
};


class Open2Lookup344B20
{
public:
	bool *findFlag(AsciiString name);

private:
	AsciiString canonicalFlagName(const AsciiString &name);
	char m_flagMapPad[0x16040];
	Open2FlagMap344B20 m_flags;
};

// @?findFlag@Open2Lookup344B20@@QAEPA_NVAsciiString@@@Z 0x00344B20
bool *Open2Lookup344B20::findFlag(AsciiString name)
{
	AsciiString canonical = canonicalFlagName(name);
	// Extending this temporary through both returns preserves retail's one composite cleanup.
	const Open2FlagName344B20 &key = Open2FlagName344B20(canonical, name);
	Open2FlagNode344B20 *found = m_flags.find(key);
	if (found != m_flags.m_header)
		return &found->m_value;
	return 0;
}
