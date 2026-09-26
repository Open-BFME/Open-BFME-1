// ?d_002e5790@@YAXXZ
// partial score=0.4 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// PARTIAL, score ~0.4. Address-derived candidate for 0x002E5790, a
// LuaScriptEngine event dispatch member. NOTE for the next agent: the
// r2 brief called 0x002E5A70 a "landed sibling" for this body; it is not.
// reverse/re_attempts.log shows it as a 0.45 partial (model=Codex,
// stash reverse/attempts/0x002e5a70.cpp) and reverse/functions.csv still
// points that row at Code/gen_asm/d_002e5390.asm (an unconverted dump).
// That stash IS still useful as a template for the thunk ABIs (event-name
// lookup via j_000454e4, Lua-value push via j_00033078, the StringBase/
// AsciiString shape) and this candidate reuses those. But its guessed
// 4-argument signature is wrong for 0x002E5790: this body's `ret 0xc` is
// only THREE explicit stack args -- P1 is a void** whose target is
// compared/forwarded, P2 is the Object*, P3 is the 3-element argument
// array directly (no separate 4th parameter), and there is an explicit
// `if (state == 0) return;` the sibling's reconstruction omitted.
//
// Residual from tools/probe.py at 0x002E5790: object is 580B vs retail
// 589B, first diff at +0x33, diffs cascade through nearly the whole body
// from ONE register-role choice at entry: retail keeps `this` in ESI,
// the lua_State* read as [this+8] in EAX (re-read at call sites rather
// than cached in a dedicated local), and 0 as a cached EBX constant reused
// across every null check; this candidate's compiler instead put `this`
// in EBX and the lua_State* pointer in EDI. The algorithm, field offsets
// (+8 state, +0xb0 recursion depth checked against 10, +0xb8 compare
// target, +0x204/+0x344/+0x200 on Object, the 0x18-byte-stride/kind@+0x18
// argument-array addressing, and the three thunk-callee ABIs) are all
// confirmed correct by matching structure through the whole function; only
// the register/local-caching shape at entry needs another pass, and it
// looks like the same class of lever documented in docs/matching.md's
// "Import called twice" row (CSE of a repeatedly-read field into a
// register happening before vs. after the compiler expects a cached local).

typedef bool Bool;
typedef int Int;

class Object;

class BfmeGlob939C
{
public:
	virtual void bfmeSlot939C00();
};

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
	char *raw() const { return m_data; }
};

struct lua_State;
struct BfmeQ1039;

class GameLogicRva002E5790
{
public:
	Object *bfmeFind1011(Int id);
};

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
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void *g_activeObj12F0610;

extern GameLogicRva002E5790 *TheBfmeGameLogic;
extern void bfmeGo1039E(BfmeQ1039 *q, int value);
extern void j_00033078(void);
extern void j_000454e4(void);
extern void j_00028bb9(void);
extern void j_0003ebad(void);
extern void j_0001f253(void);

class BfmeOwnerBRRva002E5790
{
public:
	void dispatch(void **recordSlot, Object *object, char *argsBase);
	char m_pad00[0xB0];
	Int m_recursionDepth;	// +0xb0
	char m_pad_b4[4];
	void *m_compareTarget;	// +0xb8
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

static __forceinline void bfmePushLuaValue(BfmeOwnerBRRva002E5790 *owner,
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

static __forceinline Object *bfmeFindObject(GameLogicRva002E5790 *gl, Int id)
{
	typedef Object *(GameLogicRva002E5790::*Function)(Int);
	union
	{
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_0001f253;
	return (gl->*fn.member)(id);
}

void BfmeOwnerBRRva002E5790::dispatch(void **recordSlot, Object *object,
	char *argsBase)
{
	lua_State *state = *(lua_State **)((char *)this + 8);
	if (state == 0)
		return;
	if (m_recursionDepth > 10)
		return;

	int top = lua_gettop(state);
	g_activeObj12F0610 = 0;

	char *objectBytes = (char *)object;
	void *eventSource = *(void **)(objectBytes + 0x204);
	if (eventSource == 0)
		return;

	if ((objectBytes[0x344] & 1) != 0)
	{
		if (*recordSlot != m_compareTarget)
			return;
	}

	void *eventOwner = *(void **)((char *)eventSource + 0x200);
	if (eventOwner == 0)
		return;

	bool hasEventName = false;
	AsciiString *name = bfmeLookupEventName(eventOwner, *recordSlot,
		&hasEventName);

	AsciiString eventName(*name);
	char *eventData = eventName.raw();
	if (eventData == 0 || *(unsigned short *)(eventData + 4) == 0)
		return;

	lua_getglobal(state, eventData + 8);
	if (lua_type(state, 1) != 5)
	{
		AsciiString error;
		error = (lua_type(state, 1) == 1)
			? (const char *)0x010CF7A8 : (const char *)0x010CF78C;
		lua_settop(state, top);
		return;
	}

	bfmePushLuaValue(this, state, object);

	int argumentCount = 1;
	for (int i = 0; i < 3; ++i)
	{
		char *arg = argsBase + i * 0x18;
		int kind = *(int *)(arg + 0x18);
		if (kind == 1)
		{
			lua_pushnumber(state, *(float *)(arg + 8));
		}
		else if (kind == 2)
		{
			bfmeGo1039E((BfmeQ1039 *)state, arg[0xc] != 0);
		}
		else if (kind == 3)
		{
			Object *resolved = bfmeFindObject(TheBfmeGameLogic,
				*(int *)(arg + 0x10));
			bfmePushLuaValue(this, state, resolved);
		}
		else
		{
			break;
		}
		++argumentCount;
	}

	if (hasEventName)
	{
		g_activeObj12F0610 = state;
		++m_recursionDepth;
		lua_call(state, argumentCount, 0);
		--m_recursionDepth;
	}

	if (g_activeObj12F0610 != 0 && m_recursionDepth == 0)
	{
		bfmeNotifyLuaEvent((const char *)0x010CF754);
		g_activeObj12F0610 = 0;
	}
}
