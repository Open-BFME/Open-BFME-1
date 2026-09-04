// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME: SpecialAbilityUpdate::initLaser, retail 0x002A7010.
// The BFME LaserUpdate interface takes the four-argument positional form;
// this is the BFME-era twin of the Zero Hour helper.

typedef bool Bool;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

extern const char g_emptyString[];

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data + 1)
			: g_emptyString;
	}

private:
	BfmeAsciiStringData *m_data;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable;
class ClientUpdateModule;

class ClientUpdateModule
{
};

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);
};

struct Rva0087DC00Vec
{
	int x;
	int y;
	int z;
};

class Rva0087DC00
{
public:
	void get(Rva0087DC00Vec *out);
};

class Matrix3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
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
	virtual Drawable *getDrawable();

	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const unsigned char *>(this) + 0x38);
	}

	Rva0087DC00 &getGeometryInfo()
	{
		return *reinterpret_cast<Rva0087DC00 *>(
			reinterpret_cast<unsigned char *>(this) + 0xac);
	}

	Bool getSingleLogicalBonePosition(const char *boneName,
		Coord3D *position, Matrix3D *transform) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate : public ClientUpdateModule
{
public:
	void initLaser(const Object *parent, const Coord3D *start,
		const Coord3D *end, Int sizeDeltaFrames);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1e0];
	unsigned char m_unmodelled_1e0[0x1e4 - 0x1e0];
	AsciiString m_specialObjectAttachToBoneName;
};

class SpecialAbilityUpdate
{
public:
	Bool initLaser(Object *specialObject, Object *target);

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
};

typedef void (__fastcall *SpecialAbilityCleanupCall)(SpecialAbilityUpdate *);
extern void j_000434c3();

// ?initLaser@SpecialAbilityUpdate@@QAE_NPAVObject@@0@Z
Bool SpecialAbilityUpdate::initLaser(Object *specialObject, Object *target)
{
	SpecialAbilityUpdateModuleData *data = m_moduleData;
	static NameKeyType key_LaserUpdate =
		TheNameKeyGenerator->nameToKey("LaserUpdate");
	Drawable *draw = specialObject->getDrawable();
	if (!draw)
	{
		((SpecialAbilityCleanupCall)j_000434c3)(this);
		return false;
	}

	LaserUpdate *update = (LaserUpdate *)draw->findClientUpdateModule(
		key_LaserUpdate);
	if (!update)
	{
		((SpecialAbilityCleanupCall)j_000434c3)(this);
		return false;
	}

	Coord3D startPos;
	if (!m_object->getSingleLogicalBonePosition(
		data->m_specialObjectAttachToBoneName.str(), &startPos, 0))
	{
		startPos.set(m_object->getPosition());
	}

	Coord3D endPos;
	if (target)
	{
		target->getGeometryInfo().get(
			(Rva0087DC00Vec *)&endPos);
		endPos.x += target->getPosition()->x;
		endPos.y += target->getPosition()->y;
		endPos.z += target->getPosition()->z;
	}
	else
	{
		endPos = startPos;
	}

	update->initLaser(0, &startPos, &endPos, 0);
	return true;
}
