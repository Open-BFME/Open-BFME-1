// cl: /O2 /Ob0

// The stored address is the real STLport wide istream vftable
// (symbols.csv: ??_7?$basic_istream@GV?$char_traits@G@_STL@@@_STL@@6B@ at
// 0x0112F2FC), named with __identifier() so the DIR32 points at it directly.
extern "C" void *__identifier("??_7?$basic_istream@GV?$char_traits@G@_STL@@@_STL@@6B@")[];

class HoldRva00841110
{
public:
	char m_lead[4];
	int m_off;
};

class Rva00841110
{
public:
	void apply();
};

void Rva00841110::apply()
{
	HoldRva00841110 *hold = *(HoldRva00841110 **)((char *)this - 8);
	*(unsigned *)((char *)this - 8 + hold->m_off) =
		(unsigned)__identifier("??_7?$basic_istream@GV?$char_traits@G@_STL@@@_STL@@6B@");
}
