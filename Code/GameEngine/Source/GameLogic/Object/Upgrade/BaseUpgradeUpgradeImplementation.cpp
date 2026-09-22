// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: BaseUpgrade::upgradeImplementation -- retail 0x002D3970, 578 bytes.
//
// Identity: the body reads its module data at this-0xc and its Object at this-8,
// the BaseUpgrade layout proven by the matched neighbours ??_GBaseUpgrade@@MAEPAXI@Z
// at 0x002D3900 and ??0BaseUpgradeModuleData@@QAE@XZ at 0x002D3C50 (vtable 0x00CCC0EC).
// It builds the module data's building template at a pristine bone of the owning
// object and hands the result to Player::onStructureCreated, which is what a base
// upgrade does.
//
// Coord3D::set(Real,Real,Real) is the Zero Hour spelling
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h:385);
// passing the three coordinates by value through it is what makes MSVC 7.1 keep y and z
// on the x87 stack (fld/fstp) while x stays in eax for the cross-jumped `mov [esp+0x14],eax`
// tail at +0x192 -- the residue every earlier attempt on this address was left with.

#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	~Coord3D() {}

	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	Real x;
	Real y;
	Real z;
};

struct WorldPosition
{
	Real x;
	Real y;
	Real z;
};

class Vector4
{
public:
	Vector4();

	Real X;
	Real Y;
	Real Z;
	Real W;
};

class Matrix3D
{
public:
	Real Get_X_Translation() const { return Row[0].W; }
	Real Get_Y_Translation() const { return Row[1].W; }
	Real Get_Z_Translation() const { return Row[2].W; }
	Real Get_Z_Rotation() const;

private:
	Vector4 Row[3];
};

struct WorldMatrix
{
	Real m[12];
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data + 1) :
			reinterpret_cast<const char *>(0x0107388B);
	}

private:
	BfmeAsciiStringData *m_data;
};

class BaseUpgradeModuleData
{
public:
	virtual ~BaseUpgradeModuleData();

	unsigned char m_pad[0x6c];
	AsciiString m_buildingTemplateName;
	AsciiString m_placementPrefix;
	Int m_placementIndex;
};

class ThingTemplate;
class Team;
class Object;

template <Int NUMBITS>
class BitFlags
{
public:
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class BFMEDrawableBoneQuery
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

class Drawable;

class Thing
{
public:
	__forceinline const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}
	__forceinline const Matrix3D *getTransformMatrix() const
	{
		return &m_transform;
	}
	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
	void setOrientation(Real angle);

private:
	unsigned char m_head[8];
	Matrix3D m_transform;
	Coord3D m_cachedPos;
};

class Player
{
public:
	void onStructureCreated(Object *builder, Object *structure);

	__forceinline Team *getDefaultTeam() const
	{
		return const_cast<Team *>(*reinterpret_cast<Team * const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x230));
	}
};

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
	virtual BFMEDrawableBoneQuery *getDrawable() const;

	Player *getControllingPlayer() const;
	void setProducer(const Object *producer);
	void setBuilder(const Object *builder);
	void setPosition(const Coord3D *position);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thingTemplate, Team *team,
		const ObjectStatusMaskType &status, UnsignedInt unknown);
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
private:
	unsigned char m_pad[0x0c];

public:
	BFMEPathfinderMapShim *m_pathfinder;
};

extern ThingFactory *TheThingFactory;
extern AI *TheAI;
extern void j_0003aa8f();

typedef void (Player::*OnStructureCreatedCall)(Object *builder, Object *structure);

union OnStructureCreatedCallBits
{
	void (*raw)();
	OnStructureCreatedCall member;
};

class BaseUpgrade
{
protected:
	virtual void upgradeImplementation();
};

// ?upgradeImplementation@BaseUpgrade@@MAEXXZ
void BaseUpgrade::upgradeImplementation()
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	BaseUpgradeModuleData *moduleData =
		*reinterpret_cast<BaseUpgradeModuleData **>(self - 0xc);
	Object *object = *reinterpret_cast<Object **>(self - 8);
	if (object == 0)
		return;
	Player *player = object->getControllingPlayer();
	if (player == 0)
		return;

	BFMEDrawableBoneQuery *drawable = object->getDrawable();
	if (drawable == 0)
		return;

	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(
		moduleData->m_buildingTemplateName);
	if (thingTemplate == 0)
		return;

	Coord3D bonePositions[32];
	Matrix3D boneTransforms[32];
	Int placementIndex = moduleData->m_placementIndex;
	const char *prefix = moduleData->m_placementPrefix.str();
	Int boneCount = drawable->getPristineBonePositions(
		prefix, 1, bonePositions, boneTransforms, 32, 0);

	Coord3D position;
	Real orientation;
	WorldMatrix worldTransform;
	if (placementIndex > 0 && placementIndex < boneCount)
	{
		worldTransform.m[0] = 1.0f;
		worldTransform.m[1] = 0.0f;
		worldTransform.m[2] = 0.0f;
		worldTransform.m[3] = 0.0f;
		worldTransform.m[4] = 0.0f;
		worldTransform.m[5] = 1.0f;
		worldTransform.m[6] = 0.0f;
		worldTransform.m[7] = 0.0f;
		worldTransform.m[8] = 0.0f;
		worldTransform.m[9] = 0.0f;
		worldTransform.m[10] = 1.0f;
		worldTransform.m[11] = 0.0f;
		(reinterpret_cast<const Thing *>(object))->convertBonePosToWorldPos(
			0, &boneTransforms[placementIndex], 0,
			reinterpret_cast<Matrix3D *>(&worldTransform));
		position.set(worldTransform.m[3], worldTransform.m[7], worldTransform.m[11]);
		orientation = reinterpret_cast<const Matrix3D *>(&worldTransform)->Get_Z_Rotation();
	}
	else
	{
		const Thing *thing = reinterpret_cast<const Thing *>(object);
		const Coord3D *objectPosition = thing->getPosition();
		position.set(objectPosition->x, objectPosition->y, objectPosition->z);
		orientation = thing->getTransformMatrix()->Get_Z_Rotation();
	}

	Team *defaultTeam = player->getDefaultTeam();
	ObjectStatusMaskType status;
	Object *newObject = TheThingFactory->newObject(
		thingTemplate, defaultTeam, status, 0);
	newObject->setProducer(object);
	newObject->setBuilder(object);
	newObject->setPosition(reinterpret_cast<const Coord3D *>(&position));
	reinterpret_cast<Thing *>(newObject)->setOrientation(orientation);
	TheAI->m_pathfinder->addObjectToPathfindMap(newObject);
	OnStructureCreatedCallBits call;
	call.raw = j_0003aa8f;
	(player->*call.member)(object, newObject);
}
