// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt opcode-table entry 0x2B: retail RVA 0x008CB3C0 (259 bytes).
//
// Boundary: the body ends in the virtual Release tail jump `jmp [edx+4]` at
// +0x100, followed by int3 padding at +0x103.
// Caller: the opcode table at VA 0x012D5A68 (see identity_evidence/
// 008CA3A0-boundary.md) holds VA 0x00CCB3C0 in entry 0x2B at VA 0x012D5B14;
// the dispatcher calls entries as cdecl (interpreter, context). The body
// reads only the interpreter: stack count at +0x0 and value array at +0x8,
// like the matched BitAnd/StoreRegister/0x66 handlers. It pops two values,
// pushes the top one when its tag/validity tests pass (tag 27 over tag 10
// asks top's virtual slot 18 about the under value's lookup of key slot 120)
// and otherwise pushes g_bfmeFallbackDB. The EA handler name is unproven, so
// the method keeps its address.
class BfmeTab1024 { public: int bfmeFind1024(int); };

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17();
	virtual bool slot18(int);

	bool isUndefined() const { return (m_valueBits >> 15 & 1) == 0; }
	bool GetMaxRefCountHit() const { return (m_valueBits >> 30 & 1) != 0; }
	unsigned int getType() const { return m_valueBits & 0x3f; }

	unsigned int m_valueBits;
	BfmeTab1024 m_08;
};

class AptActionInterpreter
{
public:
	struct LocalContextT;
	static void _FunctionRva008CB3C0(AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
// 0x01338480 is g_bfmeRouteKeys1282 (four-byte string slots); 0x01338660 is slot 120,
// the same key BfmeStringList0089CBA0Rva0089D4C0.cpp tests.
extern int g_bfmeRouteKeys1282[];

// ?_FunctionRva008CB3C0@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008CB3C0(AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *result = g_bfmeFallbackDB;
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];

	if (top->getType() == 27 && !top->isUndefined()
		&& under->getType() == 10 && !under->isUndefined())
	{
		int found = under->m_08.bfmeFind1024((int)&g_bfmeRouteKeys1282[120]);
		if (top->slot18(found))
		{
			result = top;
			top->AddRef();
		}
	}
	else if (!(top->getType() == 10 && !top->isUndefined())
		&& !(top->getType() == 27 && !top->isUndefined())
		&& top->getType() == under->getType())
	{
		result = top;
		top->AddRef();
	}

	for (int index = 1; index <= 2; ++index)
	{
		AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];

		if (!value->GetMaxRefCountHit())
			value->Release();
	}

	interpreter->m_stackTop -= 2;
	interpreter->m_stack[interpreter->m_stackTop++] = result;

	if (!result->GetMaxRefCountHit())
		result->AddRef();
	result->Release();
}
