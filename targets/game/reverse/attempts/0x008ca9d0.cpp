// ?_FunctionAptActionPush@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
// partial score=0.0968 date=2026-09-29
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// EA Apt ActionScript Push (opcode 0x96), retail 0x008CA9D0: slot 0x96 of
// the opcode table based at 0x00ED5A68 (see
// AptActionInterpreterStoreRegister.cpp), at 0x00ED5CC0.
//
// Apt pre-resolves a push into an aligned count and a pointer to the
// pushed values.  A value of type 8 names a constant-pool entry (+0x60) and
// one of type 4 names a register (+0x58, an empty register pushing the
// undefined value); anything else is pushed as it is.

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	unsigned int getType() const
	{
		return m_valueBits & 0x3f;
	}

	bool isUndefined() const
	{
		return (m_valueBits >> 15 & 1) == 0;
	}

	bool GetMaxRefCountHit() const
	{
		return (m_valueBits >> 30 & 1) != 0;
	}

	unsigned int m_valueBits;
	int m_index;
};

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
	};

	static void _FunctionAptActionPush(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
	char m_pad0C[0x4C];
	AptValue **m_registers58;
	char m_pad5C[4];
	AptValue **m_constants;
};

extern AptValue *gpUndefinedValue;

void AptActionInterpreter::_FunctionAptActionPush(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	const unsigned char *p = (const unsigned char *)(((unsigned int)context->m_pc + 3) & ~3u);
	context->m_pc = p + 8;
	for (int i = 0; i < *(const int *)p; i++)
	{
		AptValue *value = (*(AptValue ***)(p + 4))[i];
		if (value->getType() == 8 && !value->isUndefined())
		{
			value = interpreter->m_constants[value->m_index];
		}
		else if (value->getType() == 4 && !value->isUndefined())
		{
			value = interpreter->m_registers58[value->m_index];
			if (value == 0)
				value = gpUndefinedValue;
		}
		interpreter->m_stack[interpreter->m_stackTop++] = value;
		if (!value->GetMaxRefCountHit())
			value->AddRef();
	}
}
