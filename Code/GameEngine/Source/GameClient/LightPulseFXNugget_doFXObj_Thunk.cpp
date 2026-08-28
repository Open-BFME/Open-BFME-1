// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of BFME's object-bound light-pulse FX dispatch.

typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const
	{
		return m_boundingCircleRadius;
	}

private:
	Real m_boundingCircleRadius;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return m_geometryInfo;
	}

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x78];
	GeometryInfo m_geometryInfo;
};

class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color,
		Real opacity, Real radius, UnsignedInt increaseFrames, UnsignedInt decreaseFrames);
};

extern Display *TheDisplay;

class LightPulseFXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad[0xB0];
	RGBColor m_color;
	Real m_radius;
	Real m_boundingCirclePct;
	UnsignedInt m_increaseFrames;
	UnsignedInt m_decreaseFrames;
};

void LightPulseFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		Real radius = m_radius;
		if (m_boundingCirclePct > 0.0f)
		{
			radius = primary->getGeometryInfo().getBoundingCircleRadius()
				* m_boundingCirclePct;
		}

		TheDisplay->createLightPulse(primary->getPosition(), &m_color, 1.0f,
			radius, m_increaseFrames, m_decreaseFrames);
	}
}
