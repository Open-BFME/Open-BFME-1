// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CrushEnum
{
	TOTAL_CRUSH,
	BACK_END_CRUSH,
	FRONT_END_CRUSH,
	NO_CRUSH
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual bool getFrontCrushed() const = 0;
	virtual bool getBackCrushed() const = 0;
};

class GeometryInfo
{
public:
	Real getMajorRadius() const
	{
		return m_majorRadius;
	}

private:
	char m_padding[0x10];
	Real m_majorRadius;
};

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((char *)this + 0x200);
	}

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((char *)this + 0x38);
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return *(const GeometryInfo *)((char *)this + 0xAC);
	}
};

// ?crushLocationCheck@@YA?AW4CrushEnum@@PAVObject@@0@Z
__declspec(noinline) static CrushEnum crushLocationCheck(Object *crusherObject,
	Object *victimObject)
{
	if ((crusherObject == 0) || (victimObject == 0))
		return NO_CRUSH;

	bool frontCrushed = victimObject->getBodyModule()->getFrontCrushed();
	bool backCrushed = victimObject->getBodyModule()->getBackCrushed();
	const Coord3D *otherDir = victimObject->getUnitDirectionVector2D();
	const Coord3D *pos = crusherObject->getPosition();
	const Coord3D *otherPos = victimObject->getPosition();

	Real crushPointOffsetDistance = victimObject->getGeometryInfo().getMajorRadius() * 0.5;

	Coord3D crushPointOffset;
	crushPointOffset.x = otherDir->x * crushPointOffsetDistance;
	crushPointOffset.y = otherDir->y * crushPointOffsetDistance;
	crushPointOffset.z = 0;

	Coord3D comparisonCoord;
	Real dx, dy;

	CrushEnum retval = NO_CRUSH;
	Real bestDist = 99999;

	if (!frontCrushed && !backCrushed)
	{
		comparisonCoord = *otherPos;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		retval = TOTAL_CRUSH;
		bestDist = dist;
	}

	if (!frontCrushed)
	{
		comparisonCoord = *otherPos;
		comparisonCoord.x += crushPointOffset.x;
		comparisonCoord.y += crushPointOffset.y;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		if (dist < bestDist)
		{
			if (backCrushed)
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = FRONT_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	if (!backCrushed)
	{
		comparisonCoord = *otherPos;
		comparisonCoord.x -= crushPointOffset.x;
		comparisonCoord.y -= crushPointOffset.y;

		dx = comparisonCoord.x - pos->x;
		dy = comparisonCoord.y - pos->y;
		Real dist = (Real)(dx * dx + dy * dy);

		if (dist < bestDist)
		{
			if (frontCrushed)
			{
				retval = TOTAL_CRUSH;
				bestDist = dist;
			}
			else
			{
				retval = BACK_END_CRUSH;
				bestDist = dist;
			}
		}
	}

	return retval;
}

__declspec(noinline) CrushEnum forceCrushLocationCheck(Object *crusherObject,
	Object *victimObject)
{
	return crushLocationCheck(crusherObject, victimObject);
}
