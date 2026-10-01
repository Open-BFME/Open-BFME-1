// Open-BFME5 conversions.

class BfmeR1093
{
public:
	char bfmeHas1093(int a);
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeD1093
{
public:
	BfmeR1093 *bfmeLook1093(short *h);
};

class BfmeP1093
{
public:
	int bfmeNext1093(int a);
};

// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the address-derived lookups this TU
// spells are still unnamed, so the global keeps its real spelling and the reads are cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]
extern BfmeP1093 *g_bfmeP1093;

char __stdcall bfmeGo1093A(int a, int b)
{
	int h;

	a = g_bfmeP1093->bfmeNext1093(a);
	h = g_bfmeP1093->bfmeNext1093(b);
	while ((short)a) {
		BfmeR1093 *r = ((BfmeD1093 *)ThePlayerList)->bfmeLook1093((short *)&a);

		if (r) {
			b = h;
			while ((short)b) {
				BfmeR1093 *q = ((BfmeD1093 *)ThePlayerList)->bfmeLook1093((short *)&b);

				if (q) {
					int m = q->m_bfme24;

					if (r->bfmeHas1093(m))
						return 1;
				}
			}
		}
	}
	return 0;
}
