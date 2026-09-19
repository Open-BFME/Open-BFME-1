// cl: /DNDEBUG /MD /EHa /Oy-
// Open-BFME: empty DebugIOOds ctor. Same two-vtable EH shape as DebugIONet.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class DebugIOInterface
{
protected:
	virtual ~DebugIOInterface() {}

public:
	DebugIOInterface() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIOOds : public DebugIOInterface
{
public:
	explicit DebugIOOds(void);
};

// ??0DebugIOOds@@QAE@XZ
DebugIOOds::DebugIOOds(void)
{
}
