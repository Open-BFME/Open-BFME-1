// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME: empty DebugCmdInterfaceDebug ctor. Same two-vtable EH shape
// as DebugIOOds / DebugIONet: inlines the DebugCmdInterface vtable store,
// then stores the derived vtable, with the EH state around the derived
// store because the base has a virtual destructor.

class DebugCmdInterface
{
protected:
	virtual ~DebugCmdInterface() {}

public:
	DebugCmdInterface() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal.h
class DebugCmdInterfaceDebug : public DebugCmdInterface
{
public:
	explicit DebugCmdInterfaceDebug(void);
};

// ??0DebugCmdInterfaceDebug@@QAE@XZ
DebugCmdInterfaceDebug::DebugCmdInterfaceDebug(void)
{
}
