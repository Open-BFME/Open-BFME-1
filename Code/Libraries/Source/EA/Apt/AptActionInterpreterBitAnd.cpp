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

	int toInteger() const;

private:
	unsigned int m_valueBits;
};

class AptInteger : public AptValue
{
public:
	static AptInteger *Create(int value);
};

class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionAptActionBitAnd(
		AptActionInterpreter *interpreter, LocalContextT *context);
	static void _FunctionAptActionBitOr(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *gpUndefinedValue;
unsigned int AptGetSwfVersion();

void AptActionInterpreter::_FunctionAptActionBitAnd(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	AptValue *result;

	if (AptGetSwfVersion() == 7
		&& (top->isUndefined() || under->isUndefined())
		&& (result = gpUndefinedValue) != 0)
	{
		// SWF 7 preserves undefined instead of coercing it through integer arithmetic.
	}
	else
	{
		int topValue = top->toInteger();
		int underValue = under->toInteger();

		result = AptInteger::Create(underValue & topValue);
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

void AptActionInterpreter::_FunctionAptActionBitOr(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	AptValue *result;

	if (AptGetSwfVersion() == 7
		&& (top->isUndefined() || under->isUndefined())
		&& (result = gpUndefinedValue) != 0)
	{
		// SWF 7 preserves undefined instead of coercing it through integer arithmetic.
	}
	else
	{
		int topValue = top->toInteger();
		int underValue = under->toInteger();

		result = AptInteger::Create(underValue | topValue);
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
