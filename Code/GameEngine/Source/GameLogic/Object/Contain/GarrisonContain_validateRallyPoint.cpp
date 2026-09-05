// cl: /DNDEBUG /MD /EHsc
// GarrisonContain::validateRallyPoint at 0x0021E3B0.
// ZH twin: GarrisonContain::validateRallyPoint. FindPositionOptions is a
// free cdecl around the 0x00026C4C thunk (body 0x001AF610). Object
// position at +0x38, bounding-circle radius at +0xBC, exit rally at
// this+0x9A8, m_rallyValid at +0x9B6.

typedef unsigned char Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}

	unsigned int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

enum
{
	FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 8
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	float getBoundingCircleRadius() const
	{
		return *(const float *)((const char *)this + 0xBC);
	}
};

bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);

class GarrisonContain
{
public:
	Object *getObject() const { return m_object; }

protected:
	void validateRallyPoint();

private:
	void *m_vtbl;
	void *m_moduleData;
	Object *m_object;
	char m_pad[0x99C];
	Coord3D m_exitRallyPoint;
	char m_padRally[2];
	Bool m_rallyValid;
};

void GarrisonContain::validateRallyPoint()
{
	if (m_rallyValid == 1)
	{
		Coord3D result;
		FindPositionOptions options;
		options.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;
		options.minRadius = 0.0f;
		options.maxRadius = 0.0f;
		options.ignoreObject = getObject();
		options.relationshipObject = getObject();
		if (findPositionAround(&m_exitRallyPoint, &options, &result) == 0)
			m_rallyValid = 0;
	}

	if (m_rallyValid == 0)
	{
		FindPositionOptions options;
		options.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;
		options.minRadius = getObject()->getBoundingCircleRadius();
		options.maxRadius = options.minRadius * 1.8f;
		options.ignoreObject = getObject();
		options.relationshipObject = getObject();
		m_rallyValid = findPositionAround(getObject()->getPosition(), &options, &m_exitRallyPoint);
	}
}
