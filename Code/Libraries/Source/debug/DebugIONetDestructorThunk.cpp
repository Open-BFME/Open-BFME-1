// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??1DebugIONet@@UAE@XZ: Code/Libraries/Source/WWVegas/WWDebug/debug_io_net.cpp
// Open-BFME5: lift DebugIONet dtor __emit thunk to clean C++. Retail keeps
// an EBP frame (/Oy-): stores its own vtable at entry, FreeConsole() when the
// byte flag at this+4 is set, then runs the inlined base dtor (base vtable
// store) on the normal and unwind paths.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);

class DebugIONetBase
{
public:
	virtual ~DebugIONetBase() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIONet : public DebugIONetBase
{
public:
	virtual ~DebugIONet();

private:
	bool m_allocatedConsole;
};

// ??1DebugIONet@@UAE@XZ
DebugIONet::~DebugIONet()
{
	if (m_allocatedConsole) {
		FreeConsole();
	}
}
