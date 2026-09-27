// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME5: DebugIOCon's destructor and DebugCmdInterfaceDebug::Delete. /EHa /Oy-
// give ~DebugIOCon retail's EBP frame and EH state around FreeConsole(); retail
// 0x00890F10 stores DebugIOCon's table 0x01135C9C, then DebugIOInterface's.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);
void DebugFreeMemory(void *ptr);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class DebugIOInterface
{
public:
    virtual ~DebugIOInterface() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIOCon : public DebugIOInterface
{
public:
    virtual ~DebugIOCon();

private:
    bool m_allocatedConsole;
};

// ??1DebugIOCon@@UAE@XZ
DebugIOCon::~DebugIOCon()
{
    if (m_allocatedConsole) {
        FreeConsole();
    }
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_cmd.h
class DebugCmdInterface
{
protected:
    virtual ~DebugCmdInterface() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal.h
class DebugCmdInterfaceDebug : public DebugCmdInterface
{
public:
    virtual ~DebugCmdInterfaceDebug();
    virtual void Delete();
};

// Out of line because retail's deleting destructors call it (0x0088A6B0 -> 0x0088A6E0).
__declspec(noinline) DebugCmdInterfaceDebug::~DebugCmdInterfaceDebug() {}

// ?Delete@DebugCmdInterfaceDebug@@UAEXXZ
// Destroys through vtable slot 0 with the "do not free" flag, then frees
// separately -- the shape retail uses for this Delete idiom.
void DebugCmdInterfaceDebug::Delete()
{
	this->~DebugCmdInterfaceDebug();
	DebugFreeMemory(this);
}
