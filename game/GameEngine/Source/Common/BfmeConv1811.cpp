struct BfmePairJC
{
	float m_bfmeXJC;
	float m_bfmeYJC;
};

struct Coord2D;

// ILT 0x0000E359 -> 0x003FD6E0, the matched getNextOptimized@PathNode.
class PathNode
{
public:
	const PathNode *getNextOptimized(Coord2D *dir, float *dist) const;
};

typedef PathNode BfmeUnitJC;

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

	if (unit->getNextOptimized(reinterpret_cast<Coord2D *>(&direction), &distance) == 0)
		return 0;

	if (distance < g_bfmeDirectionWeight1285)
		return 1;

	return 0;
}
