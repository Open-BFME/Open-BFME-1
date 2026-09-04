// ?bfmeAdd1226@BfmeR1226@@QAEXPAX0H@Z
// partial score=0.78 date=2026-09-04
// ?bfmeAdd1226@BfmeR1226@@QAEXPAX0H@Z
// partial score=0.78 date=2026-09-02
// ?bfmeAdd1226@BfmeR1226@@QAEXPAX0H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// bounded Apt bytecode execution helper, retail 0x008CCED0 (375 bytes).

class BfmeR1226Value
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

class BfmeR1226;
struct BfmeR1226ExecContext
{
	unsigned char *m_cursor;
	int m_unknown04;
	BfmeR1226Value *m_heldValue;
	unsigned char *m_end;
	BfmeR1226Value *m_created;
	bool m_stopped;
};

typedef void (__cdecl *BfmeR1226Opcode)(BfmeR1226 *, BfmeR1226ExecContext *);

extern BfmeR1226Opcode g_bfmeR1226Opcodes[];
extern int g_rva8CCED0RouteMarker;
extern BfmeR1226Value *g_bfmeFallbackDB;

class Rva8CCED0IdleHook
{
public:
	int m_unused;
	int m_enabled;
	void run();
};

extern Rva8CCED0IdleHook *g_rva8CD130IdleHook;

class BfmeR1226
{
public:
	void bfmeAdd1226(void *code, void *value, int limit);
	BfmeR1226Value *makeValue(BfmeR1226Value *value, int zero, void *marker,
		int one1, int one2, int zero2);
	void popValues(int count);

	void pushValue(BfmeR1226Value *value)
	{
		m_stack[m_count++] = value;
		if (!value->maxRefCountHit())
			value->addRef();
	}

	int m_count;
	int m_unused;
	BfmeR1226Value **m_stack;
	char m_gap0c[0x24];
	int m_ownedCount;
	int m_ownedCapacity;
	BfmeR1226Value **m_ownedValues;
	char m_gap3c[0x40];
	int m_stop;
	int m_savedStackBase;
};

void BfmeR1226::bfmeAdd1226(void *code, void *valueArgument, volatile int limit)
{
	unsigned char *start = (unsigned char *)code;
	if (limit == -1)
	{
		m_ownedValues[m_ownedCount++] = (BfmeR1226Value *)valueArgument;
		((BfmeR1226Value *)valueArgument)->addRef();
	}
	BfmeR1226Value *value = (BfmeR1226Value *)valueArgument;

	int zero = 0;
	BfmeR1226ExecContext execute;
	execute.m_unknown04 = (int)value;
	execute.m_heldValue = (BfmeR1226Value *)zero;
	execute.m_cursor = start;
	execute.m_end = (unsigned char *)zero;
	execute.m_created = makeValue(value, zero, &g_rva8CCED0RouteMarker, 1, 1, zero);
	execute.m_stopped = (bool)zero;
	volatile int oldStackBase = m_savedStackBase;
	bool stopped = false;
	m_savedStackBase = m_count;
	for (;;)
	{
		if (m_stop != zero)
			break;
		if (execute.m_end != (unsigned char *)zero && execute.m_cursor == execute.m_end)
		{
			execute.m_heldValue->release();
			execute.m_heldValue = (BfmeR1226Value *)zero;
			execute.m_end = (unsigned char *)zero;
		}

		unsigned opcode = *execute.m_cursor++;
		if (execute.m_stopped)
			goto afterExecution;
		if (limit >= zero && execute.m_cursor - start > limit)
			goto pushFallback;
		if (opcode == (unsigned)zero)
		{
			if (limit < zero)
				goto afterExecution;
			goto pushFallback;
		}
		g_bfmeR1226Opcodes[opcode](this, &execute);
	}

afterExecution:
	if (m_count > m_savedStackBase)
	{
		int excess = m_count - m_savedStackBase;
		if (limit >= zero)
			--excess;
		if (excess > zero)
			popValues(excess);
	}
	goto finishCleanup;

pushFallback:
	pushValue(g_bfmeFallbackDB);
	goto afterExecution;

finishCleanup:
	m_savedStackBase = oldStackBase;

	if (limit == -1)
	{
		m_ownedValues[m_ownedCount - 1]->release();
		--m_ownedCount;
	}

	if ((m_count == zero || (m_count == 1 && m_stack[zero] == g_bfmeFallbackDB)) &&
		g_rva8CD130IdleHook->m_enabled != zero)
		g_rva8CD130IdleHook->run();

}
