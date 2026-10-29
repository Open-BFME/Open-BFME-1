// ?run@Rva008CCED0BytecodeRunner@@QAEPAEPAX0H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Bytecode runner with a local execution context and balanced value stacks.

class Rva008CCED0BytecodeRunnerValue
{
public:
	virtual void addRef();
	virtual void release();
	// ?maxRefCountHit@Rva008CCED0BytecodeRunnerValue@@QBE_NXZ absent-from-retail
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

#define g_bfmeR1226Opcodes g_Va012D5A68
#define g_rva8CCED0RouteMarker g_Va01338700
extern Rva008CCED0BytecodeRunnerOpcode g_bfmeR1226Opcodes[];
extern int g_rva8CCED0RouteMarker;
class AptValue;
extern AptValue *g_bfmeFallbackDB;

class Rva8CD130IdleHook
{
public:
	void run();
};

class Rva8CCED0IdleHook
{
public:
	int m_unused;
	int m_enabled;
	// ?run@Rva8CCED0IdleHook@@QAEXXZ absent-from-retail
	void run() { ((Rva8CD130IdleHook *)this)->run(); }
};

// Retail 0x01337810 is ?g_rva01337810GcRoots@@3PAURva00899560Pool@@A (data_rows.csv,
// Apt/Apt.cpp); g_rva8CD130IdleHook was only a pin.
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
#define g_rva8CD130IdleHook ( *(Rva8CD130IdleHook **)&g_rva01337810GcRoots )

class Rva00899770;
class BfmeStrVKI;
class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
};

class BfmeA1232
{
public:
	void bfmePop1232(int count);
};

class Rva008CCED0BytecodeRunner
{
public:
	unsigned char *run(void *code, void *value, int limit);
	// ?makeValue@Rva008CCED0BytecodeRunner@@QAEPAVRva008CCED0BytecodeRunnerValue@@PAV2@HPAXHHH@Z absent-from-retail
	Rva008CCED0BytecodeRunnerValue *makeValue(Rva008CCED0BytecodeRunnerValue *value, int zero, void *marker, int one1, int one2, int zero2)
	{
		return (Rva008CCED0BytecodeRunnerValue *)((Rva008AE770Stack *)this)->createString(value, zero, (BfmeStrVKI *)marker, one1, one2, zero2);
	}
	// ?popValues@Rva008CCED0BytecodeRunner@@QAEXH@Z absent-from-retail
	void popValues(int count) { ((BfmeA1232 *)this)->bfmePop1232(count); }

	// ?pushValue@Rva008CCED0BytecodeRunner@@QAEXPAVRva008CCED0BytecodeRunnerValue@@@Z absent-from-retail
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

// ?run@Rva008CCED0BytecodeRunner@@QAEPAEPAX0H@Z
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
	int count;
	m_savedStackBase = m_count;
	if (m_stop != zero)
		goto reloadBound;
loop:
	if (execute.m_end != (unsigned char *)zero && execute.m_cursor == execute.m_end)
	{
		execute.m_heldValue->release();
		execute.m_heldValue = (Rva008CCED0BytecodeRunnerValue *)zero;
		execute.m_end = (unsigned char *)zero;
	}
	{
		unsigned opcode = *execute.m_cursor++;
		bound = limit;
		if (execute.m_stopped)
			goto cleanup;
		if (bound >= zero && execute.m_cursor - start > bound)
			goto pushFallback;
		if (opcode == (unsigned)zero)
			goto nullOpcode;
		g_bfmeR1226Opcodes[opcode](this, &execute);
		if (m_stop == zero)
			goto loop;
	}
reloadBound:
	bound = limit;
cleanup:
	{
		count = m_count;
		if (bound >= zero && count > m_savedStackBase)
		{
			popValues(count - m_savedStackBase - 1);
			goto finishCleanup;
		}
		goto unboundedCleanup;
nullOpcode:
		if (bound < zero)
			goto cleanup;
pushFallback:
		pushValue((Rva008CCED0BytecodeRunnerValue *)g_bfmeFallbackDB);
		goto cleanup;
unboundedCleanup:
		if (count > m_savedStackBase)
			popValues(count - m_savedStackBase);
	}

finishCleanup:
	m_savedStackBase = oldStackBase;

	if (bound == -1)
	{
		m_ownedValues[m_ownedCount - 1]->release();
		--m_ownedCount;
	}

	int finalCount = *(unsigned *)&m_count;
	if ((finalCount == zero || (finalCount == 1 && m_stack[m_count - 1] == (Rva008CCED0BytecodeRunnerValue *)g_bfmeFallbackDB)) &&
		((Rva8CCED0IdleHook *)g_rva8CD130IdleHook)->m_enabled != zero)
		((Rva8CCED0IdleHook *)g_rva8CD130IdleHook)->run();

	return execute.m_cursor;
}
