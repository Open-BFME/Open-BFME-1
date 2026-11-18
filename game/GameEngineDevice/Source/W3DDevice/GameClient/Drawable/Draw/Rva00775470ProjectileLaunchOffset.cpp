// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
// readable body of ?getProjectileLaunchOffset@Rva00775470ModelDraw@@UBE_NABV?$BitFlags@$0HF@@@W4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@4@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
//
// 0x00775470, 599 bytes (ret 0x1C): the model draw's getProjectileLaunchOffset.
// ObjectDrawInterface slot 6 of the W3DModelDraw family vtables (the
// symbols.csv pin, nine anchors) routes through ILT 0x000117DE here, the slot
// Zero Hour's ObjectDrawInterface gives getProjectileLaunchOffset; the seven
// stack arguments and the body are the Zero Hour twin. The decoration is not
// proven: tools/ilt_oracle.py contradicts W3DModelDraw (and
// W3DModelDrawModuleData::findBestInfo at 0x00765B70) for every access, const
// and BitFlags size tried, so the class keeps the address.
//
// BFME differences: the weapon barrels come from a second condition lookup
// on the module data (0x00765DC0 via ILT 0x0000CE5F), which validateStuff
// also receives with the drawable's bone record (Drawable +0x2F0);
// getPristineBonePositions takes a sixth argument; the turret rotation of the
// launch matrix and the turret bone lookups are gone (the turret arguments
// are only cleared).
//
// Layout: the receiver is the ObjectDrawInterface subobject at +0x10, so the
// module data (+0x08) and drawable (+0x0C) sit at -8 and -4. Module data
// extra public bones +0x30, attach-to-drawable bone +0x40; ModelConditionInfo
// weapon barrel vectors +0x7C (12 bytes each), barrel element 0x3C bytes with
// the projectile offset matrix at +0x0C; Drawable orientation +0x44.

#include "vector3.h"
#include "matrix3d.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../../GameEngine/Include/Common/ScalarTypes.h"



#define NULL 0

#include "../../../../../../GameEngine/Include/Common/Enums/WeaponSlotType.h"
enum WhichTurretType { TURRET_INVALID = -1 };

template <int NUMBITS> class BitFlags;
typedef BitFlags<117> ModelConditionFlags;

class RenderObjClass;
class AsciiString;

namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}
typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVec;

// StringBase<char>'s buffer header: refcount, length, capacity, data.
struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

class BfmeAsciiView
{
public:
	Bool isNotEmpty() const { return m_data != NULL && m_data->m_length != 0; }
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	const BfmeAsciiHeader *m_data;
};

// The bone record validateStuff takes (Rva00774AA0.cpp).
struct Rva00774AA0DrawableBones;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct WeaponBarrelInfo
{
	char m_unmodelled000[0x0c];
	Matrix3D m_projectileOffsetMtx;					// +0x0C
};

// STLport vector<WeaponBarrelInfo> storage: start, finish, end of storage.
class WeaponBarrelInfoVec
{
public:
	Bool empty() const { return m_start == m_finish; }
	unsigned int size() const { return m_finish - m_start; }
	const WeaponBarrelInfo &operator[](Int n) const { return m_start[n]; }
private:
	WeaponBarrelInfo *m_start;
	WeaponBarrelInfo *m_finish;
	WeaponBarrelInfo *m_endOfStorage;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	void validateStuff(RenderObjClass *robj, Real scale, const AsciiStringVec &extraPublicBones,
		const ModelConditionInfo *barrels, const Rva00774AA0DrawableBones &bones) const;

