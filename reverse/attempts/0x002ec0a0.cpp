// ?rva002EC0A0ParseTokenEventList@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.22 date=2026-09-25
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x002EC0A0. Owner layout and helper contracts are read from retail.
// stlport

#include <vector>
#include "ascii_string.h"

struct lua_State;
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_settop(lua_State *state, int index);

typedef int NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern char Rva006A16B0Empty[];

struct Gen002E1260
{
	NameKeyType m_key;
	AsciiString m_function;
	unsigned char m_debugSingleStep;
	char m_padding[3];
};

struct Gen002E9E10
{
	AsciiString m_name;
	unsigned char m_flag;
	char m_padding[3];
	_STL::vector<Gen002E1260> m_functions;
};

typedef char Gen002E1260Size[(sizeof(Gen002E1260) == 12) ? 1 : -1];
typedef char Gen002E9E10Size[(sizeof(Gen002E9E10) == 20) ? 1 : -1];

class BfmeThingBUF
{
public:
	AsciiString m_name;
	unsigned char m_flag;
	char m_padding[3];
	_STL::vector<Gen002E1260> m_functions;

	BfmeThingBUF *bfmeInitBUF(void *name);
	void assignFrom(const BfmeThingBUF &other);
	void rva002E1CB0(void *entry);
};

typedef char BfmeThingBUFSize[(sizeof(BfmeThingBUF) == 20) ? 1 : -1];

class XmlNameSlotList
{
public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	int finish();
};

class Rva0035EF40
{
public:
	const char *get();
};

class LuaScriptEngine
{
	char m_pad00[8];
	lua_State *m_luaState;
	char m_pad0C[0x7C];
	unsigned char m_eventEnd;
	char m_pad89[3];
	_STL::vector<Gen002E9E10> m_eventBuffer;
	char m_pad98[0x1C];
	unsigned char m_keepOpen;

public:
	Gen002E9E10 *rva002EBF60Lookup(const AsciiString &name);
	void rva002EC0A0ParseTokenEventList(class BfmeLexEAN *parser);
};

#pragma comment(linker, "/alternatename:?bfmeInitBUF@BfmeThingBUF@@QAEPAV1@PAX@Z=?j_00038401@@YAXXZ")
#pragma comment(linker, "/alternatename:?assignFrom@BfmeThingBUF@@QAEXABV1@@Z=?j_0001226f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002E1CB0@BfmeThingBUF@@QAEXPAX@Z=?j_000405b6@@YAXXZ")
#pragma comment(linker, "/alternatename:?count@XmlNameSlotList@@QAEHXZ=?j_00038fc8@@YAXXZ")
#pragma comment(linker, "/alternatename:?tagAt@XmlNameSlotList@@QAEPBDH@Z=?j_0003a5fd@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameAt@XmlNameSlotList@@QAEPBDH@Z=?j_00027a7a@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@XmlNameSlotList@@QAEHXZ=?j_00049ae4@@YAXXZ")
#pragma comment(linker, "/alternatename:?get@Rva0035EF40@@QAEPBDXZ=?j_000262ba@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EBF60Lookup@LuaScriptEngine@@QAEPAVGen002E9E10@@ABVAsciiString@@@Z=?j_00035107@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EC0A0ParseTokenEventList@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_0003ed33@@YAXXZ")

struct StringHeaderView
{
	int m_references;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

static inline StringHeaderView *stringHeader(const AsciiString &value)
{
	return *(StringHeaderView *const *)&value;
}

static inline const char *stringData(const AsciiString &value)
{
	return value.str();
}

static inline int stringLength(const char *value)
{
	int length = 0;
	if (value != 0)
	{
		while (*value != 0)
		{
			++value;
			++length;
		}
	}
	return length;
}

static inline bool stringPresent(const AsciiString &value)
{
	return value.isNotEmpty();
}

static inline bool sameString(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

static inline void setString(AsciiString &destination, const char *value)
{
	((StringBase<char> *)&destination)->set(value, stringLength(value));
}

void LuaScriptEngine::rva002EC0A0ParseTokenEventList(BfmeLexEAN *parser)
{
	XmlNameSlotList *xml = (XmlNameSlotList *)parser;
	AsciiString name;
	AsciiString inherit;
	int index = 0;
	if (xml->count() > 0)
	{
		do
		{
			const char *value = xml->nameAt(index);
			const char *tag = xml->tagAt(index);
			if (strcmp(tag, "Name") == 0)
				setString(name, value);
			else if (strcmp(tag, "Inherit") == 0)
				setString(inherit, value);
			++index;
		} while (index < xml->count());
	}

	BfmeThingBUF record;
	record.bfmeInitBUF(&name);
	int status = xml->finish();
	BfmeThingBUF *inherited = (BfmeThingBUF *)rva002EBF60Lookup(inherit);
	if (inherited != 0)
		record.assignFrom(*inherited);

	while (status == 1)
	{
		const char *current = ((Rva0035EF40 *)parser)->get();
		if (strcmp(current, "EventHandler") == 0)
		{
			AsciiString eventName;
			AsciiString functionName;
			bool debugSingleStep = false;
			index = 0;
			if (xml->count() > 0)
			{
				do
				{
					const char *value = xml->nameAt(index);
					const char *tag = xml->tagAt(index);
					if (strcmp(tag, "EventName") == 0)
						setString(eventName, value);
					else if (strcmp(tag, "ScriptFunctionName") == 0)
						setString(functionName, value);
					else if (strcmp(tag, "DebugSingleStep") == 0)
						debugSingleStep = strcmp(value, "true") == 0;
					++index;
				} while (index < xml->count());
			}

			if (stringPresent(eventName) && stringPresent(functionName))
			{
				lua_getglobal(m_luaState, stringData(functionName));
				int type = lua_type(m_luaState, -1);
				if (type != 5)
				{
					AsciiString error;
					if (lua_type(m_luaState, -1) == 1)
						setString(error, " is not defined.");
					else
						setString(error, " is not a lua function.");
				}
				lua_settop(m_luaState, -2);

				Gen002E1260 entry;
				entry.m_key = TheNameKeyGenerator->nameToKey(stringData(eventName));
				entry.m_function = functionName;
				entry.m_debugSingleStep = debugSingleStep;
				record.rva002E1CB0(&entry);
			}
		}
		status = xml->finish();
	}

	if (status == 0 && m_keepOpen)
	{
		m_eventEnd = 0;
		Gen002E9E10 *entry = m_eventBuffer.begin();
		Gen002E9E10 *end = m_eventBuffer.end();
		while (entry != end)
		{
			if (sameString(entry->m_name, record.m_name))
			{
				((StringBase<char> *)&entry->m_name)->set(
					*(StringBase<char> *)&record.m_name);
				entry->m_flag = record.m_flag;
				entry->m_functions = record.m_functions;
				break;
			}
			++entry;
		}
		if (entry == end)
			m_eventBuffer.push_back(*(Gen002E9E10 *)&record);
	}
}
