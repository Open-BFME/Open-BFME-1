// ?bfmeContainsRegion@PathfindLayer@@QAEHPBURegion2D@@@Z
// partial score=0.58 date=2026-09-03
// BFME-only bridge-layer region overlap test, retail 0x003FBA10 (110 bytes).

typedef int Bool;
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Region2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Bridge
{
public:
	void getBounds(Region2D *bounds) const;
};

class PathfindLayer
{
public:
	Bool bfmeContainsRegion(const Region2D *region);

private:
	char m_pad00[0x3c];
	Bridge *m_bfmeOther;
};

Bool PathfindLayer::bfmeContainsRegion(const Region2D *region)
{
	Region2D bounds;
	register const Region2D *input = region;
	Bridge *bridge = m_bfmeOther;
	if (bridge == 0)
		return false;
	bridge->getBounds(&bounds);
	if (input->hi.x + 10 <= bounds.lo.x)
		return false;
	if (input->hi.y + 10 <= bounds.lo.y)
		return false;
	if (input->lo.x - 10 >= bounds.hi.x)
		return false;
	if (input->lo.y - 10 >= *(const Int *)((const char *)bridge + 4))
		return false;
	return true;
}
