// cl: /DNDEBUG /MD /EHsc
// Convert 0x0026D4F0: range-vs-gap compare, this-adj [esi-0x18].

struct BfmePt951
{
	float m_bfmeX;
	float m_bfmeY;
};

class BfmeGap951
{
public:
	float bfmeGapB951(const BfmePt951 *other) const;
};

class Gen_001E1950
{
public:
	float bfmeValue(void) const;
};

class BfmeGeomD4F0
{
public:
	BfmeGap951 *m_bfmeGeom;
	char m_bfmePad[0x14];
};

class BfmeWeapD4F0
{
public:
	bool bfmeInRangeD4F0(const BfmePt951 *pt);

	char m_bfmePad[0xc8];
	Gen_001E1950 *m_bfmeWeap;
};

class BfmeBothD4F0 : public BfmeGeomD4F0, public BfmeWeapD4F0
{
};

bool BfmeWeapD4F0::bfmeInRangeD4F0(const BfmePt951 *pt)
{
	Gen_001E1950 *weap = m_bfmeWeap;
	if (!weap)
		return false;

	if (pt)
	{
		float range = weap->bfmeValue();
		if (static_cast<BfmeBothD4F0 *>(this)->m_bfmeGeom->bfmeGapB951(pt) < range * range)
			return false;
	}
	return true;
}
