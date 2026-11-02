// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Rva0061A0F0Owner::rva0061A0F0 (retail 0x0061A0F0, 213 B, plain ret). Owner
// and method identity are not recovered, so both names are address-derived.
// It fetches an AsciiString from TheLivingWorldCampaignManager through
// 0x003B3950 (falling back to "NoActNameFound" when empty), then walks the
// 0x24-byte records of the vector at +0x9C until the first one whose +0x18
// byte is clear, and hands that record, 1 and its 0x006196F0 string to
// 0x00619C40. Retail loads ECX with this before that call, so the receiver
// is declared as a member of the owner (its body never reads ECX).
//
// The loop keeps retail's head test only with the foldable `searching &&`
// first term, and the record address is recomputed after the flag load only
// when each use indexes begin() directly (handoff
// targets/game/reverse/attempt_support/0061a0f0-unrotated-loop-20261102.md).
#include "ascii_string.h"

// 0x003B3950 returns the string through a hidden pointer under the ledger's
// BfmeRoomYC view; it carries one AsciiString.
class BfmeRoomYC : public AsciiString
{
};

class Glo012F1024Type
{
public:
	BfmeRoomYC Rva003B3950Room(void);
};

extern Glo012F1024Type *TheLivingWorldCampaignManager;

// The 0x24-byte record 0x00619C40 receives (its pinned 0x006196C0 getter
// names the type); 0x006196F0 is a second AsciiString getter on it, reached
// through ILT 0x0001DEE4.
struct Rva00619C40Entry
{
	AsciiString rva006196F0();
	char m_opaque00[0x18];
	unsigned char m_byte18;
	char m_opaque19[0xB];
};

struct Rva0061A0F0Vector
{
	Rva00619C40Entry *m_start;
	Rva00619C40Entry *m_finish;
	Rva00619C40Entry *m_endOfStorage;
	Rva00619C40Entry *begin() { return m_start; }
};

class Rva0061A0F0Owner
{
public:
	void rva0061A0F0();
	void rva00619C40(Rva00619C40Entry *entry, int index, const AsciiString &name);
	char m_opaque00[0x9C];
	Rva0061A0F0Vector m_entries;
};

void Rva0061A0F0Owner::rva0061A0F0()
{
	BfmeRoomYC name = TheLivingWorldCampaignManager->Rva003B3950Room();
	if (name.getLength() == 0)
		name.format(AsciiString("NoActNameFound"));
	bool found = false;
	bool searching = true;
	for (int i = 0; searching && !found; ++i)
	{
		if (m_entries.begin()[i].m_byte18 == 0)
		{
			rva00619C40(&m_entries.begin()[i], 1, m_entries.begin()[i].rva006196F0());
			found = true;
		}
	}
}
