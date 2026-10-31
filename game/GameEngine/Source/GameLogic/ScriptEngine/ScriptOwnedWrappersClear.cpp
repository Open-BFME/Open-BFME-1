// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class ScriptGroupPoolObject
{
public:
};

class ScriptPoolObject
{
public:
	void deleteInstance(int);
};

struct ScriptGroupWrapper
{
	ScriptGroupPoolObject *m_value;
};

struct ScriptWrapper
{
	ScriptPoolObject *m_value;
};

class BfmeScriptOwnedWrappers
{
public:
	void clear();

private:
	ScriptWrapper *m_script;
	ScriptGroupWrapper *m_scriptGroup;
};

extern "C" void __cdecl __identifier("?j_00002338@@YAXXZ")();
extern "C" void __cdecl __identifier("?j_00022039@@YAXXZ")();

void BfmeScriptOwnedWrappers::clear()
{
	union { void (*raw)(); void *(ScriptGroupPoolObject::*member)(unsigned); }
		dropGroup = { __identifier("?j_00002338@@YAXXZ") };
	union { void (*raw)(); void *(ScriptPoolObject::*member)(unsigned); }
		dropScript = { __identifier("?j_00022039@@YAXXZ") };
	ScriptGroupWrapper *scriptGroup = m_scriptGroup;
	if (scriptGroup != 0) {
		if (scriptGroup->m_value != 0)
			(scriptGroup->m_value->*dropGroup.member)(1);
		operator delete(scriptGroup);
	}

	ScriptWrapper *script = m_script;
	if (script != 0) {
		if (script->m_value != 0)
			(script->m_value->*dropScript.member)(1);
		operator delete(script);
	}
}

// Retail 0x003525E0 (200 B, ret 4 at +0xC5 then int3 padding to 0x003526E0):
// the copy constructor reached through ILT 0x00024C12, called by the matched
// Rva003529B0/Rva00354BC0 copies and the ScriptList copy constructor. Each held
// wrapper is deep-copied through new and its ILT copy constructor (0x0003910D,
// 0x0003CFDD); the catch(...) funclet sits inside the body at +0x86 and frees the
// first copy through ScriptPoolObject::deleteInstance (ILT 0x00022039) before
// rethrowing. Same +0/+4 layout as BfmeScriptOwnedWrappers above.
class BfmeNodeCU
{
public:
	BfmeNodeCU(const BfmeNodeCU &other);
	~BfmeNodeCU()
	{
		if (m_value != 0)
			m_value->deleteInstance(1);
	}

private:
	ScriptPoolObject *m_value;
	int m_unused04;
	int m_unused08;
};

class BfmeNodeCV
{
public:
	BfmeNodeCV(const BfmeNodeCV &other);

private:
	int m_unused00;
	int m_unused04;
	int m_unused08;
};

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	BfmeNodeCU *m_a;
	BfmeNodeCV *m_b;
};

Rva003525E0Pair::Rva003525E0Pair(const Rva003525E0Pair &other)
{
	m_a = other.m_a ? new BfmeNodeCU(*other.m_a) : 0;
	try
	{
		m_b = other.m_b ? new BfmeNodeCV(*other.m_b) : 0;
	}
	catch (...)
	{
		delete m_a;
		throw;
	}
}
