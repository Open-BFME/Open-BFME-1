// cl: /DNDEBUG /MD /EHsc
typedef float Real;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class Matrix3D;

// This view models only the Object offsets read by these effects.
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	unsigned char m_unreconstructed00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed44[0x78];
	Real m_boundingCircleRadius;
};

class Display
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
	virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
	virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
	virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C();
	virtual void v90(); virtual void v94();
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color,
		float opacity, float radius, unsigned int increaseFrames, unsigned int decreaseFrames);
};

extern Display *TheDisplay;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unreconstructed04[0xB0];
};

class LightPulseFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	RGBColor m_color;
	Real m_radius;
	Real m_boundingCirclePct;
	UnsignedInt m_increaseFrames;
	UnsignedInt m_decreaseFrames;
};

// ?doFXObj@LightPulseFXNugget@@UBEXPBVObject@@0@Z
void LightPulseFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		Real radius = m_radius;
		if (m_boundingCirclePct > 0.0f)
		{
			radius = primary->getBoundingCircleRadius()
				* m_boundingCirclePct;
		}

		TheDisplay->createLightPulse(primary->getPosition(), &m_color, 1.0f,
			radius, m_increaseFrames, m_decreaseFrames);
	}
}

// ?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void LightPulseFXNugget::doFXPos(const Coord3D *primary,
	const Matrix3D *, float, const Coord3D *) const
{
	if (primary)
		TheDisplay->createLightPulse(primary, &m_color, 1.0f, m_radius,
			m_increaseFrames, m_decreaseFrames);
}
