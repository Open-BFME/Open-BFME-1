// ?bfmeWithin@Gen_001E2940@@QBE_NPBVObject@@0@Z
// partial score=0.6 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Same value-minus-offset as Gen_001E1950::bfmeValue, then a distance-squared
// test: true when the offset-adjusted range is positive and larger than the
// separation of the two objects.

class Object
{
public:
	float getDistanceSquared(const Object *other) const;
};

class BfmeThingDF
{
public:
	int m_bfmeHead[6];
	float m_bfmeValue;
};

extern float g_bfmeOffsetDF;
extern float g_bfmeZeroCY;

class Gen_001E2940
{
public:
	bool bfmeWithin(const Object *a, const Object *b) const;

private:
	int m_bfmeHead;
	BfmeThingDF *m_bfmeThing;
};

bool Gen_001E2940::bfmeWithin(const Object *a, const Object *b) const
{
	float range = m_bfmeThing->m_bfmeValue - g_bfmeOffsetDF;
	float stored = range;
	if (stored > g_bfmeZeroCY)
	{
		if (stored * stored > a->getDistanceSquared(b))
			return true;
	}
	return false;
}
