// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME5: DebugCmdInterfaceDebug dtor (ICF of DebugIOFlat). EBP frame (/Oy-):
// own vtable at entry, FreeConsole() when flag at this+4 set, base vtable store.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);

class DebugCmdInterfaceDebugBase
{
public:
    virtual ~DebugCmdInterfaceDebugBase() {}
};

class DebugCmdInterfaceDebug : public DebugCmdInterfaceDebugBase
{
public:
    virtual ~DebugCmdInterfaceDebug();

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
