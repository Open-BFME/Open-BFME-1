// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??0DebugIONet@@QAE@XZ: Code/Libraries/Source/WWVegas/WWDebug/debug_io_net.cpp
// Open-BFME: empty DebugIONet ctor. Inlines the DebugIOInterface vtable
// store, then stores the derived vtable, with the EH state around the
// derived store because the base has a virtual destructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class DebugIOInterface
{
protected:
	virtual ~DebugIOInterface() {}

public:
	DebugIOInterface() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIONet : public DebugIOInterface
{
public:
	explicit DebugIONet(void);
};

// ??0DebugIONet@@QAE@XZ
DebugIONet::DebugIONet(void)
{
}
