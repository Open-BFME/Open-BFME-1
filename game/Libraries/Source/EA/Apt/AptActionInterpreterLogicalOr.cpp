// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: near-twin of Rva008C72D0LessThanZero.cpp's _FunctionRva008C72D0
// (0x008C72D0, 221 B) and AptActionInterpreterLessThan.cpp. Same shape (SWF
// version 7 undefined-operand fast path reading g_bfmeFallbackDB, then both
// operands converted through AptValue::toNumber, then a boolean packed through
// d_008996b0, then the same pop-two-refs/push-result stack tail), but this
// sibling opcode is an is-either-nonzero test (topValue != 0 || underValue
// != 0) rather than the 0x008C72D0 twin's is-both-nonzero test.
//
// IDENTITY: address-derived. Real opcode name not recovered; the callee set
// (AptGetSwfVersion x1, AptValue::toNumber x2, d_008996b0 x1) matches both twins.

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	float toNumber();

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

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionRva008C73B0(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
extern const float BfmeZeroRange;
unsigned int AptGetSwfVersion();
void __cdecl d_008996b0(void);

// ?_FunctionRva008C73B0@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008C73B0(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	AptValue *result;

	if (AptGetSwfVersion() == 7
		&& (top->isUndefined() || under->isUndefined())
		&& (result = g_bfmeFallbackDB) != 0)
	{
	}
	else
	{
		float topValue = top->toNumber();
		float underValue = under->toNumber();
		int flag;

		if (topValue != BfmeZeroRange || underValue != BfmeZeroRange)
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
