// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: GarrisonContain::calcBestGarrisonPosition at 0x0021E130.
// Methods run on this-0x20; the point table is at this+0x3DC with 40
// Coord3D slots per condition index.

typedef int Int;
typedef bool Bool;
#define NULL 0
enum { GARRISON_INDEX_INVALID = -1 };

struct Coord3D
{
	float x, y, z;
	void set(const Coord3D *p)
	{
		x = p->x;
		y = p->y;
		z = p->z;
	}
};

class GarrisonContain
{
public:
	Bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);

protected:
	Int findConditionIndex();
	Int findClosestFreeGarrisonPointIndex(Int conditionIndex, const Coord3D *targetPos);

private:
	char m_pad[0x3DC];
	Coord3D m_garrisonPoint[3][40];
};

// ?calcBestGarrisonPosition@GarrisonContain@@QAE_NPAUCoord3D@@PBU2@@Z
Bool GarrisonContain::calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos)
{
	if (sourcePos == NULL || targetPos == NULL)
		return false;
	GarrisonContain *g = (GarrisonContain *)((char *)this - 0x20);
	Int conditionIndex = g->findConditionIndex();
	Int placeIndex = g->findClosestFreeGarrisonPointIndex(conditionIndex, targetPos);
	if (placeIndex == GARRISON_INDEX_INVALID)
		return false;
	sourcePos->set(&m_garrisonPoint[conditionIndex][placeIndex]);
	return true;
}
