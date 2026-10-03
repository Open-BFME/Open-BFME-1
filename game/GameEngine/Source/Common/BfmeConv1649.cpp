// Open-BFME5 conversions.

// The seven callees of this destructor are all the ONE narrow
// StringBase<char>::releaseBuffer at 0x00887940 (matched in
// game/Libraries/Source/string/StringBase.cpp), so each member is the real
// narrow string and its inline destructor reaches that body directly.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef AsciiString BfmeStrVUO;

// Retail's prologue stores the vtable pointer 0x010EC774 at +0, so the class is
// polymorphic and the seven-string layout starts at +4. That table holds NINE
// slots (rva 0x00CEC774, entries 0..8, 0 at 9), so the class has nine virtuals
// and the destructor stays non-virtual: it is the scalar destructor the ledger
// row pins here. None of the nine has an identity this TU may spell -- slot 0
// is a five-byte ILT thunk (rva 0x00019489) onto
// ??_GGen_dtor_003a88e0@@UAEPAXI@Z, a vector deleting destructor of a class
// with a virtual base, and slots 1..8 point into the same 0x003A88E0 cluster --
// and a vtable slot can only name a member of the class, so they are declared
// pure here. The emitted table's CONTENTS are not byte-checked (only the stored
// address 0x010EC774 is), so pure slots keep this body's bytes exact while
// costing the object nothing undefined: __purecall is the matched 0x006CF680
// body in game/Libraries/Source/WWVegas/WWLib/Except.cpp.
class BfmeOwnVUO
{
public:
	~BfmeOwnVUO();
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmeSlot6() = 0;
	virtual void bfmeSlot7() = 0;
	virtual void bfmeSlot8() = 0;
	BfmeStrVUO m_bfme04;
	BfmeStrVUO m_bfme08;
	BfmeStrVUO m_bfme0c;
	char m_bfmePad10[0xc];
	BfmeStrVUO m_bfme1c;
	BfmeStrVUO m_bfme20;
	BfmeStrVUO m_bfme24;
	BfmeStrVUO m_bfme28;
};

BfmeOwnVUO::~BfmeOwnVUO()
{
}
