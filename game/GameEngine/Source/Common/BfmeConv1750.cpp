// Retail VA 0x0110CBEC is Rva0059FB40TailDtor's own vftable: the derived
// destructor at 0x0059FB40 is `mov dword ptr [ecx],0x0110CBEC ; jmp base`.
// That table is a COMDAT emitted by VptrTailJumpDestructors.cpp, and C++ has no
// expression for a vftable address, so it is spelled by its decorated symbol
// with __identifier (the convention BfmeConv2067.cpp uses for the same table
// family) rather than by a stand-in name.
extern "C" int __identifier("??_7Rva0059FB40TailDtor@@6B@");

class BfmeBaseBC
{
};

extern "C" void __cdecl __identifier("?j_0001b522@@YAXXZ")();
typedef void (__fastcall *BfmeBaseBCConstructorThunk)(BfmeBaseBC *self);

class BfmeOwnBC : public BfmeBaseBC
{
public:
	BfmeOwnBC(void);

	int *m_bfmeVfBC;
	int m_bfmeABC;
	unsigned char m_bfmeHeadBC[8];
	int m_bfmeBBC;
	int m_bfmeCBC;
	int m_bfmeDBC;
	char m_bfmeEBC;
	unsigned char m_bfmePadBC[3];
	float m_bfmeFBC;
	char m_bfmeGBC;
};

BfmeOwnBC::BfmeOwnBC(void)
{
	((BfmeBaseBCConstructorThunk)&__identifier(
		"?j_0001b522@@YAXXZ"))(static_cast<BfmeBaseBC *>(this));
	m_bfmeVfBC = &__identifier("??_7Rva0059FB40TailDtor@@6B@");
	m_bfmeCBC = 0x1e;
	m_bfmeBBC = 0;
	m_bfmeEBC = 0;
	m_bfmeGBC = 0;
	m_bfmeDBC = 7;
	m_bfmeFBC = 1.0f;
	m_bfmeABC = 0x1e;
}
