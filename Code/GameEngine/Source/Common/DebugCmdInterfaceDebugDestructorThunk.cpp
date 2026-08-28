// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME5: DebugCmdInterfaceDebug dtor (ICF of DebugIOFlat). EBP frame (/Oy-):
// own vtable at entry, FreeConsole() when flag at this+4 set, base vtable store.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);
void DebugFreeMemory(void *ptr);

class DebugCmdInterfaceDebugBase
{
public:
    virtual ~DebugCmdInterfaceDebugBase() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal.h
class DebugCmdInterfaceDebug : public DebugCmdInterfaceDebugBase
{
public:
    virtual ~DebugCmdInterfaceDebug();
    virtual void Delete();

private:
    bool m_allocatedConsole;
};

// ??1DebugCmdInterfaceDebug@@UAE@XZ
DebugCmdInterfaceDebug::~DebugCmdInterfaceDebug()
{
    if (m_allocatedConsole) {
        FreeConsole();
    }
}

// ?Delete@DebugCmdInterfaceDebug@@UAEXXZ
// Destroys through vtable slot 0 with the "do not free" flag, then frees
// separately -- the shape retail uses for this Delete idiom.
void DebugCmdInterfaceDebug::Delete()
{
	this->~DebugCmdInterfaceDebug();
	DebugFreeMemory(this);
}