	char m_unmodelled000[0x7c];
	WeaponBarrelInfoVec m_weaponBarrelInfoVec[1];			// +0x7C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDrawModuleData
{
public:
	const ModelConditionInfo *findBestInfo(const ModelConditionFlags &c) const;
	const ModelConditionInfo *rva00765DC0(const ModelConditionFlags &c) const;

	char m_unmodelled000[0x30];
	unsigned char m_extraPublicBones[0x0c];				// +0x30, vector<AsciiString>
	char m_unmodelled03c[0x40 - 0x3c];
	BfmeAsciiView m_attachToDrawableBone;				// +0x40

	const AsciiStringVec &getExtraPublicBones() const { return *(const AsciiStringVec *)m_extraPublicBones; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Real getScale(void) const;
	Real getOrientation(void) const { return m_orientation; }
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex, Coord3D *positions,
		Matrix3D *transforms, Int maxBones, Int flags) const;
	const Rva00774AA0DrawableBones &getBones(void) const { return *m_bones; }

private:
	char m_unmodelled000[0x44];
	Real m_orientation;						// +0x44
	char m_unmodelled048[0x2f0 - 0x48];
	Rva00774AA0DrawableBones *m_bones;				// +0x2F0
};

class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
protected:
	virtual void crc(void *xfer) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module : public MemoryPoolObject, public Snapshot
{
protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
private:
	const ModuleData *m_moduleData;					// +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class DrawableModule : public Module
{
protected:
	Drawable *getDrawable() const { return m_drawable; }
private:
	Drawable *m_drawable;						// +0x0C
};

class DrawModule : public DrawableModule
{
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class ObjectDrawInterface
{
public:
	BFME_VIRTUAL_SLOT(0) BFME_VIRTUAL_SLOT(1) BFME_VIRTUAL_SLOT(2)
	BFME_VIRTUAL_SLOT(3) BFME_VIRTUAL_SLOT(4) BFME_VIRTUAL_SLOT(5)
	virtual Bool getProjectileLaunchOffset(const ModelConditionFlags &condition, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D *launchPos, WhichTurretType tur, Coord3D *turretRotPos,
		Coord3D *turretPitchPos) const = 0;		// slot 6
};

#undef BFME_VIRTUAL_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class Rva00775470ModelDraw : public DrawModule, public ObjectDrawInterface
{
public:
	virtual Bool getProjectileLaunchOffset(const ModelConditionFlags &condition, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D *launchPos, WhichTurretType tur, Coord3D *turretRotPos,
		Coord3D *turretPitchPos) const;

protected:
	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const
	{
		return (const W3DModelDrawModuleData *)getModuleData();
	}
};

static inline void zeroCoord(Coord3D *c)
{
	c->x = 0.0f; c->y = 0.0f; c->z = 0.0f;
}

Bool Rva00775470ModelDraw::getProjectileLaunchOffset(
	const ModelConditionFlags& condition,
	WeaponSlotType wslot,
	Int specificBarrelToUse,
	Matrix3D* launchPos,
	WhichTurretType tur,
	Coord3D* turretRotPos,
	Coord3D* turretPitchPos
) const
{
	const W3DModelDrawModuleData* d = getW3DModelDrawModuleData();
	const ModelConditionInfo* stateToUse = d->findBestInfo(condition);
	const ModelConditionInfo* barrelState = d->rva00765DC0(condition);
	if (!stateToUse)
	{
		return false;
	}

	stateToUse->validateStuff(NULL, getDrawable()->getScale(), d->getExtraPublicBones(),
		barrelState, getDrawable()->getBones());

	Coord3D techOffset;
	zeroCoord(&techOffset);
	// must use pristine bone here since the result is used by logic
	Matrix3D pivot;
	if (d->m_attachToDrawableBone.isNotEmpty() &&
			getDrawable()->getPristineBonePositions( d->m_attachToDrawableBone.str(), 0, NULL, &pivot, 1, 0 ) == 1)
	{
		pivot.Pre_Rotate_Z(getDrawable()->getOrientation());
		techOffset.x = pivot.Get_X_Translation();
		techOffset.y = pivot.Get_Y_Translation();
		techOffset.z = pivot.Get_Z_Translation();
	}

	const WeaponBarrelInfoVec& wbvec = barrelState->m_weaponBarrelInfoVec[wslot];
	if( wbvec.empty() )
	{
		// Can't find the launch pos, but they might still want the other info they asked for
		launchPos = NULL;
	}
	else
	{
		if (specificBarrelToUse < 0 || specificBarrelToUse >= wbvec.size())
			specificBarrelToUse = 0;

		if (launchPos)
		{
			*launchPos = wbvec[specificBarrelToUse].m_projectileOffsetMtx;
			launchPos->Adjust_Translation( Vector3( techOffset.x, techOffset.y, techOffset.z ) );
		}
	}

	if (turretRotPos)
		zeroCoord(turretRotPos);
	if (turretPitchPos)
		zeroCoord(turretPitchPos);

	return launchPos ? true : false;// return if LaunchPos is valid or not
}
