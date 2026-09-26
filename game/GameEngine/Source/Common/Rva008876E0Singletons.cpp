// ?getRva008876E0Singleton@@YAPAXXZ
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME7: two static-guard singleton getters (0x008877A0 and 0x008876E0)
// kept in ONE TU so their compiler-generated atexit thunks get distinct $E
// names (two TUs would both emit $E2 and the pins would collide).

extern "C" __declspec(dllimport) void __stdcall Rva01358E4CInit(void *body);
extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *body);

class Rva008877A0Type
{
public:
	char m_pad0[0x18];
	bool m_flag18;

	Rva008877A0Type()
	{
		m_flag18 = true;
		Rva01358E4CInit(this);
	}
	~Rva008877A0Type()
	{
		Rva01358D0CReset(this);
		m_flag18 = false;
	}
};

class Rva008876E0Type
{
public:
	char m_pad0[0x18];
	bool m_flag18;

	Rva008876E0Type()
	{
		m_flag18 = true;
		Rva01358E4CInit(this);
	}
	~Rva008876E0Type()
	{
		Rva01358D0CReset(this);
		m_flag18 = false;
	}
};

// ?getRva008877A0Singleton@@YAPAXXZ
void *getRva008877A0Singleton()
{
	static Rva008877A0Type obj;
	return &obj;
}

void *getRva008876E0Singleton()
{
	static Rva008876E0Type obj;
	return &obj;
}
