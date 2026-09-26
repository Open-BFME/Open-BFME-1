// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

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

	static void _FunctionAptActionSwap(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

void AptActionInterpreter::_FunctionAptActionSwap(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];

	top->AddRef();
	under->AddRef();

	for (int index = 1; index <= 2; ++index)
	{
		AptValue *value = interpreter->m_stack[interpreter->m_stackTop - index];

		if (!value->GetMaxRefCountHit())
			value->Release();
	}

	interpreter->m_stackTop -= 2;
	interpreter->m_stack[interpreter->m_stackTop++] = top;

	if (!top->GetMaxRefCountHit())
		top->AddRef();

	interpreter->m_stack[interpreter->m_stackTop++] = under;

	if (!under->GetMaxRefCountHit())
		under->AddRef();

	top->Release();
	under->Release();
}
