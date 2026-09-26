struct BfmePairJC
{
	float m_bfmeXJC;
	float m_bfmeYJC;
};

class BfmeUnitJC
{
public:
	int bfmeQueryJC(BfmePairJC *direction, float *distance);
};

extern const float g_bfmeDirectionWeight1285;

class BfmeOwnerJC
{
public:
	char bfmeNearJC(void);

	int m_bfmeSpareJC;
	void *m_bfmeThingJC;
	unsigned char m_bfmeGapJC[8];
	BfmeUnitJC *m_bfmeUnitJC;
};

char BfmeOwnerJC::bfmeNearJC(void)
{
	if (m_bfmeThingJC == 0)
		return 0;

	BfmeUnitJC *unit = m_bfmeUnitJC;

	if (unit == 0)
		return 0;

	float distance;
	BfmePairJC direction;

	if (unit->bfmeQueryJC(&direction, &distance) == 0)
		return 0;

	if (distance < g_bfmeDirectionWeight1285)
		return 1;

	return 0;
}
