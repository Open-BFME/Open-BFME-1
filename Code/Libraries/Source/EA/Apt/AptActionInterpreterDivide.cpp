// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: near-twin of Rva008C72D0LessThanZero.cpp's _FunctionRva008C72D0
// (0x008C72D0, 221 B) and AptActionInterpreterLessThan.cpp, retail
// 0x008C7060, 210 bytes. Same SWF-version-7 undefined-operand fast path
// reading g_bfmeFallbackDB, then both operands converted through bfmeF1239,
// but this opcode computes underValue / topValue and boxes the float result
// through the already-matched d_008a4cd0 (pinned _bfmeMakeF1239) rather than
// d_008996b0's bool box; a division-by-zero (topValue == BfmeZeroRange)
// falls back to the same g_bfmeFallbackDB sentinel reloaded fresh.
//
// IDENTITY: address-derived. Real opcode name not recovered (ActionScript
// divide); the callee set (Rva00892370Get x1, bfmeF1239 x2, bfmeMakeF1239 x1)
// matches the sibling near-twins.

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

	static void _FunctionRva008C7060(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
extern const float BfmeZeroRange;
unsigned int Rva00892370Get();
void __cdecl d_008a4cd0(void);

// ?d_008c7060@@YAXXZ
void AptActionInterpreter::_FunctionRva008C7060(
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

		if (topValue == BfmeZeroRange)
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
