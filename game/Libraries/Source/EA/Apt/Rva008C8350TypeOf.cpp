// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt opcode 0x44 handler (Flash ActionTypeOf, slot 0x00ED5B78 of the table at 0x00ED5A68):
// replaces the top value with a new string value whose text names the value's type.

typedef int Bool;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isUndefined() const
	{
		return ((unsigned char)~(m_flags >> 15) & 1) != 0;
	}
	int getType() const
	{
		return m_flags & 0x3f;
	}
	__forceinline bool isType(int kind) const
	{
		return getType() == kind && !isUndefined();
	}
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

// Retail tests only AL after calling the landed Bool predicate, so the call reads it as bool.
typedef bool (Rva008A0F20Header::*Rva008A0F20BoolPredicate)() const;

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

struct BfmeStringData3AF0
{
	unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};

extern char *g_rva008C8350Builtin851C;
extern char *g_rva008C8350Builtin86F4;
extern unsigned char g_Va013385F8;
extern BfmeStringData3AF0 *g_stringBlock01338724;
extern char g_rva8D0D80CreateTag;
extern char *g_rva008C8350Builtin860C;
extern void *g_rva008B2EA0Base;
extern char *g_rva008C8350Builtin855C;

// ?rva008C8350StackBuiltin@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::rva008C8350StackBuiltin(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	Rva008B2EA0Node *result = rva008B2EA0Create();

	if ((top->m_flags & 0x8000) != 0)
	{
		if (top->isType(7) || top->isType(6))
			result->append(g_rva008C8350Builtin860C + 8);
		else if (top->isType(5))
			result->append(g_rva008C8350Builtin851C + 8);
		else if ((top->getType() == 1 || top->getType() == 0x2a) && !top->isUndefined())
			result->append(g_rva008C8350Builtin86F4 + 8);
		else if (top->isType(0x1b) || top->isType(0x16))
			result->append(*(char **)&g_rva8D0D80CreateTag + 8);
		else if (top->getType() >= 0x0c && top->getType() <= 0x13 && !top->isUndefined())
		{
			if (top->getType() == 0x0d || top->getType() == 0x12)
				result->append(*(char **)&g_Va013385F8 + 8);
			else if ((reinterpret_cast<Rva008A0F20Header *>(top)->*
				reinterpret_cast<Rva008A0F20BoolPredicate>(&Rva008A0F20Header::isKind13))())
				result->append(g_stringBlock01338724 + 1);
			else
				result->append(*(char **)&g_rva8D0D80CreateTag + 8);
		}
		else if (top->getType() == 3)
			result->append((char *)g_rva008B2EA0Base + 8);
		else if (top->isUndefined())
			result->append(g_stringBlock01338724 + 1);
		else if (top->getType() == 0x0a || top->getType() == 9)
			result->append(g_rva008C8350Builtin855C + 8);
	}
	else
		result->append(g_stringBlock01338724 + 1);

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
