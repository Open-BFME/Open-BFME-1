// ?d_001eb3c0@@YAXXZ
// partial score=0.67 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x001EB3C0, 24 bytes through the int3 run at +0x18: a cdecl clear of
// six consecutive words.  Nothing references it or its ILT 0x00019FFB, so the
// names keep the address.  Its last 20 bytes equal
// ModelConditionInfo::TurretInfo::clear and were claimed as an alias of it;
// retail has no COMDAT folding, so they belong to this body.

struct Rva001EB3C0Words
{
	int m_word00;
	int m_word04;
	int m_word08;
	int m_word0C;
	int m_word10;
	int m_word14;
};

void Rva001EB3C0Clear( Rva001EB3C0Words *words )
{
	words->m_word00 = 0;
	words->m_word04 = 0;
	words->m_word08 = 0;
	words->m_word0C = 0;
	words->m_word10 = 0;
	words->m_word14 = 0;
}
