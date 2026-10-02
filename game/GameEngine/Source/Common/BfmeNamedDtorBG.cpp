// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/stringinline
//
// Open-BFME5: named object destructor at retail 0x0060AB40, 149 bytes; shares
// the vftable constant 0x01115C60 with the constructor at 0x0060AAE0
// (BfmeNamedCtorBG.cpp), proving the same class.

#include "StringInline.h"

class BfmeHostCA
{
public:
	void bfmeRemoveCA(const char *name);
};

// The singleton at 0x012F706C is DEFINED as
// `LivingWorldManager *TheLivingWorldManager` (?TheLivingWorldManager@@3PAV
// LivingWorldManager@@A, targets/game/reverse/data_rows.csv); nothing defines
// ?g_bfmeGameCW@@3PAVBfmeGameCW@@A, so only a reference to the defining
// spelling links. bfmeRemoveCA is matched on BfmeHostCA (0x00616320), so the
// pointer is cast at the use.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

// Defined in BfmeNamedCtorBG.cpp (its own row keeps this file's row from
// counting as an orphan-inducing duplicate class); undefined here so the
// compiler cannot elide the call. The base -- not the derived class --
// introduces the vtable, so its vfptr and this both sit at offset 0.
class BfmeNamedBaseBG
{
public:
	virtual ~BfmeNamedBaseBG();
};

class BfmeNamedBG : public BfmeNamedBaseBG
{
public:
	~BfmeNamedBG();

	__declspec(noinline) AsciiString bfmeGetKeyBG() const;

	char m_bfmePadBG[0x9c];
	volatile char m_bfmeFlagBG;
	char m_bfmePadBBG[3];
	volatile int m_bfmeABG;
	volatile int m_bfmeBBG;
	AsciiString m_bfmeKeyBG;
};

__declspec(noinline) AsciiString BfmeNamedBG::bfmeGetKeyBG() const
{
	return m_bfmeKeyBG;
}

BfmeNamedBG::~BfmeNamedBG()
{
	((BfmeHostCA *)TheLivingWorldManager)->bfmeRemoveCA(bfmeGetKeyBG().str());
}
