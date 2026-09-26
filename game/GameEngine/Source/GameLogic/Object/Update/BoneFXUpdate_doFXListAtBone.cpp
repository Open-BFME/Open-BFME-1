// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BoneFXUpdate::doFXListAtBone, retail 0x00287F80 / 135B.
// The standalone declarations preserve the BFME object and module offsets.

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
};

struct DamageInfo
{
	unsigned char m_pad[0x10];
	Int m_damageType;
};

class BodyModule
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class Object
{
public:
	BodyModule *getBodyModule() const
	{
		return *reinterpret_cast<BodyModule *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x200);
	}

	void convertBonePosToWorldPos(const Coord3D *, const Matrix3D *, Coord3D *, Matrix3D *) const;
};

struct BoneFXUpdateModuleData
{
	unsigned char m_pad[8];
	unsigned int m_damageFXTypes;
};

static Bool getDamageTypeFlag(unsigned int flags, Int damageType)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

class BoneFXUpdate
{
protected:
	void doFXListAtBone(const FXList *, const Coord3D *);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void resolveBoneLocations();

	private:
	const BoneFXUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x62c - 0x0c];
	Int m_curBodyState;
	Bool m_bonesResolved[4];
};

// ?doFXListAtBone@BoneFXUpdate@@IAEXPBVFXList@@PBUCoord3D@@@Z
void BoneFXUpdate::doFXListAtBone(const FXList *fxList, const Coord3D *bonePosition)
{
	if (!m_bonesResolved[m_curBodyState])
		resolveBoneLocations();

	const BoneFXUpdateModuleData *data = m_moduleData;
	const DamageInfo *lastDamageInfo = m_object->getBodyModule()->getLastDamageInfo();
	if (lastDamageInfo != 0 &&
		!getDamageTypeFlag(data->m_damageFXTypes, lastDamageInfo->m_damageType))
		return;

	Coord3D newPos;
	m_object->convertBonePosToWorldPos(bonePosition, 0, &newPos, 0);
	if (fxList != 0 && !const_cast<FXList *>(fxList)->bfmeIsBlocked())
		fxList->doFXPos(&newPos, 0, 0.0f, 0);
}
