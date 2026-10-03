// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: near-twin of Rva008C72D0LessThanZero.cpp's _FunctionRva008C72D0
// (0x008C72D0, 221 B) and AptActionInterpreterLessThan.cpp, retail
// 0x008C7060, 210 bytes. Same SWF-version-7 undefined-operand fast path
// reading g_bfmeFallbackDB, then both operands converted through AptValue::toNumber,
// but this opcode computes underValue / topValue and boxes the float result
// through the already-matched d_008a4cd0 (pinned _bfmeMakeF1239) rather than
// d_008996b0's bool box; a division-by-zero (topValue == g_rva01075350)
// falls back to the same g_bfmeFallbackDB sentinel reloaded fresh.
//
// IDENTITY: address-derived. Real opcode name not recovered (ActionScript
// divide); the callee set (AptGetSwfVersion x1, AptValue::toNumber x2,
// bfmeMakeF1239 x1)
// matches the sibling near-twins.

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

	static void _FunctionRva008C7060(
		AptActionInterpreter *interpreter, LocalContextT *context);
	static void _FunctionRva008C6FA0(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
extern const float g_rva01075350;
unsigned int AptGetSwfVersion();
void __cdecl d_008a4cd0(void);

// ?_FunctionRva008C7060@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008C7060(
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

		if (topValue == g_rva01075350)
			result = g_bfmeFallbackDB;
		else
			result = ((AptValue *(__cdecl *)(float))d_008a4cd0)(underValue / topValue);
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

// ?_FunctionRva008C6FA0@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008C6FA0(
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

		result = ((AptValue *(__cdecl *)(float))d_008a4cd0)(underValue * topValue);
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
