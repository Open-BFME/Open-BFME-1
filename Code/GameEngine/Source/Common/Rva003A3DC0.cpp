// Retail 0x003A3DC0, 48 bytes.
// The body looks up a target through g_bfmeGameCW, then passes three member
// addresses and a byte member to the target's existing retail thunk. The
// receiver name stays RVA-derived because no caller proves a semantic owner.

class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;

class AsciiString;
struct Rva006122A0Item;

class Rva006122A0Mgr
{
public:
	Rva006122A0Item *find(const AsciiString &name);
};

class Rva003A3DC0Target
{
public:
	void apply(void *first, void *second, void *third, unsigned char flag);
};

extern void j_0003d893();

class Rva003A3DC0Owner
{
public:
	void rva003A3DC0(void *key);

	unsigned char m_head[4];
	unsigned char m_first[8];
	unsigned char m_second[0x11];
	unsigned char m_flag;
	unsigned char m_middle[0x2a];
	unsigned char m_third[4];
};

void Rva003A3DC0Owner::rva003A3DC0(void *key)
{
	Rva006122A0Mgr *game = reinterpret_cast<Rva006122A0Mgr *>(g_bfmeGameCW);
	Rva003A3DC0Target *target = reinterpret_cast<Rva003A3DC0Target *>(
		game->find(*reinterpret_cast<AsciiString *>(key)));

	typedef void (Rva003A3DC0Target::*Apply)(void *, void *, void *, unsigned char);
	union
	{
		void (*function)();
		Apply member;
	} route;
	route.function = j_0003d893;
	(target->*route.member)(m_first, m_second, m_third, m_flag);
}
