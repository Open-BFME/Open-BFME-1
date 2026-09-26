// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The slot-3 Apt action body at 0x008C6E20 adds the top two numeric values.
// The retail callee set and the shared stack layout match the converted
// divide body, while the Apt handler slot and address identify this body.

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

	static void _FunctionRva008C6E20(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
unsigned int Rva00892370Get();
void __cdecl d_008a4cd0(void);

// ?_FunctionRva008C6E20@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008C6E20(
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

		result = ((AptValue *(__cdecl *)(float))d_008a4cd0)(underValue + topValue);
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
