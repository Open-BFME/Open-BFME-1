// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008C66A0 (129 bytes, RET at +0x7A and +0x80). Address-owned Apt
// callback: it reads the integer on the Apt stack top, and when that slot of
// the holder's 32-byte value-stack table is live, releases its +4 value,
// clears it, releases the whole stack and drops the live-slot count at
// holder+0x1234. Its registered name and semantic identity are unknown.

class AptValue
{
public:
	virtual void addRef();
	int toInteger() const;
	float toNumber();
	unsigned int kind() const { return m_valueBits & 0x3f; }
	bool isUndefined() const { return ((m_valueBits >> 15) & 1) == 0; }
	bool isScriptFunction() const { return kind() == 10 && !isUndefined(); }
	bool isNativeFunction() const { return kind() == 9 && !isUndefined(); }

private:
	unsigned int m_valueBits;
};

class Rva008A0FF0Value
{
public:
	virtual void slot00();
	virtual void release();
};

class Rva008A0FF0ValueStack
{
public:
	void releaseAll();

	void *m_value00;
	Rva008A0FF0Value *m_value04;
	int m_value08;
	int m_value0C;
	int m_value10;
	int m_count;
	int m_capacity;
	Rva008A0FF0Value **m_values;
};

struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
	AptValue *at(int i) const { return m_rva01338750[m_count - 1 - i]; }
};

extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
// retail 0x013377D8; its one definition is ?g_bfmeHolderBU@@3PAUBfmePickWorld1284@@A
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

AptValue *__cdecl dup_008c66a0()
{
	// Native 0x008C66A0 loads VA 0x01338750: the existing stack's +8 field.
	// One volatile pointer read retains VC7.1's native array-before-count order.
	AptValue **values = *reinterpret_cast<AptValue ** volatile *>(&Rva008AE770TheStack.m_rva01338750);
	AptValue *arg = values[Rva008AE770TheStack.m_count - 1];
	if (!arg->isUndefined())
	{
		int index = arg->toInteger();
		char *holder = ((char *)g_bfmeHolderBU);
		if (((Rva008A0FF0ValueStack *)*(char **)(holder + 0x1230))[index].m_value00)
		{
			((Rva008A0FF0ValueStack *)*(char **)(holder + 0x1230))[index].m_value04->release();
			((Rva008A0FF0ValueStack *)*(char **)(((char *)g_bfmeHolderBU) + 0x1230))[index].m_value00 = 0;
			((Rva008A0FF0ValueStack *)*(char **)(((char *)g_bfmeHolderBU) + 0x1230))[index].releaseAll();
			--*(int *)(((char *)g_bfmeHolderBU) + 0x1234);
		}
	}
	return g_bfmeFallbackDB;
}

// Retail 0x008C64C0 (470 bytes): the paired registration callback (Apt
// setInterval). Open BFME 2 59e3f8f8 AptActionInterpreterConstantHandlers.cpp
// callback006FEFF0 supplies the shape: claim the first free 32-byte timer,
// resolve object+method callbacks through findChild (bfmeTest1220), copy the
// remaining arguments, return AptInteger::Create(slot).
class AptInteger
{
public:
	static AptInteger *Create(int value);
};

class BfmeNode1220
{
public:
	int bfmeTest1220(int *name, int context);
};

struct AptIntervalParams
{
	int m_count;
	int m_capacity;
	AptValue **m_items;
	void push(AptValue *value)
	{
		m_items[m_count] = value;
		++m_count;
		value->addRef();
	}
};

struct AptIntervalTimer
{
	int m_used;
	AptValue *m_callback;
	float m_interval;
	float m_countdown;
	AptValue *m_context;
	AptIntervalParams m_params;
};

struct AptIntervalPool
{
	char m_pad0000[0x1230];
	AptIntervalTimer *m_timers;
	int m_activeTimers;
	char m_pad1238[0x12a4 - 0x1238];
	int m_maxTimers;
};
#define POOL ((AptIntervalPool *)g_bfmeHolderBU)

AptValue *Rva008C64C0(AptValue *, int nParams)
{
	AptValue *callback = Rva008AE770TheStack.at(0);
	AptValue *delay = Rva008AE770TheStack.at(1);
	int firstParam = 2;
	if (callback->isUndefined())
		return (AptValue *)AptInteger::Create(0);
	int i;
	for (i = 0; i < POOL->m_maxTimers; ++i)
	{
		if (!POOL->m_timers[i].m_used)
		{
			++POOL->m_activeTimers;
			POOL->m_timers[i].m_used = 1;
			POOL->m_timers[i].m_context = g_bfmeFallbackDB;
			if (!callback->isScriptFunction() && !callback->isNativeFunction())
			{
				AptValue *context = callback;
				delay = Rva008AE770TheStack.at(2);
				callback = (AptValue *)((BfmeNode1220 *)callback)->bfmeTest1220((int *)((char *)Rva008AE770TheStack.at(1) + 8), 0);
				firstParam = 3;
				POOL->m_timers[i].m_context = context;
			}
			POOL->m_timers[i].m_callback = callback;
			POOL->m_timers[i].m_callback->addRef();
			POOL->m_timers[i].m_interval = delay->toNumber();
			POOL->m_timers[i].m_countdown = POOL->m_timers[i].m_interval;
			if (nParams > firstParam)
			{
				int remaining = nParams - firstParam;
				for (int j = 0; j < remaining; ++j)
				{
					AptValue *param = Rva008AE770TheStack.at(j + firstParam);
					POOL->m_timers[i].m_params.push(param);
				}
			}
			break;
		}
	}
	return (AptValue *)AptInteger::Create(i);
}
