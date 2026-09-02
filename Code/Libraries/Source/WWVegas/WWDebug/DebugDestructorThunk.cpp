// cl: /DNDEBUG /MD /EHa /Oy-
// Debug destructor: store the Debug vtable then destroy the member at +0x9E6F.
// That offset is one byte before m_prefix at +0x9E70 (see debug_operator_uint.cpp).

class DebugMember
{
public:
	~DebugMember();
};

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
