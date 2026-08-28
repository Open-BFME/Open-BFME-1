// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

extern ScriptEngine *TheScriptEngine;

class Rva000C9530S00
{
public:
	virtual void s00();
};

class Rva000C9530S04 : public Rva000C9530S00
{
public:
	virtual void s04();
};

class Rva000C9530S08 : public Rva000C9530S04
{
public:
	virtual void s08();
};

class Rva000C9530S0C : public Rva000C9530S08
{
public:
	virtual void s0C();
};

class Rva000C9530S10 : public Rva000C9530S0C
{
public:
	virtual void s10();
};

class Rva000C9530S14 : public Rva000C9530S10
{
public:
	virtual void s14();
};

class Rva000C9530S18 : public Rva000C9530S14
{
public:
	virtual void s18();
};

class Rva000C9530Pointee : public Rva000C9530S18
{
public:
	virtual void dispatch(int, int);
};

class Rva000C9530
{
	char m_pad[0x220];
	Rva000C9530Pointee *m_pointee;

public:
	void wrap(int a, int b);
};

void Rva000C9530::wrap(int a, int b)
{
	TheScriptEngine->notifyOfObjectCreationOrDestruction();
	if (m_pointee)
		m_pointee->dispatch(a, b);
}
