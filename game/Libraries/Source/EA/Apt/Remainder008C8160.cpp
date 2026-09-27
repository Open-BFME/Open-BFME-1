// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The address-qualified handler at 0x008C8160 computes the numeric remainder.
// Extent: final ret at +0xDD; two INT3 bytes then independent EH prologue at 008C8240.
// Split the 491-byte scaffold at that witnessed boundary.

class AptValue
{
public:
	float toNumber();
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



class AptActionInterpreter
{
public:
	struct LocalContextT;

	static void _FunctionRva008C8160(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *g_bfmeFallbackDB;
unsigned int Rva00892370Get();
AptValue *Rva008A4EA0MakeFloat(float);
extern const float BfmeZeroRange;
extern "C" double fmod(double, double);
#pragma intrinsic(fmod)

// ?_FunctionRva008C8160@AptActionInterpreter@@SAXPAV1@PAULocalContextT@1@@Z
void AptActionInterpreter::_FunctionRva008C8160(
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
        float topValue = top->toNumber();
        if (topValue == BfmeZeroRange) result = g_bfmeFallbackDB;
        else {
            float underValue = under->toNumber();
            result = Rva008A4EA0MakeFloat((float)fmod(underValue, topValue));
        }
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
