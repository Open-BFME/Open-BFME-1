class BfmeCrateERG
{
public:
	BfmeCrateERG(void);
	void bfmeAssignERG(const BfmeCrateERG &other);

	unsigned char m_bfmeVfERG[4];
	BfmeCrateERG *m_bfmeNextERG;
	char m_bfmeOverrideERG;
	char m_bfmePadERG[3];
	int m_bfmeAERG;
	int m_bfmeBERG;
	int m_bfmeCERG;
};

// Retail's constructor call goes through ILT 0x26CBA to the
// matched 34-byte ctor ??0Rva00618630@@QAE@XZ (0x00618630,
// R3ScalarFieldConstructors.cpp): same 24-byte object, so the fresh crate is
// built by that constructor.
class Rva00618630
{
public:
	Rva00618630();
	unsigned char m_bfmeBytes[24];
};

class BfmeCrateSystemERG
{
public:
	BfmeCrateERG *bfmeNewOverrideERG(BfmeCrateERG *crate);
};

// Retail's assignment call at 0x00448725 is the five-byte ILT thunk
// ?j_00048725@@YAXXZ (game/gen_small/thunks_034.cpp), whose body is the 5-byte
// ?m@Gen_00094900@@QAEXPAXH@Z gen-shim at 0x00094900, so the call names the
// thunk: the call site keeps the source crate on the stack and the fresh one
// in ecx, and the pointer-to-member view of the union types that thiscall
// while the address it holds makes the compiler emit the direct call.
extern "C" void __identifier("?j_00048725@@YAXXZ")();

BfmeCrateERG *BfmeCrateSystemERG::bfmeNewOverrideERG(BfmeCrateERG *crate)
{
	if (crate == 0)
		return 0;

	BfmeCrateERG *fresh = (BfmeCrateERG *)new Rva00618630;
	union AssignCall {
		void (*bfmeThunk)();
		void (BfmeCrateERG::*bfmeAssign)(const BfmeCrateERG &);
	} drop;

	drop.bfmeThunk = (void (*)())&__identifier("?j_00048725@@YAXXZ");
	(fresh->*drop.bfmeAssign)(*crate);
	fresh->m_bfmeAERG = crate->m_bfmeAERG;
	fresh->m_bfmeBERG = crate->m_bfmeBERG;
	fresh->m_bfmeCERG = crate->m_bfmeCERG;
	crate->m_bfmeNextERG = fresh;
	fresh->m_bfmeOverrideERG = 1;
	return fresh;
}