// ?d_008cced0@@YAXXZ
// partial score=0.7733333333333333 date=2026-09-22
// ?run@Rva008CCED0BytecodeRunner@@QAEPAEPAX0H@Z
// Retail 008CCED0: thiscall; 3 stack dwords; ret 0C; EAX cursor.
// Analyst docs/analysis/0x008cf740.md plus full entry-to-retail-ret disassembly.
// Context: +00 cursor +04 receiver +08 held value +0C stop cursor +10 lookup +14 stop byte.
// makeValue -> 008CC940 thiscall six args ret18 pointer result;
// popValues -> 008A0CF0 thiscall count ret4 (including zero on bounded path);
// Rva8CCED0IdleHook::run -> 008A30C0 thiscall zero args.
// Globals: opcode table VA012D5A68; marker holder VA01338700;
// fallback pointer VA013379BC; idle hook pointer VA01337810.
// Resume: first divergence +A5 branch placement; 373/375B 81 positional differences.
// The volatile parameter/local preserve retail reloads and the reused argument stack slot.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// bounded Apt bytecode execution helper, retail 0x008CCED0 (375 bytes).

class Rva008CCED0BytecodeRunnerValue
{
public:
	virtual void addRef();
	virtual void release();
	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned m_flags;
};

class Rva008CCED0BytecodeRunner;
struct Rva008CCED0BytecodeRunnerExecContext
{
	unsigned char *m_cursor;
	int m_unknown04;
	Rva008CCED0BytecodeRunnerValue *m_heldValue;
	unsigned char *m_end;
	Rva008CCED0BytecodeRunnerValue *m_created;
	bool m_stopped;
};

typedef void (__cdecl *Rva008CCED0BytecodeRunnerOpcode)(Rva008CCED0BytecodeRunner *, Rva008CCED0BytecodeRunnerExecContext *);

extern Rva008CCED0BytecodeRunnerOpcode g_bfmeR1226Opcodes[];
extern int g_rva8CCED0RouteMarker;
extern Rva008CCED0BytecodeRunnerValue *g_bfmeFallbackDB;

class Rva8CCED0IdleHook
{
public:
	int m_unused;
	int m_enabled;
	void run();
};

extern Rva8CCED0IdleHook *g_rva8CD130IdleHook;

class Rva008CCED0BytecodeRunner
{
public:
	unsigned char *run(void *code, void *value, int limit);
	Rva008CCED0BytecodeRunnerValue *makeValue(Rva008CCED0BytecodeRunnerValue *value, int zero, void *marker,
		int one1, int one2, int zero2);
	void popValues(int count);

	void pushValue(Rva008CCED0BytecodeRunnerValue *value)
	{
		m_stack[m_count++] = value;
		if (!value->maxRefCountHit())
			value->addRef();
	}

	int m_count;
	int m_unused;
	Rva008CCED0BytecodeRunnerValue **m_stack;
	char m_gap0c[0x24];
	int m_ownedCount;
	int m_ownedCapacity;
	Rva008CCED0BytecodeRunnerValue **m_ownedValues;
	char m_gap3c[0x40];
	int m_stop;
	int m_savedStackBase;
};

unsigned char *Rva008CCED0BytecodeRunner::run(void *code, void *valueArgument, volatile int limit)
{
	unsigned char *start = (unsigned char *)code;
	if (limit == -1)
	{
		m_ownedValues[m_ownedCount++] = (Rva008CCED0BytecodeRunnerValue *)valueArgument;
		((Rva008CCED0BytecodeRunnerValue *)valueArgument)->addRef();
	}
	Rva008CCED0BytecodeRunnerValue *value = (Rva008CCED0BytecodeRunnerValue *)valueArgument;

	int zero = 0;
	Rva008CCED0BytecodeRunnerExecContext execute;
	execute.m_unknown04 = (int)value;
	execute.m_heldValue = (Rva008CCED0BytecodeRunnerValue *)zero;
	execute.m_cursor = start;
	execute.m_end = (unsigned char *)zero;
	execute.m_created = makeValue(value, zero, &g_rva8CCED0RouteMarker, 1, 1, zero);
	execute.m_stopped = (bool)zero;
	volatile int oldStackBase = m_savedStackBase;
	int bound;
	m_savedStackBase = m_count;
	for (;;)
	{
		if (m_stop != zero)
		{
			bound = limit;
			break;
		}
		if (execute.m_end != (unsigned char *)zero && execute.m_cursor == execute.m_end)
		{
			execute.m_heldValue->release();
			execute.m_heldValue = (Rva008CCED0BytecodeRunnerValue *)zero;
			execute.m_end = (unsigned char *)zero;
		}

		unsigned opcode = *execute.m_cursor++;
		bound = limit;
		if (execute.m_stopped)
			break;
		if (bound >= zero && execute.m_cursor - start > bound)
		{
			pushValue(g_bfmeFallbackDB);
			break;
		}
		if (opcode == (unsigned)zero)
		{
			if (bound >= zero)
				pushValue(g_bfmeFallbackDB);
			break;
		}
		g_bfmeR1226Opcodes[opcode](this, &execute);
	}
	int count = m_count;
	if (bound >= zero && count > m_savedStackBase)
		popValues(count - m_savedStackBase - 1);
	else if (count > m_savedStackBase)
		popValues(count - m_savedStackBase);

finishCleanup:
	m_savedStackBase = oldStackBase;

	if (bound == -1)
	{
		m_ownedValues[m_ownedCount - 1]->release();
		--m_ownedCount;
	}

	if ((m_count == zero || (m_count == 1 && m_stack[m_count - 1] == g_bfmeFallbackDB)) &&
		g_rva8CD130IdleHook->m_enabled != zero)
		g_rva8CD130IdleHook->run();

	return execute.m_cursor;
}
