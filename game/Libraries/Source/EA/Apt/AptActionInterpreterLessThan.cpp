// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

	float toNumber();	// retail 0x008983D0, AptValue_toNumber.cpp

private:
	unsigned int m_valueBits;
};

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionAptActionLessThan(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
unsigned int AptGetSwfVersion();
void __cdecl d_008996b0(void);

void AptActionInterpreter::_FunctionAptActionLessThan(
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

		result = ((AptValue *(__cdecl *)(unsigned char))d_008996b0)(
			underValue < topValue);
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
