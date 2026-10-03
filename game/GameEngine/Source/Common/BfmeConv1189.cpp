// Open-BFME5 conversions.

// The vptr BfmeBase1189 stamps at +0 is retail VA 0x0111291C, the vftable of
// Rva005E95C0 (targets/game/reverse/dir32_addresses.csv), defined once by
// game/GameEngine/Source/Common/V3PolyCopyCtors.cpp. __identifier spells the
// retail symbol exactly, so the store references the defining name.
extern "C" int __identifier("??_7Rva005E95C0@@6B@")[];

struct BfmeQuad1189
{
	BfmeQuad1189(void)
	{
		m_bfme08 = 0;
		m_bfme04 = 0;
		m_bfme00 = 0;
		m_bfme0c = 0;
	}
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeBase1189
{
public:
	BfmeBase1189(void) { m_bfme00 = (char *)__identifier("??_7Rva005E95C0@@6B@"); }
	char *volatile m_bfme00;
};

class BfmeA1189 : public BfmeBase1189
{
public:
	BfmeA1189(void);
	BfmeQuad1189 m_bfme04[8];
	int m_bfme84;
};

BfmeA1189::BfmeA1189(void)
{
	m_bfme84 = 0;
}
