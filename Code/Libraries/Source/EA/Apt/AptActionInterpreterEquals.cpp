// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <math.h>

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

	static void _FunctionAptActionEquals(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

extern AptValue *gpUndefinedValue;
unsigned int AptGetSwfVersion();
extern double g_bfmeFactorBW;
void __cdecl d_008996b0(void);

void AptActionInterpreter::_FunctionAptActionEquals(
	AptActionInterpreter *interpreter, LocalContextT *)
{
	AptValue *top = interpreter->m_stack[interpreter->m_stackTop - 1];
	AptValue *under = interpreter->m_stack[interpreter->m_stackTop - 2];
	AptValue *result;

	if (AptGetSwfVersion() == 7
		&& (top->isUndefined() || under->isUndefined())
		&& (result = gpUndefinedValue) != 0)
	{
	}
	else
	{
		float topValue = ((BfmeE1239 *)top)->bfmeF1239();
		float underValue = ((BfmeE1239 *)under)->bfmeF1239();
		float difference = topValue - underValue;

		difference = (float)fabs(difference);

		result = ((AptValue *(__cdecl *)(unsigned char))d_008996b0)(
			difference < g_bfmeFactorBW);
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
