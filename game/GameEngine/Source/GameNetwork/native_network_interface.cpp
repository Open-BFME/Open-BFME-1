// cl: /DNDEBUG /MD /GX

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

// Retail vtable at 0x0111A968, its own name ??_7Network@@6B@. C++ has no
// spelling for a vftable symbol (no class declares these entries here, and
// no key function is defined in this TU, so no class declaration would emit
// or name the vftable), so the extern carries the mangled name itself and the
// store relocates against the real symbol.
extern "C" const void *__identifier("??_7Network@@6B@")[];

// The first thing this constructor does is run the base constructor at
// 0x009A1A30, which the ledger carries as ??0SubsystemInterface@@QAE@XZ and
// whose body is game/GameEngine/Source/Common/System/SubsystemInterface.cpp:
// a public __thiscall no-argument constructor, i.e. `this` in ecx and no stack
// traffic. C++ cannot spell that name here -- naming it as a member call
// would need BFMENativeNetwork to derive from the real SubsystemInterface,
// which is a different class -- so the extern below carries the mangled name
// itself. __thiscall is rejected beside extern "C" (C4234) and __stdcall
// appends its own `@0` to the name, so neither spells this symbol; with no
// arguments __cdecl, __stdcall and __thiscall all encode the same call, and
// `this` is already in ecx.
extern "C" void __identifier("??0SubsystemInterface@@QAE@XZ")( void );

class BFMENativeNetwork
{
public:
	void *construct();

private:
	void *m_vtable;
	unsigned int m_unknown04;
	void *m_connectionManager;
	int m_state;
	__int64 m_performanceFrequency;
	__int64 m_lastPerformanceCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown29[3];
	unsigned int m_stallCount;
	unsigned int m_unknown30;
	bool m_flag34;
	bool m_flag35;
	char m_unknown36[2];
	int m_lastValue;
};

void *BFMENativeNetwork::construct()
{
	__identifier("??0SubsystemInterface@@QAE@XZ")();
	m_vtable = (void *)__identifier("??_7Network@@6B@");
	m_connectionManager = 0;
	m_state = 0;
	m_accumulator = 0;
	m_flag35 = false;
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	m_flag34 = false;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_lastValue = -1;
	return this;
}
