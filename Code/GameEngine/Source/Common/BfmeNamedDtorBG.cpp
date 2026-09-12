// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Ireference/shims/stringinline
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

extern "C" BfmeHostCA *g_bfmeGameCW;

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
	g_bfmeGameCW->bfmeRemoveCA(bfmeGetKeyBG().str());
}
