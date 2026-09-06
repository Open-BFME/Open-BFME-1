// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: near-twin of AptActionInterpreter::_FunctionAptActionLessThan
// (0x008C7210, AptActionInterpreterLessThan.cpp). Same shape (SWF-version-7
// undefined-operand fast path, then the two operands converted through
// bfmeF1239, then a boolean packed through d_008996b0, then the same
// pop-two-refs/push-result stack tail), but this sibling opcode's fast-path
// fallback reads a different global (g_bfmeFallbackDB, not gpUndefinedValue)
// and its "compare" is not `underValue < topValue`: both operands are
// tested for exact equality against BfmeZeroRange (0.0f), consistent with
// the pinned name's "zero constant" origin -- an is-both-zero test rather
// than a less-than.
//
// IDENTITY: address-derived. Real opcode name not recovered; the callee set
// (Rva00892370Get x1, bfmeF1239 x2, d_008996b0 x1) matches the twin exactly.

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isUndefined() const
	{
		return (m_valueBits >> 15 & 1) == 0;
	}

	bool GetMaxRefCountHit() const
	{
		return (m_valueBits >> 30 & 1) != 0;
	}

private:
	unsigned int m_valueBits;
};

class BfmeE1239 : public AptValue
{
public:
	float bfmeF1239();
};

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionRva008C72D0(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
extern const float BfmeZeroRange;
unsigned int Rva00892370Get();
void __cdecl d_008996b0(void);

// ?d_008c72d0@@YAXXZ
void AptActionInterpreter::_FunctionRva008C72D0(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	AptValue *result;

	if (Rva00892370Get() == 7
		&& (top->isUndefined() || under->isUndefined())
		&& (result = g_bfmeFallbackDB) != 0)
	{
	}
	else
	{
		float topValue = ((BfmeE1239 *)top)->bfmeF1239();
		float underValue = ((BfmeE1239 *)under)->bfmeF1239();
		int flag;

		if (topValue != BfmeZeroRange && underValue != BfmeZeroRange)
			flag = 1;
		else
			flag = 0;

		result = ((AptValue *(__cdecl *)(unsigned char))d_008996b0)(flag);
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
}
