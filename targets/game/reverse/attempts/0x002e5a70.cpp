// ?dispatch@Rva002E5A70Call@@QAEXPAXPAVObject@@00@Z
// partial score=0.28 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// Retail 0x002E5A70, 549 bytes. The matched caller
// Code/GameEngine/Source/Common/Rva002E0E30RecordDispatch.cpp reaches this
// body through ILT thunk j_000122a6 (0x000122A6 -> FUN_006e5a70, i.e. this
// RVA) as `Rva002E5A70Call::dispatch(void *recordData, Object *object,
// void *argument2, void *argument3)`; that file is landed and already fixes
// this body's ABI, so the class stays the SAME opaque name it uses rather
// than the unproven "BfmeOwnerBR" a prior attempt guessed (BfmeOwnerBR's own
// landed member bfmeGo939B/bfmeTail939B at 0x002E7650/0x002E76xx take a
// different argument shape -- an int record index, not a raw recordData
// pointer -- so that identity does not actually fit this body).
//
// The Lua event body itself: reads a recursion-depth guard at +0xb0, the
// lua_State* at +8, looks up the object's event source, resolves the event
// name through a per-owner lookup thunk, pushes the object/argument2 as Lua
// values, walks up to three BfmeLuaEventArgument records (kind 1 = resolve
// by ObjectID, 2 = bool literal, 3 = float literal), and calls the Lua
// function when it found a name. AsciiString eventName(*name) is the
// canonical by-value string shape (reference/shims/stringinline) -- the
// prior attempt's hand-rolled StringBase<T> did not resolve to the real
// matched releaseBuffer body at 0x00887940.

template <class T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);

protected:
	void releaseBuffer();
	char *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString &operator=(const char *text);
	~AsciiString() { releaseBuffer(); }
};

class Object;
struct lua_State;
struct BfmeQ1039;

class BfmeEventNameLookup
{
public:
	AsciiString *lookup(void *recordData, bool *hasEventName);
};

class BfmeLuaValuePush
{
public:
	void push(lua_State *state, void *value);
};

extern "C" int lua_gettop(lua_State *state);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_call(lua_State *state, int arguments, int results);
extern "C" void lua_settop(lua_State *state, int index);
extern "C" void *g_activeObj12F0610;

class GameLogic
{
public:
	Object *bfmeFind1011(int id);
};

extern GameLogic *TheBfmeGameLogic;
extern void bfmeGo1039E(BfmeQ1039 *q, int value);
extern void j_00033078(void);
extern void j_000454e4(void);
extern void j_0003ebad(void);

struct BfmeLuaEventArgument
{
	char m_pad00[8];
	float m_real;
	unsigned char m_bool;
	char m_pad0d[3];
	int m_objectID;
	char m_pad14[4];
	int m_kind;
};

static __forceinline AsciiString *bfmeLookupEventName(void *owner,
	void *recordData, bool *hasEventName)
{
	typedef AsciiString *(BfmeEventNameLookup::*Function)(void *, bool *);
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_000454e4;
	return (reinterpret_cast<BfmeEventNameLookup *>(owner)->*fn.member)(
		recordData, hasEventName);
}

class Rva002E5A70Call
{
public:
	void dispatch(void *recordData, Object *object, void *argument2,
		void *argument3);
};

static __forceinline void bfmePushLuaValue(Rva002E5A70Call *owner,
	lua_State *state, void *value)
{
	typedef void (BfmeLuaValuePush::*Function)(lua_State *, void *);
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_00033078;
	(reinterpret_cast<BfmeLuaValuePush *>(owner)->*fn.member)(state, value);
}

static __forceinline void bfmeNotifyLuaEvent(const char *name)
{
	typedef void (*Function)(const char *);
	union
	{
		void (*raw)(void);
		Function typed;
	} fn;
	fn.raw = j_0003ebad;
	fn.typed(name);
}

void Rva002E5A70Call::dispatch(void *recordData, Object *object,
	void *argument2, void *argument3)
{
	if (*(int *)((char *)this + 0xb0) > 10)
		return;

	lua_State *state = *(lua_State **)((char *)this + 8);
	int top = lua_gettop(state);
	g_activeObj12F0610 = 0;

	char *objectBytes = (char *)object;
	void *eventSource = *(void **)(objectBytes + 0x204);
	if (eventSource == 0 || (objectBytes[0x344] & 1) != 0)
		return;

	void *eventOwner = *(void **)((char *)eventSource + 0x200);
	if (eventOwner == 0)
		return;

	bool hasEventName = false;
	AsciiString *name = bfmeLookupEventName(eventOwner, recordData,
		&hasEventName);
	if (name == 0)
		return;

	AsciiString eventName(*name);
	char *eventData = *(char **)&eventName;
	if (eventData == 0 || *(unsigned short *)(eventData + 4) == 0)
		return;

	lua_getglobal(state, eventData + 8);
	if (lua_type(state, 1) != 5)
	{
		AsciiString error;
		error = lua_type(state, 1) == 1
			? (const char *)0x010CF7A8 : (const char *)0x010CF78C;
		return;
	}

	bfmePushLuaValue(this, state, object);
	bfmePushLuaValue(this, state, argument2);

	int argumentCount = 2;
	BfmeLuaEventArgument *arguments =
		reinterpret_cast<BfmeLuaEventArgument *>(argument3);
	for (int i = 0; i < 3; ++i)
	{
		BfmeLuaEventArgument *argument = arguments + i;
		switch (argument->m_kind)
		{
		case 1:
		{
			Object *resolved = TheBfmeGameLogic->bfmeFind1011(
				argument->m_objectID);
			bfmePushLuaValue(this, state, resolved);
			break;
		}
		case 2:
			bfmeGo1039E((BfmeQ1039 *)state, argument->m_bool != 0);
			break;
		case 3:
			bfmeGo1039E((BfmeQ1039 *)state, (int)argument->m_real);
			break;
		default:
			i = 3;
			continue;
		}
		++argumentCount;
	}

	if (hasEventName)
	{
		g_activeObj12F0610 = state;
		++*(int *)((char *)this + 0xb0);
		lua_call(state, argumentCount, 0);
		lua_settop(state, top);
		--*(int *)((char *)this + 0xb0);
	}

	if (g_activeObj12F0610 != 0 && *(int *)((char *)this + 0xb0) == 0)
	{
		bfmeNotifyLuaEvent((const char *)0x010CF754);
		g_activeObj12F0610 = 0;
	}
}
