// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME: Debug I/O net destructor. Stores the net vtable, CloseHandle on
// the pipe at +4 unless it is INVALID_HANDLE_VALUE, then restores the
// DebugIOInterface vtable. Named apart from ??1DebugIONet which is already
// claimed on the FreeConsole ICF body.

typedef void *HANDLE;

extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class DebugIOInterface
{
protected:
	virtual ~DebugIOInterface() {}

public:
	DebugIOInterface() {}
};

class Rva0088FB30NetIO : public DebugIOInterface
{
	HANDLE m_pipe;

public:
	virtual ~Rva0088FB30NetIO();
};

// ??1Rva0088FB30NetIO@@UAE@XZ
Rva0088FB30NetIO::~Rva0088FB30NetIO()
{
	if (m_pipe != (HANDLE)-1)
		CloseHandle(m_pipe);
}
