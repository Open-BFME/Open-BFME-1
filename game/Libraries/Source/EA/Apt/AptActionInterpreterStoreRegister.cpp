// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// EA Apt ActionScript StoreRegister (opcode 0x87), retail 0x008CA920.
// The interpreter's opcode table in .data is indexed by the Flash action
// code: Equals (0x0E, 0x008C7140) sits at 0x00ED5AA0 and BitAnd (0x60,
// 0x008CA030) at 0x00ED5BE8, which puts the table base at 0x00ED5A68 and
// this body in slot 0x87 at 0x00ED5C84.
//
// The operand is the register index as an aligned dword.  The top of the
// stack replaces that register, releasing the old value and adding a
// reference to the new one.  Retail tests whether the +0x58 register array
// is the +0x54 one and then runs the same store in both branches, re-reading
// the operand each time; the two arms are kept that way.

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
	};

	static void _FunctionAptActionStoreRegister(
		AptActionInterpreter *interpreter, LocalContextT *context);

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
	char m_pad0C[0x48];
	AptValue **m_registers54;
	AptValue **m_registers58;
};

void AptActionInterpreter::_FunctionAptActionStoreRegister(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	const unsigned char *p = (const unsigned char *)(((unsigned int)context->m_pc + 3) & ~3u);
	context->m_pc = p + 4;
	if (interpreter->m_registers58 != interpreter->m_registers54)
	{
		if (interpreter->m_registers58[*(const int *)p])
			interpreter->m_registers58[*(const int *)p]->Release();
		interpreter->m_registers58[*(const int *)p] = interpreter->m_stack[interpreter->m_stackTop - 1];
		if (interpreter->m_registers58[*(const int *)p])
			interpreter->m_registers58[*(const int *)p]->AddRef();
	}
	else
	{
		if (interpreter->m_registers58[*(const int *)p])
			interpreter->m_registers58[*(const int *)p]->Release();
		interpreter->m_registers58[*(const int *)p] = interpreter->m_stack[interpreter->m_stackTop - 1];
		if (interpreter->m_registers58[*(const int *)p])
			interpreter->m_registers58[*(const int *)p]->AddRef();
	}
}
