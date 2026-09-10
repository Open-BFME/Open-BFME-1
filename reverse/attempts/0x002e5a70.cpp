// ?dispatch@BfmeOwnerBR@@QAEXPAXPAVObject@@00@Z
// partial score=0.45 date=2026-09-10
// Open-BFME5 conversions.

class BfmeGlob939A
{
public:
	virtual void bfmeSlot939A00();
	virtual void bfmeSlot939A01();
	virtual void bfmeSlot939A02();
	virtual void bfmeSlot939A03();
	virtual void bfmeTail939A();
};

extern BfmeGlob939A *g_bfme939GlobA;
void bfmeCall939A(void);

void bfmeGo939A(void)
{
	bfmeCall939A();
	g_bfme939GlobA->bfmeTail939A();
}

class Object;
class DelayedLuaEventList;

struct BfmeElem939B
{
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int i, Object *object, DelayedLuaEventList *events);
	void bfmeTail939B(BfmeElem939B *e, Object *object, DelayedLuaEventList *events);
	void dispatch(void *recordData, Object *object, void *argument2,
		void *argument3);
	char m_bfmePad[0x10];
	BfmeElem939B m_bfmeArr[1];
};

void BfmeOwnerBR::bfmeGo939B(int i, Object *object, DelayedLuaEventList *events)
{
	bfmeTail939B(&m_bfmeArr[i], object, events);
}

struct lua_State;
struct BfmeQ1039;

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

class GameLogic
{
public:
	Object *bfmeFind1011(int id);
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
extern "C" void *g_activeObj12F0610;

extern GameLogic *TheBfmeGameLogic;
extern void bfmeGo1039E(BfmeQ1039 *q, int value);
extern void j_00033078(void);
extern void j_000454e4(void);
extern void j_00028bb9(void);
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

static __forceinline void bfmePushLuaValue(BfmeOwnerBR *owner,
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

void BfmeOwnerBR::dispatch(void *recordData, Object *object,
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

class BfmeGlob939C
{
public:
	virtual void bfmeSlot939C00();
	virtual void bfmeSlot939C01();
	virtual void bfmeSlot939C02();
	virtual void bfmeSlot939C03();
	virtual void bfmeSlot939C04();
	virtual void bfmeSlot939C05();
	virtual void bfmeSlot939C06();
	virtual void bfmeSlot939C07();
	virtual void bfmeSlot939C08();
	virtual void bfmeSlot939C09();
	virtual void bfmeSlot939C10();
	virtual void bfmeSlot939C11();
	virtual void bfmeSlot939C12();
	virtual void bfmeSlot939C13();
	virtual void bfmeSlot939C14();
	virtual void bfmeSlot939C15();
	virtual void bfmeSlot939C16();
	virtual void bfmeSlot939C17();
	virtual void bfmeSlot939C18();
	virtual void bfmeSlot939C19();
	virtual void bfmeSlot939C20();
	virtual void bfmeSlot939C21();
	virtual void bfmeSlot939C22();
	virtual void bfmeSlot939C23();
	virtual void bfmeSlot939C24();
	virtual void bfmeSlot939C25();
	virtual void bfmeSlot939C26();
	virtual void bfmeSlot939C27();
	virtual void bfmeSlot939C28();
	virtual void bfmeSlot939C29();
	virtual void bfmeSlot939C30();
	virtual int bfmeVirt939C(int f);
};

extern BfmeGlob939C *g_bfme939GlobC;

int bfmeGo939C(void)
{
	int r = g_bfme939GlobC->bfmeVirt939C(0);
	return r == 0;
}

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

extern BfmeGlob939D *g_bfme939GlobD;

int __stdcall bfmeGo939D(char v)
{
	char r = g_bfme939GlobD->bfmeCall939D();
	return (char)(r - v) == 0;
}

extern char g_bfme939Str[];

class BfmeSub939E
{
public:
	void bfmeCall939E(int *out, char *s);
};

void bfmeGo939E(BfmeSub939E *a)
{
	int tmp;
	a->bfmeCall939E(&tmp, g_bfme939Str);
}

class BfmeSub939G
{
public:
	void bfmeCall939G();
	void *m_bfmeP;
};

class BfmeThing939G
{
public:
	void bfmeGo939G(void *a);
	char m_bfmePad[8];
	BfmeSub939G m_bfmeSub;
};

void BfmeThing939G::bfmeGo939G(void *a)
{
	BfmeSub939G *s = &m_bfmeSub;
	if (!a && s->m_bfmeP)
		s->bfmeCall939G();
}
