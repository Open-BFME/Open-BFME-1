// ?bfmeCellClear@Rva003D5B00Holder@@QBEHHH@Z
// partial score=0.95 date=2026-09-04
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Open-BFME5: thiscall cell bit test at retail 0x003D5B00 (75B).
// Sibling of rva003D5AE0 (0x003D5AE0): same +0xC & 0xFC0 vs 0x40 bitfield.
//
// PARTIAL: 73/75 bytes. MSVC 7.1 folds null-check into add flags (je after
// add) instead of retail test eax,eax / je. Remainder (push-esi-early,
// bounds, edx bitfield, jne/mov-1 tail) matches.

struct Rva003D5B00Cell { char m_pad[0xC]; unsigned m_bits; };
struct Rva003D5B00Map {
	char m_pad[0x10];
	Rva003D5B00Cell **m_rows;
	int m_minX; int m_minY; int m_maxX; int m_maxY;
};
class Rva003D5B00Holder {
public:
	int bfmeCellClear(int x, int y) const;
private:
	Rva003D5B00Map *m_map;
};

int Rva003D5B00Holder::bfmeCellClear(int x, int y) const
{
	Rva003D5B00Map *map = m_map;
	if (x < map->m_minX) goto fail;
	if (x > map->m_maxX) goto fail;
	if (y < map->m_minY) goto fail;
	if (y > map->m_maxY) goto fail;
	Rva003D5B00Cell *row = map->m_rows[x];
	Rva003D5B00Cell *cell = row + y;
	if ((unsigned)cell == 0u) goto fail;
	if ((cell->m_bits & 0xFC0u) == 0x40u)
		return 1;
fail:
	return 0;
}
