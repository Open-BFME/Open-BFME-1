// cl: /DNDEBUG /MD /EHa /Oy-
// Debug destructor: store the Debug vtable then destroy the member at +0x9E6F.
// That offset is one byte before m_prefix at +0x9E70 (see debug_operator_uint.cpp).

class DebugMember
{
public:
	~DebugMember();
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

__declspec(noinline) DebugMember::~DebugMember() { _ReadWriteBarrier(); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
	virtual ~Debug();
	char m_pad[0x9E6B];
	DebugMember m_member;
};

// ??1Debug@@UAE@XZ
Debug::~Debug()
{
}
