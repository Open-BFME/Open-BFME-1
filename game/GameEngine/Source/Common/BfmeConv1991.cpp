// The retail call at 0x0005D731 is to ILT 0x0002B369, a 5-byte `jmp 0xABA820`
// (RVA 0x006BA820), which targets/game/reverse/functions.csv matches as
// ??0BfmeThingTGE@@QAE@XZ in game/GameEngine/Source/Common/BfmeConv1313.cpp.
// That ctor leaves a function table pointer in the object's first dword, and
// the `call dword ptr [eax + 0x48]` this body makes right after dispatches
// through it: the table is not a compiler-emitted vftable, so it is indexed
// directly and +0x48 is its nineteenth entry.
class BfmeThingTGE
{
public:
	BfmeThingTGE();
	void bfmeBaseTGE();
	void *m_bfmeVft;
	char m_bfmePad[0x58];
	void *m_bfmeHandle;
};

typedef void (BfmeThingTGE::*ApplyLevelTGE)(unsigned char);

// The allocated object's type as this body's own ledger row spells it.
class BfmeThingEUH;

// 0x012ED249, the byte the body loads into cl (retail .data holds 0; defined
// here under its pinned name, identity unproven).
unsigned char g_bfmeLevelEUH;

BfmeThingEUH *bfmeMakeEUH()
{
	BfmeThingTGE *obj = new BfmeThingTGE;

	(obj->*reinterpret_cast<ApplyLevelTGE *>(obj->m_bfmeVft)[0x48 / sizeof(void *)])(
			g_bfmeLevelEUH);

	return reinterpret_cast<BfmeThingEUH *>(obj);
}