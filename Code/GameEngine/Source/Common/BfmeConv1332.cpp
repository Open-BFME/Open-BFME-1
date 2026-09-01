// Open-BFME5 conversions.

struct BfmeVecUGA
{
	float m_bfmeX;
	float m_bfmeY;
	float m_bfmeZ;
};

class BfmeCellUGA
{
public:
	BfmeCellUGA *bfmeSetUGA(const BfmeVecUGA *v);
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

BfmeCellUGA *BfmeCellUGA::bfmeSetUGA(const BfmeVecUGA *v)
{
	m_bfmeX = (int)v->m_bfmeX;
	m_bfmeY = (int)v->m_bfmeY;
	m_bfmeZ = (int)v->m_bfmeZ;
	return this;
}

class BfmeStreakUGB
{
public:
	void bfmeSetUGB(unsigned n, void *locs, void *widths, void *colors, int stamp);
	void bfmeSetLocsUGB(unsigned n, void *locs);
	void bfmeSetWidthsUGB(unsigned n, void *widths);
	void bfmeSetColorsUGB(unsigned n, void *colors);
	char m_bfmePad[0x10];
	int m_bfmeFlags;
	char m_bfmePad2[0xb8];
	int m_bfmeStamp;
};

void BfmeStreakUGB::bfmeSetUGB(unsigned n, void *locs, void *widths, void *colors, int stamp)
{
	m_bfmeStamp = stamp;
	bfmeSetLocsUGB(n, locs);
	if (widths)
		bfmeSetWidthsUGB(n, widths);
	if (colors)
		bfmeSetColorsUGB(n, colors);
	m_bfmeFlags &= ~0x20000;
}
