// ?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
// partial score=0.9 date=2026-08-28
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of Laser's positional dispatch.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;
class Object;
class ThingTemplate;

class ClientUpdateModule
{
};

class AsciiString
{
private:
	char *m_text;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class BFMEThingFactory : public ThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *thingTemplate,
		DrawableStatus status, Int drawableID);
};

class LaserUpdate : public ClientUpdateModule
{
public:
	void initLaser(const Object *parent, const Coord3D *start,
		const Coord3D *end, Int sizeDeltaFrames);
};

class LaserFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float,
		const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unmodelled[0xB0];
	AsciiString m_laserName;
	bool m_laserBackwards;
	unsigned char m_padding[3];
	Coord3D m_targetPositionOffsetFallback;
};

// ?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void LaserFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float,
	const Coord3D *secondary) const
{
	if (primary)
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(m_laserName);
		Drawable *draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable(
			thingTemplate, DRAWABLE_STATUS_NONE, -1);
		if (draw)
		{
			static NameKeyType key_LaserUpdate =
				TheNameKeyGenerator->nameToKey("LaserUpdate");
			LaserUpdate *update =
				(LaserUpdate *)draw->findClientUpdateModule(key_LaserUpdate);
			if (update)
			{
				Coord3D position;
				if (!secondary)
				{
					position.x = primary->x;
					position.y = primary->y;
					position.z = primary->z;
					position.x += m_targetPositionOffsetFallback.x;
					position.y += m_targetPositionOffsetFallback.y;
					position.z += m_targetPositionOffsetFallback.z;

					if (!m_laserBackwards)
					{
						update->initLaser(0, primary, &position, 0);
					}
					else
					{
						update->initLaser(0, &position, primary, 0);
					}
				}
				else
				{
					update->initLaser(0, primary, secondary, 0);
				}
			}
		}
	}
}
