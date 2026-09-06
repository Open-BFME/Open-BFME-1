// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of CameraShakerVolumeFXNugget::doFXPos
// (CameraShakerVolumeFXNugget_doFXPos_Thunk.cpp); positional dispatch sibling of
// LightPulseFXNugget::doFXObj (LightPulseFXNugget_doFXObj_Thunk.cpp), BFME's four-arg
// doFXPos (no overrideRadius) per reference/CnC_Generals_Zero_Hour FXList.cpp:344.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

struct RGBColor
{
	float red, green, blue;
};

class Matrix3D;

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

class LightPulseFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const void *, const void *) const;

private:
	unsigned char m_unmodelled[0xB0];
	RGBColor m_color;
	float m_radius;
	float m_boundingCirclePct;
	unsigned int m_increaseFrames;
	unsigned int m_decreaseFrames;
};

// ?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void LightPulseFXNugget::doFXPos(const Coord3D *primary,
	const Matrix3D *, float, const Coord3D *) const
{
	if (primary)
		TheDisplay->createLightPulse(primary, &m_color, 1.0f, m_radius,
			m_increaseFrames, m_decreaseFrames);
}
