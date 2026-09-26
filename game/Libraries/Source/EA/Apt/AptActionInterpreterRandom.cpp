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

	static void _FunctionAptActionRandom(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

unsigned int bfmeNext1221();

void AptActionInterpreter::_FunctionAptActionRandom(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *value = interpreter->m_stack[interpreter->m_stackTop - 1];
	int resultValue;

	if (value->isUndefined())
	{
		resultValue = 0;
	}
	else
	{
		int maximum = value->toInteger();
		resultValue = bfmeNext1221() % maximum;
	}

	AptValue *result = AptInteger::Create(resultValue);
	AptValue *oldValue = interpreter->m_stack[interpreter->m_stackTop - 1];

	if (!oldValue->GetMaxRefCountHit())
		oldValue->Release();

	interpreter->m_stackTop--;
	interpreter->m_stack[interpreter->m_stackTop++] = result;

	if (!result->GetMaxRefCountHit())
		result->AddRef();
}
