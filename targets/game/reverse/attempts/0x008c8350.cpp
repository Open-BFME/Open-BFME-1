// ?d_008c8350@@YAXXZ
// partial score=0.35 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived Apt stack handler reconstructed from retail 0x008C8350.

typedef int Bool;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool GetMaxRefCountHit() const
	{
		return (m_flags >> 30 & 1) != 0;
	}

	unsigned m_flags;
};

class Rva008B2EA0Node
{
public:
	void append(void *value);
};

Rva008B2EA0Node *rva008B2EA0Create();

class Rva008A0F20Header
{
public:
	int m_unreconstructed_00;
	unsigned m_flags;

	Bool isKind13() const;
};

class AptActionInterpreter
{
public:
	struct LocalContextT;
	static void rva008C8350StackBuiltin(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern char *g_rva008C8350Builtin851C;
extern char *g_rva008C8350Builtin86F4;
extern char *g_rva008C8350Builtin85F8;
extern char *g_rva008C8350Builtin8724;
extern char *g_rva008C8350Builtin8610;
extern char *g_rva008C8350Builtin860C;
extern char *g_rva008C8350Builtin8608;
extern char *g_rva008C8350Builtin855C;

void AptActionInterpreter::rva008C8350StackBuiltin(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	Rva008B2EA0Node *result = 0;
	AptValue *top;
	unsigned flags;
	int type;
	void *value;

	top = interpreter->m_stack[interpreter->m_stackTop - 1];
	result = rva008B2EA0Create();
	flags = top->m_flags;

	if ((flags & 0x8000) != 0)
	{
		type = flags & 0x3f;

	if (type != 7)
		goto check6;
	if (!((unsigned char)~(flags >> 15) & 1))
		goto use860C;

check6:
	if (type != 6)
		goto check5;
	if (!((unsigned char)~(flags >> 15) & 1))
		goto use860C;

check5:
	if (type != 5)
		goto type1;
	if (((unsigned char)~(flags >> 15) & 1) != 0)
		goto type1;
	value = g_rva008C8350Builtin851C + 8;
	goto append;

type1:
	if (type == 1)
		goto type1or2A;
	if (type != 0x2a)
		goto type1B;

type1or2A:
	if (((unsigned char)~(flags >> 15) & 1) != 0)
		goto type1B;
	value = g_rva008C8350Builtin86F4 + 8;
	goto append;

type1B:
	if (type == 0x1b)
	{
		if (!((unsigned char)~(flags >> 15) & 1))
			goto use8610;
	}

	if (type == 0x16)
	{
		if (!((unsigned char)~(flags >> 15) & 1))
			goto use8610;
	}

	if (type < 0x0c || type > 0x13)
		goto general;
	if (((unsigned char)~(flags >> 15) & 1) != 0)
		goto general;

	if (type == 0x0d || type == 0x12)
	{
		value = g_rva008C8350Builtin85F8;
		goto append;
	}

	if (reinterpret_cast<Rva008A0F20Header *>(top)->isKind13())
		value = g_rva008C8350Builtin8724 + 8;
	else
		value = g_rva008C8350Builtin8610 + 8;
	goto append;

general:
	if (type == 3)
	{
		value = g_rva008C8350Builtin8608 + 8;
		goto append;
	}

	if (((unsigned char)~(flags >> 15) & 1) == 0)
		goto type9orA;
	value = g_rva008C8350Builtin8724 + 8;
	goto append;

type9orA:
	if (type == 0x0a || type == 9)
	{
		value = g_rva008C8350Builtin855C;
		goto append;
	}
	goto use860C;

use8610:
	value = g_rva008C8350Builtin8610 + 8;
	goto append;

use860C:
	value = g_rva008C8350Builtin860C + 8;
	goto append;
	}
	else
	{
		value = g_rva008C8350Builtin8724 + 8;
		goto append;
	}

append:
	result->append(value);

	AptValue *old = interpreter->m_stack[interpreter->m_stackTop - 1];
	if (!old->GetMaxRefCountHit())
		old->Release();

	interpreter->m_stackTop--;
	interpreter->m_stack[interpreter->m_stackTop++] =
		reinterpret_cast<AptValue *>(result);

	AptValue *resultValue = reinterpret_cast<AptValue *>(result);
	if (!resultValue->GetMaxRefCountHit())
		resultValue->AddRef();
}
