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

class Vector3;
class Vector4;

// These are StreakLineClass's protected setters at retail
// 0x0091A300 / 0x0091A380 / 0x0091A420 (streak.cpp).
class StreakLineClass
{
	friend class BfmeStreakUGB;

protected:
	void Set_Locs(unsigned n, Vector3 *locs);
	void Set_Widths(unsigned n, float *widths);
	void Set_Colors(unsigned n, Vector4 *colors);
};

class BfmeStreakUGB
{
public:
	void bfmeSetUGB(unsigned n, void *locs, void *widths, void *colors, int stamp);
	char m_bfmePad[0x10];
	int m_bfmeFlags;
	char m_bfmePad2[0xb8];
	int m_bfmeStamp;
};

void BfmeStreakUGB::bfmeSetUGB(unsigned n, void *locs, void *widths, void *colors, int stamp)
{
	m_bfmeStamp = stamp;
	reinterpret_cast<StreakLineClass *>(this)->Set_Locs(n, static_cast<Vector3 *>(locs));
	if (widths)
		reinterpret_cast<StreakLineClass *>(this)->Set_Widths(n, static_cast<float *>(widths));
	if (colors)
		reinterpret_cast<StreakLineClass *>(this)->Set_Colors(n, static_cast<Vector4 *>(colors));
	m_bfmeFlags &= ~0x20000;
}
