// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: BaseUpgrade::upgradeImplementation -- retail 0x002D3970, 578 bytes.
//
// Identity: slot 9 (+0x24) of the vtable at VA 0x010CBFD8 is ILT 0x00044FCB,
// which jumps to 0x002D3970. ??0BaseUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z at
// 0x002D3800 installs that vtable into its second base subobject
// (`mov [esi+0x10], 0x10cbfd8` at +0x21), so this body is the BaseUpgrade
// override reached through that subobject -- which is why it reads its module
// data at this-0xc and its Object at this-8. (The primary ??_7BaseUpgrade@@6B@
// at VA 0x010CC0EC, installed at +0x14 of the same ctor, does NOT hold this
// slot; do not cite it for this identity.)
//
// It builds the module data's building template at a pristine bone of the
// owning object and hands the result to the body behind ILT 0x0003AA8F, which
// is what a base upgrade does.
//
// Module data layout, read straight off retail: the vptr occupies +0x00, the
// building-template name is at +0x70 (`lea ecx, [ebx+0x70]` at +0x50), the
// placement-prefix string at +0x74 (`mov ebx, [ebx+0x74]` at +0xa8) and the
// placement index at +0x78 (`mov esi, [ebx+0x78]` at +0xa5).
//
// Coord3D::set(Real,Real,Real) is the Zero Hour spelling
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h:385);
// passing the three coordinates by value through it is what makes MSVC 7.1 keep y and z
// on the x87 stack (fld/fstp) while x stays in eax for the cross-jumped `mov [esp+0x14],eax`
// tail at +0x192 -- the residue every earlier attempt on this address was left with.

#include <bitset>

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// Retail's empty-string sentinel: `mov ebx, 0x107388b` at +0xb4 is a DIR32
// relocation to ?Rva006A16B0Empty@@3PADA (reverse/symbols.csv, 0x0107388B).
extern char Rva006A16B0Empty[];

// Retail inlines the whole of AsciiString::str() here -- +0xa8..+0xb9 is
// `mov ebx,[ebx+0x74]; test ebx,ebx; je; add ebx,8; jmp; mov ebx,0x107388b`.
// ascii_string.h's str() forwards to StringBase<char>::str(), which has an
// out-of-line body, so calling it would emit a call where retail has the test
// and the add. Read the one data pointer the header's layout puts at +0x0 and
// do the +8 to the Header's data[] in line, which is what retail emitted.
static const char *inlineStr(const AsciiString &s)
{
	const char *text = *reinterpret_cast<const char *const *>(&s);
	return text ? text + 8 : Rva006A16B0Empty;
}

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
	// `mov eax, [ebp+0x230]` at +0x19f, where ebp is the controlling player.
	// tools/name_oracle.py --class Player --offset 0x230 has no witness for
	// this field, so the name stays offset-derived. Zero Hour's
	// Player::getDefaultTeam (reference/CnC_Generals_Zero_Hour/GeneralsMD/
	// Code/GameEngine/Include/Common/Player.h) is the likely identity; that is
	// a lead, not a claim this TU makes.
	__forceinline Team *team230() const
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

// Retail's tail call, at +0x202: `push esi; push edi; mov ecx, ebp;
// call 0x43aa8f` -- ILT 0x0003AA8F, which jumps to 0x000D4770. That is a
// thiscall on the controlling player (ecx) with the owning object and the new
// structure on the stack. The ledger already owns the body at the other end
// under an address-derived name -- reverse/functions.csv:
// `?rva000D4770InterfaceDispatch@@YGXPAVThing@@PAVObject@@@Z,,0x000D4770,91,
// Code/GameEngine/Source/Common/Rva000D4770InterfaceDispatch.cpp,matched` --
// and that row spells it __stdcall with no receiver, which is consistent with
// the body (it reads both operands off the stack and never touches ecx). So
// this TU makes no claim about the callee's identity beyond its address: the
// member-pointer pun below is only the mechanism that reproduces retail's
// `mov ecx, ebp` plus the two pushes, and the name is the address.
//
// Zero Hour has Player::onStructureCreated(Object *builder, Object *structure)
// at reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/
// Common/Player.h:459, which fits the shape exactly. That is evidence for a
// future rename of 0x000D4770 -- one
// that would have to settle the ledger row's __stdcall spelling too -- not an
// identity asserted here.
typedef void (Player::*Rva000D4770Call)(Object *builder, Object *structure);

union Rva000D4770CallBits
{
	void (*raw)();
	Rva000D4770Call member;
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
	const char *prefix = inlineStr(moduleData->m_placementPrefix);
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

	Team *team230 = player->team230();
	ObjectStatusMaskType status;
	Object *newObject = TheThingFactory->newObject(
		thingTemplate, team230, status, 0);
	newObject->setProducer(object);
	newObject->setBuilder(object);
	newObject->setPosition(reinterpret_cast<const Coord3D *>(&position));
	reinterpret_cast<Thing *>(newObject)->setOrientation(orientation);
	TheAI->m_pathfinder->addObjectToPathfindMap(newObject);
	Rva000D4770CallBits call;
	call.raw = j_0003aa8f;
	(player->*call.member)(object, newObject);
}
