// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc
// Retail INI table 0x00CF2B28 supplies the descriptive field names and units.
// Integer slots retain the parsed float bit patterns for the existing dispatch ABI.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class Matrix3D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unmodelled[0x38];
	Coord3D m_position;
};

class TacticalView
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
	virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C();
	virtual void vA0();
	virtual void addCameraShakerVolume(const Coord3D *, int, int, int);
};

extern TacticalView *TheTacticalView;

class CameraShakerVolumeFXNugget
{
public:
	virtual void v00();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unmodelled[0xBC];
	int m_radius;
	int m_durationSeconds;
	int m_amplitudeDegrees;
};

// ?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void CameraShakerVolumeFXNugget::doFXPos(const Coord3D *position,
	const Matrix3D *, float, const Coord3D *) const
{
	if (position)
		TheTacticalView->addCameraShakerVolume(position, m_radius, m_durationSeconds, m_amplitudeDegrees);
}

// ?doFXObj@CameraShakerVolumeFXNugget@@UBEXPBVObject@@0@Z
void CameraShakerVolumeFXNugget::doFXObj(const Object *object, const Object *) const
{
	if (object)
		TheTacticalView->addCameraShakerVolume(&object->m_position,
			m_radius, m_durationSeconds, m_amplitudeDegrees);
}
