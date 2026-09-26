// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &direction) const;

	unsigned char m_pad00[0x38];
	Coord3D m_cachedPos;
};

class BfmeFacingView
{
public:
	bool bfmeIsPositionAhead(const Thing *origin, const Coord3D *position) const;

private:
	unsigned char m_pad00[8];
	const Thing *m_thing;
};

bool BfmeFacingView::bfmeIsPositionAhead(
	const Thing *origin, const Coord3D *position) const
{
	Coord3D positionOffset;
	positionOffset.x = position->x;
	positionOffset.y = position->y;
	const Thing *facingThing = m_thing;
	positionOffset.x -= origin->m_cachedPos.x;
	positionOffset.y -= origin->m_cachedPos.y;
	if (facingThing != 0)
	{
		Coord3D facingDirection;
		facingThing->getUnitDirectionVector2D(facingDirection);
		if (*(volatile float *)&positionOffset.x * facingDirection.x
			+ *(volatile float *)&positionOffset.y * facingDirection.y < 0.0f)
			return true;
	}
	return false;
}
