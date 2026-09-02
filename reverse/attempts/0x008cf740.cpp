// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// partial score=0.47 date=2026-09-02
// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// PC Apt function dispatch.  The older BFME Apt runtime folds the native and
// script-function paths into this member (the later console SDK split them).
#include <new>

struct AptStringBlock { unsigned short refs; };
extern AptStringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class AptStringC
{
public:
	AptStringC(const char *text);
	~AptStringC()
	{
		AptStringBlock *block = m_block;
		--block->refs;
		if (block->refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
	AptStringBlock *m_block;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual int functionKind();

	unsigned flags;
	char gap08[0x18];
	void *runtime;
	char gap24[4];
	void *scope;
	char gap2c[4];
	void *body;

	bool isDefined() const { return (flags & 0x8000) != 0; }
	bool isPermanent() const { return ((flags >> 30) & 1) != 0; }
};

typedef AptValue *(__cdecl *AptNativeCallback)(AptValue *, int);

struct AptFunctionBody
{
	int unused0;
	int argumentCount;
	void **arguments;
	int byteCodeSize;
	unsigned short frameFlags;
	unsigned short frameFlags2;
	int localCount;
	int constantCount;
	AptValue **constantPool;
	unsigned char byteCode[1];
};

class AptFrameState
{
public:
	AptFrameState();
	int count;
	int capacity;
	AptValue **values;
	int localCount;
	void *locals;
	int flags;
};

extern void *Rva008C4890(unsigned size);
extern AptValue *g_bfmeFallbackDB;
extern AptValue *g_bfmeThisValue;
extern const char g_bfmeRootName[];
extern const char g_bfmeParentName[];

class BfmeStackBB { public: void bfmePopN(int count); };
class BfmeThing937E { public: void bfmeGo937E(AptFrameState *state); };
class Rva008A0F20Header { public: int isKind13() const; unsigned flags; char gap[0x58]; unsigned state; bool isDefined() const { return (flags & 0x8000) != 0; } };

class AptActionInterpreter
{
public:
	void callFunction(AptValue *callScope, AptValue *function, int argumentCount);
	void append(void *, void *, AptStringC *, AptValue *, int, int, int);
	void runStream(void *, void *, int);
	AptValue *findValue(void *, const char *, int);
	AptValue *makeValue(void *, void *, const char *, int, int, int);

	int stackCount;
	int stackCapacity;
	AptValue **stack;
	int frameCount;
	int frameCapacity;
	AptFrameState **frames;
	char gap18[0x18];
	int scopeCount;
	int scopeCapacity;
	AptValue **scopes;
	int stringCount;
	int stringCapacity;
	AptValue **strings;
	int registerDepth;
	int registerWidth;
	AptValue **registerBase;
	AptValue **registers;
	int constantCount;
	AptValue **constantPool;
	char gap64[0x18];
	AptValue *abortValue;
};

static void releaseValue(AptValue *value)
{
	if (value && !value->isPermanent())
		value->Release();
}

void AptActionInterpreter::callFunction(AptValue *callScope, AptValue *functionArg,
	int argumentCount)
{
	AptValue *result;
	register AptValue *function = functionArg;
	const int oldStackCount = stackCount;
	if (function != 0)
	{
		unsigned kind = function->flags & 0x3f;
		if (kind == 9 && function->isDefined())
		{
			AptNativeCallback callback = *(AptNativeCallback *)((char *)function + 0x20);
			result = callback(callScope, argumentCount);
			reinterpret_cast<BfmeStackBB *>(this)->bfmePopN(argumentCount);
			stack[stackCount++] = result;
			if (!result->isPermanent())
				result->AddRef();
			goto finished;
		}
		if (kind == 10 && function->isDefined())
		{
			const int savedConstantCount = constantCount;
			AptValue **savedConstantPool = constantPool;
			int representation = function->functionKind();
			if (representation == 1)
			{
				Rva008A0F20Header *bound = (Rva008A0F20Header *)function->scope;
				AptFunctionBody *body = (AptFunctionBody *)function->body;
				int savedStringCount = stringCount;
				if (!bound->isDefined() ||
					(bound->isKind13() && (bound->state & 0xc0000) == 0) ||
					((bound->state & 0xc0000) == 0x80000))
					goto unusable;
				constantCount = body->constantCount;
				constantPool = body->constantPool;
				AptFrameState *frame = (AptFrameState *)function->runtime;
				if (frame == 0)
				{
					void *storage = Rva008C4890(sizeof(AptFrameState));
					frame = storage ? new(storage) AptFrameState : 0;
				}
				reinterpret_cast<BfmeThing937E *>(&frameCount)->bfmeGo937E(frame);
				int bindCount = body->argumentCount < argumentCount ? body->argumentCount : argumentCount;
				for (int i = 0; i < body->argumentCount; ++i)
				{
					AptValue *value = i < bindCount ? stack[stackCount - i - 1] : g_bfmeFallbackDB;
					AptStringC name((const char *)body->arguments[i]);
					append(function->scope, 0, &name, value, 0, 1, 0);
				}
				reinterpret_cast<BfmeStackBB *>(this)->bfmePopN(argumentCount);
				scopes[scopeCount++] = callScope;
				callScope->AddRef();
				runStream(body->byteCode, function->scope, body->byteCodeSize);
				scopes[--scopeCount]->Release();
				while (stringCount > savedStringCount)
				{
					AptValue *value = strings[stringCount - 1];
					value->Release();
					--stringCount;
				}
				((AptValue *)frames[frameCount - 1])->Release();
				--frameCount;
				constantCount = savedConstantCount;
				constantPool = savedConstantPool;
				goto finished;
			}
			if (representation == 2)
			{
				Rva008A0F20Header *bound = (Rva008A0F20Header *)function->scope;
				AptFunctionBody *body = (AptFunctionBody *)function->body;
				int savedStringCount = stringCount;
				if (!bound->isDefined() ||
					(bound->isKind13() && (bound->state & 0xc0000) == 0) ||
					((bound->state & 0xc0000) == 0x80000))
					goto unusable;
				constantCount = body->constantCount;
				constantPool = body->constantPool;
				AptFrameState *frame = (AptFrameState *)function->runtime;
				if (frame == 0)
				{
					void *storage = Rva008C4890(sizeof(AptFrameState));
					frame = storage ? new(storage) AptFrameState : 0;
				}
				reinterpret_cast<BfmeThing937E *>(&frameCount)->bfmeGo937E(frame);
				++registerDepth;
				registers = registerBase + registerWidth * (registerDepth - 1);
				for (int r = 0; r < registerWidth; ++r)
					registers[r] = g_bfmeFallbackDB;
				int bindCount = body->argumentCount < argumentCount ? body->argumentCount : argumentCount;
				for (int i = 0; i < body->argumentCount; ++i)
				{
					AptValue *value = i < bindCount ? stack[stackCount - i - 1] : g_bfmeFallbackDB;
					void **formal = body->arguments + i * 2;
					if (formal[0])
					{
						int index = (int)formal[0];
						registers[index] = value;
						value->AddRef();
					}
					else
					{
						AptStringC name((const char *)formal[1]);
						append(function->scope, 0, &name, value, 0, 1, 0);
					}
				}
				reinterpret_cast<BfmeStackBB *>(this)->bfmePopN(argumentCount);
				scopes[scopeCount++] = callScope;
				callScope->AddRef();
				unsigned char flags = *((unsigned char *)body + 10);
				int nextRegister = 1;
				if (flags & 1) registers[nextRegister++] = findValue(function->scope, (const char *)0x01338710, 0);
				if (flags & 4) registers[nextRegister++] = g_bfmeFallbackDB;
				if (flags & 0x10) registers[nextRegister++] = makeValue(callScope, 0, (const char *)0x01338700, 1, 1, 0);
				if (flags & 0x40) registers[nextRegister++] = findValue(function->scope, g_bfmeRootName, 0);
				if (flags & 0x80) registers[nextRegister++] = findValue(function->scope, g_bfmeParentName, 0);
				if (*((unsigned char *)body + 11) & 1) registers[nextRegister] = g_bfmeThisValue;
				runStream(body->byteCode, function->scope, body->byteCodeSize);
				scopes[--scopeCount]->Release();
				while (stringCount > savedStringCount)
				{
					AptValue *value = strings[stringCount - 1];
					value->Release();
					--stringCount;
				}
				for (int i = 0; i < body->argumentCount; ++i)
				{
					int index = (int)body->arguments[i * 2];
					if (index && registers[index])
						releaseValue(registers[index]);
					if (index) registers[index] = g_bfmeFallbackDB;
				}
				for (int r = 0; r < registerWidth; ++r)
				{
					AptValue *value = registers[r];
					if (value && (value->flags & 0x0fff0000))
						releaseValue(value);
					registers[r] = g_bfmeFallbackDB;
				}
				if (--registerDepth == 0)
					registers = registerBase;
				else
					registers = registerBase + registerWidth * (registerDepth - 1);
				((AptValue *)frames[frameCount - 1])->Release();
				--frameCount;
				constantCount = savedConstantCount;
				constantPool = savedConstantPool;
				goto finished;
			}
			goto finished;
		}
	}

unusable:
	reinterpret_cast<BfmeStackBB *>(this)->bfmePopN(argumentCount);
	stack[stackCount++] = g_bfmeFallbackDB;
	if (!g_bfmeFallbackDB->isPermanent())
		g_bfmeFallbackDB->AddRef();

finished:
	if (abortValue != 0 && stackCount > oldStackCount - argumentCount)
		reinterpret_cast<BfmeStackBB *>(this)->bfmePopN(stackCount - oldStackCount + argumentCount);
}
