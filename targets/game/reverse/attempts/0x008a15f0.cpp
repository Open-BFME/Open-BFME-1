// ?d_008a15f0@@YAXXZ
// partial score=0.351 date=2026-09-28
// ?tickIntervalTimers@Rva008A15F0Owner@@QAEXH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Apt setInterval timers: every active 32-byte timer record at +0x1230 counts
// down by the elapsed time; an expired timer calls its script function (kind 9)
// or the method of its object (kind 10) through the interpreter state at
// 0x01338748, then re-arms by its period.  An object timer whose method is
// gone is released and cleared.  The literal the interpreter check receives
// is "tickIntervalTimers" (BFME2 labels the same body
// AptAnimationPoolData::tickIntervalTimers); the BFME1 owner class is not
// proven, so it keeps the address token.  Value, stack and interpreter
// models follow the matched Rva008A1940QueueFlush.cpp (including its volatile
// flags word, which reproduces retail's reload for the second kind test).
// The fild/fsubr/fstp countdown comes from a float local, no inline asm.
// Residue: retail keeps function in ebp and timer (then the arg loop counter)
// in ebx and spills the method; ours keeps timer in ebp and spills function.

class AptValue
{
public:
	virtual void retain();
	virtual void release();

	volatile unsigned m_flags;
	char gap08[0x20];
	AptValue *m_indirectValue;
	char gap2c[4];
	void *m_field30;

	bool permanent() const { return ((m_flags >> 30) & 1) != 0; }
	bool invalid() const { return ((unsigned char)~(m_flags >> 15) & 1) != 0; }
	bool isKind(unsigned kind) const
	{
		unsigned f = m_flags;
		return (f & 0x3f) == kind && ((unsigned char)~(f >> 15) & 1) == 0;
	}
};

struct Rva008A15F0Stack
{
	int count, unused;
	AptValue **values;

	__forceinline void push(AptValue *v)
	{
		values[count++] = v;
		if (!v->permanent())
			v->retain();
	}
	AptValue *top() { return values[count - 1]; }
	void pop()
	{
		AptValue *v = top();
		if (!v->permanent())
			v->release();
		--count;
	}
};

struct Rva008A1940Interpreter
{
	Rva008A15F0Stack primary;
};
extern Rva008A1940Interpreter Rva01338748State;

struct Rva008A1940Holder
{
	char gap00[0x12a4];
	int timerCapacity;
};
extern Rva008A1940Holder *g_bfmeHolderBU;

extern AptValue *g_bfmeFallbackDB;

class Rva008CF740Value;
class Rva008CF740 { public: void run(Rva008CF740Value *, Rva008CF740Value *, int); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
class BfmeA1232 { public: void bfmePop1232(int); };
class Rva008A0F20Header { public: int isKind13() const; };
class Rva008A0FF0ValueStack { public: void releaseAll(); };

struct Rva008A15F0Timer
{
	AptValue *m_active;
	AptValue *m_function;
	float m_period;
	float m_remaining;
	AptValue *m_receiver;
	int m_argumentCount;
	int m_capacity;
	AptValue **m_arguments;
};

class Rva008A15F0Owner
{
public:
	void tickIntervalTimers(int elapsed);

	char gap0000[0x1230];
	Rva008A15F0Timer *m_records;
	int m_count;
};

void Rva008A15F0Owner::tickIntervalTimers(int elapsed)
{
	int left = m_count;
	for (int i = 0; i < g_bfmeHolderBU->timerCapacity; ++i)
	{
		Rva008A15F0Timer *timer = &m_records[i];
		if (!timer->m_active)
			continue;

		float step = (float)elapsed;
		timer->m_remaining = timer->m_remaining - step;
		timer = &m_records[i];
		if (timer->m_remaining < 0.0f)
		{
			AptValue *function = timer->m_function;
			if (function->isKind(9))
			{
				int count = timer->m_argumentCount;
				if (count > 0)
				{
					for (int j = 0; j < m_records[i].m_argumentCount; ++j)
						Rva01338748State.primary.push(
							m_records[i].m_arguments[m_records[i].m_argumentCount - j - 1]);
					((Rva008CF740 *)&Rva01338748State)->run(
						(Rva008CF740Value *)m_records[i].m_receiver,
						(Rva008CF740Value *)function, m_records[i].m_argumentCount);
				}
				else
					((Rva008CF740 *)&Rva01338748State)->run(
						(Rva008CF740Value *)timer->m_receiver,
						(Rva008CF740Value *)function, -1);
				Rva01338748State.primary.pop();
				m_records[i].m_remaining = m_records[i].m_period + m_records[i].m_remaining;
			}
			else if (function->isKind(10))
			{
				AptValue *method;
				if (function->m_field30 && !(method = function->m_indirectValue)->invalid() &&
					!((Rva008A0F20Header *)method)->isKind13())
				{
					int count = timer->m_argumentCount;
					if (count > 0)
					{
						for (int j = 0; j < m_records[i].m_argumentCount; ++j)
							Rva01338748State.primary.push(
								m_records[i].m_arguments[m_records[i].m_argumentCount - j - 1]);
						AptValue *receiver = m_records[i].m_receiver;
						if (receiver == g_bfmeFallbackDB)
							receiver = function->m_indirectValue;
						((Rva008CF740 *)&Rva01338748State)->run(
							(Rva008CF740Value *)receiver,
							(Rva008CF740Value *)function, m_records[i].m_argumentCount);
					}
					else
					{
						AptValue *receiver = timer->m_receiver;
						if (receiver == g_bfmeFallbackDB)
							receiver = method;
						((Rva008CF740 *)&Rva01338748State)->run(
							(Rva008CF740Value *)receiver,
							(Rva008CF740Value *)function, 0);
					}
					((BfmeR1226 *)&Rva01338748State)->bfmeLine1226("tickIntervalTimers");
					((BfmeA1232 *)&Rva01338748State)->bfmePop1232(Rva01338748State.primary.count);
					m_records[i].m_remaining = m_records[i].m_period + m_records[i].m_remaining;
				}
				else
				{
					timer->m_function->release();
					((Rva008A0FF0ValueStack *)&m_records[i])->releaseAll();
					m_records[i].m_active = 0;
					--m_count;
				}
			}
		}
		if (--left == 0)
			return;
	}
}
