// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &direction) const;

	unsigned char m_pad00[0x38];
	Coord3D m_position;
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
	Coord3D offset;
	offset.x = position->x;
	offset.y = position->y;
	const Thing *thing = m_thing;
	offset.x -= origin->m_position.x;
	offset.y -= origin->m_position.y;
	if (thing != 0)
	{
		Coord3D direction;
		thing->getUnitDirectionVector2D(direction);
		if (*(volatile float *)&offset.x * direction.x
			+ *(volatile float *)&offset.y * direction.y < 0.0f)
			return true;
	}
	return false;
}
