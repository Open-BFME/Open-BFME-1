// ?tickIntervalTimers@Rva008A15F0Owner@@QAEXH@Z
// partial score=0.19498607242339833 date=2026-09-24
// ?tickIntervalTimers@Rva008A15F0Owner@@QAEXH@Z
// partial candidate for retail 0x008A15F0, 718 bytes.
// The receiver and record offsets are read directly in retail: owner records/count
// at +0x1230/+0x1234; record stride 0x20; script stack ABI from the 0x008CF740
// hub pack. The literal passed to bfmeLine1226 is "tickIntervalTimers"; the
// address-derived owner is deliberate because no class identity is proved.

typedef unsigned char UnsignedByte;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool GetMaxRefCountHit() const
	{
		return (m_flags >> 30) & 1;
	}
	bool isKind9() const
	{
		return (m_flags & 0x3f) == 9 && !((UnsignedByte)~(m_flags >> 15) & 1);
	}
	bool isKind10() const
	{
		return (m_flags & 0x3f) == 10 && !((UnsignedByte)~(m_flags >> 15) & 1);
	}
	bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}

	unsigned m_flags;
	unsigned m_value08;
	char m_gap0C[0x1c];
	AptValue *m_indirectValue;
	char m_gap2C[4];
	void *m_field30;
};

struct Rva008A15F0Timer
{
	AptValue *m_active;
	AptValue *m_function;
	float m_period;
	volatile float m_remaining;
	AptValue *m_receiver;
	int m_argumentCount;
	int m_capacity;
	AptValue **m_arguments;
};
extern AptValue **g_bfmeArr1233;

class Rva008AE770Stack
{
public:
	int count;
	int unused;
	AptValue **values;

	__forceinline void push(AptValue *value)
	{
		g_bfmeArr1233[count++] = value;
		if (!value->GetMaxRefCountHit())
			value->AddRef();
	}
	__forceinline void pop()
	{
		AptValue *value = g_bfmeArr1233[count - 1];
		if (!value->GetMaxRefCountHit())
			value->Release();
		--count;
	}
};

class Rva008CF740Value;
class Rva008CF740
{
public:
	void run(Rva008CF740Value *receiver, Rva008CF740Value *function, int count);
};

class BfmeA1232
{
public:
	void bfmePop1232(int count);
};

class BfmeR1226
{
public:
	void bfmeLine1226(char *name);
};

class Rva008A0F20Header
{
public:
	int m_unused00;
	unsigned m_flags04;
	int isKind13() const;
};

class Rva008A0FF0ValueStack
{
public:
	void releaseAll();
private:
	int m_unused00;
	int m_unused04;
	int m_unused08;
	int m_unused0C;
	int m_unused10;
	int m_count;
	int m_capacity;
	AptValue **m_values;
};

class Rva008A15F0Owner
{
public:
	char m_gap0000[0x1230];
	Rva008A15F0Timer * volatile m_records;
	__forceinline Rva008A15F0Timer *timerAt(int offset)
	{
		return (Rva008A15F0Timer *)((char *)m_records + offset);
	}
	int m_count;
	void tickIntervalTimers(int elapsed);
};

extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
extern char *Rva008A5380Holder;
extern const float BfmeZeroRange;

void Rva008A15F0Owner::tickIntervalTimers(int elapsed)
{
	int remaining = m_count;
	int offset = 0;
	int index = 0;
	if (*(int *)(Rva008A5380Holder + 0x12a4) > 0)
	{
		do
		{
			Rva008A15F0Timer *timer = timerAt(offset);
			if (timer->m_active)
			{
				__asm {
					mov eax, timer
					fild elapsed
					fsubr dword ptr [eax + 0x0c]
					fstp dword ptr [eax + 0x0c]
				}
				if (timer->m_remaining < BfmeZeroRange)
				{
					AptValue *function = timer->m_function;
					if (function->isKind9())
					{
						int count = timer->m_argumentCount;
						if (count > 0)
						{
							for (int i = 0; i < count; ++i)
								Rva008AE770TheStack.push(
									timerAt(offset)->m_arguments[count - i - 1]);
						}
						else
							count = -1;

						((Rva008CF740 *)&Rva008AE770TheStack)->run(
							(Rva008CF740Value *)timerAt(offset)->m_receiver,
							(Rva008CF740Value *)timerAt(offset)->m_function, count);
						Rva008AE770TheStack.pop();
						Rva008A15F0Timer *updated = timerAt(offset);
						updated->m_remaining = updated->m_period + updated->m_remaining;
					}
					else if (function->isKind10())
					{
						if (function->m_field30 &&
							!function->m_indirectValue->isUndefined() &&
							!((Rva008A0F20Header *)function->m_indirectValue)->isKind13())
						{
							int count = timerAt(offset)->m_argumentCount;
							if (count > 0)
							{
								for (int i = 0; i < count; ++i)
									Rva008AE770TheStack.push(
										timerAt(offset)->m_arguments[count - i - 1]);
							}

							AptValue *receiver = timerAt(offset)->m_receiver;
							if (receiver == g_bfmeFallbackDB)
								receiver = timerAt(offset)->m_function->m_indirectValue;
							int runCount;
							if (count > 0)
								runCount = count;
							else
								runCount = 0;
							((Rva008CF740 *)&Rva008AE770TheStack)->run(
								(Rva008CF740Value *)receiver,
								(Rva008CF740Value *)timerAt(offset)->m_function, runCount);
							((BfmeR1226 *)&Rva008AE770TheStack)->bfmeLine1226(
								"tickIntervalTimers");
							((BfmeA1232 *)&Rva008AE770TheStack)->bfmePop1232(
								Rva008AE770TheStack.count);
							Rva008A15F0Timer *updated = timerAt(offset);
							updated->m_remaining = updated->m_period + updated->m_remaining;
						}
						else
						{
							timerAt(offset)->m_function->Release();
							((Rva008A0FF0ValueStack *)timerAt(offset))->releaseAll();
							timerAt(offset)->m_active = 0;
							--m_count;
						}
					}
				}
				--remaining;
				if (!remaining)
					return;
			}
			++index;
			offset += 0x20;
		} while (index < *(int *)(Rva008A5380Holder + 0x12a4));
	}
}
