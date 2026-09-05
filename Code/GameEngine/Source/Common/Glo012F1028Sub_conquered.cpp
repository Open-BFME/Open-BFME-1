// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// Glo012F1028Sub method at 0x003C7130. Same holder/+4, owner-at-holder+0x40,
// payload-at-item+0x28, and pointer vector at holder+0x30 as landed
// Glo012F1028Sub::bfmeBegin (0x003C7010). Keys are ConqueredEffectFlareup
// and ConqueredEffectEvenglow. notify0C is ILT 0x0000B316; notify08 is
// ILT 0x00006BAE -> landed notify08 at 0x003BAD70.

class Glo012F1028Item
{
public:
	char m_bfmeHead[0x08];
	void *m_bfmeName;
	char m_bfmePayloadHead[0x28 - 0x0C];
	int m_bfmePayload;
};

class Rva003BAD00Owner
{
public:
	void notify0C(const AsciiString &key, const void *payload, int b);
	void notify08(const AsciiString &key, int a);
};

class BfmeItemVector
{
public:
	Glo012F1028Item **m_bfmeStart;
	Glo012F1028Item **m_bfmeFinish;
};

class Glo012F1028Holder
{
public:
	char m_bfmeHead[0x30];
	BfmeItemVector m_bfmeItems;
	char m_bfmeGap[0x40 - 0x30 - 8];
	Rva003BAD00Owner m_bfmeOwner;
};

class Glo012F1028Sub
{
private:
	void bfmeConquered(Glo012F1028Item *item);

	char m_bfmeHead[0x04];
	Glo012F1028Holder *m_bfmeHolder;
};

// ?bfmeConquered@Glo012F1028Sub@@AAEXPAVGlo012F1028Item@@@Z
void Glo012F1028Sub::bfmeConquered(Glo012F1028Item *item)
{
	Rva003BAD00Owner *owner = &m_bfmeHolder->m_bfmeOwner;
	owner->notify0C(AsciiString("ConqueredEffectFlareup"),
		&item->m_bfmePayload, 0);

	BfmeItemVector *vec = &m_bfmeHolder->m_bfmeItems;
	Glo012F1028Item **it = vec->m_bfmeStart;
	Glo012F1028Item **last = vec->m_bfmeFinish;
	if (it != last)
	{
		do
		{
			owner->notify0C(AsciiString("ConqueredEffectEvenglow"),
				&(*it)->m_bfmePayload, 0);
			++it;
		} while (it != vec->m_bfmeFinish);
	}

	owner->notify08(AsciiString("ConqueredEffectFlareup"), 1);
	owner->notify08(AsciiString("ConqueredEffectEvenglow"), 1);
}
