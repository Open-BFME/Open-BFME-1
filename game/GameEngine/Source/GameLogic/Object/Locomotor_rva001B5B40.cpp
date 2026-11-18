// ?rva001B5B40@Locomotor@@QBE_NPBVThing@@PBUCoord3D@@@Z
// Converted byte-exact (144/144 bytes), wave15 landing.
// Retail RVA 0x001B5B40.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/ScalarTypes.h"

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &direction) const;

	unsigned char m_unmodelled000[0x38];
	Coord3D m_cachedPos;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	unsigned char m_unmodelled000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_unmodelled008[0x68];
	int m_appearance;
	unsigned char m_unmodelled074[0x60];
	int m_canMoveBackward;
};

template <class T>
class Override
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}

	const T *m_overridable;
};

typedef Override<LocomotorTemplate> LocomotorTemplateOverride;

extern const Real g_rva01075350;		// VA 0x01075350, 0.0f

class Locomotor
{
public:
	virtual void slot(void);
	bool rva001B5B40(const Thing *thing, const Coord3D *position) const;

private:
	LocomotorTemplateOverride m_template;
};

// ?rva001B5B40@Locomotor@@QBE_NPBVThing@@PBUCoord3D@@@Z
bool Locomotor::rva001B5B40(const Thing *thing,
	const Coord3D *position) const
{
	Coord3D direction;
	Coord3D offset;

	if (m_template->m_appearance == 1)
	{
		if (m_template->m_canMoveBackward != 0)
		{
			thing->getUnitDirectionVector2D(*(Coord3D *)&direction);

			offset.y = position->y;
			*(volatile Real *)&offset.x = position->x - thing->m_cachedPos.x;
			offset.y -= thing->m_cachedPos.y;
			if ((*(volatile Real *)&direction.y * offset.y)
				+ direction.x * *(volatile Real *)&offset.x
				< g_rva01075350)
				return true;
		}
	}

	return false;
}
