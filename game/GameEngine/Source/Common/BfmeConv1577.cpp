// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" void __identifier("?deleteScratchSaveFile@GameState@@AAEXXZ")();

class BfmeStrVSG
{
public:
	char *m_bfme00;
};

class BfmeCreditsVSG
{
public:
	void bfmeInitVSG();
	char m_bfmePad000[0x27c];
	BfmeStrVSG m_bfme27c;
};

void BfmeCreditsVSG::bfmeInitVSG()
{
	reinterpret_cast<StringBase<char> *>(&m_bfme27c)->set("CreditsMenu", 11);
	union { void (*raw)(); void (BfmeCreditsVSG::*member)(); } next;
	next.raw = __identifier("?deleteScratchSaveFile@GameState@@AAEXXZ");
	(this->*next.member)();
}
