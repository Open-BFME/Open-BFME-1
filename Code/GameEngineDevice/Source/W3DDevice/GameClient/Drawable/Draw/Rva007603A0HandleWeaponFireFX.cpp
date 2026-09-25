// candidate for retail 0x007603A0 (478B), currently ?d_007603a0@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/w3dmodeldraw /Ireference/shims/asciistring8 /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "WW3D2/RendObj.h"

class FXList
{
public:
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, Real, const Coord3D *);
};

class FlaggedReferenceSource;

class FlaggedReferenceApplicator
{
public:
	void apply(FlaggedReferenceSource *, unsigned char);
};

struct Rva007603A0WeaponBarrelInfo
{
	Int m_recoilBone;
	Int m_fxBone;
	Int m_muzzleFlashBone;
	unsigned char m_unreconstructed[0x30];
};

struct Rva007603A0BarrelVector
{
	Rva007603A0WeaponBarrelInfo *m_begin;
	Rva007603A0WeaponBarrelInfo *m_end;
	Rva007603A0WeaponBarrelInfo *m_capacity;

	Bool empty(void) const { return m_begin == m_end; }
	unsigned int size(void) const { return (unsigned int)(m_end - m_begin); }
	Rva007603A0WeaponBarrelInfo &operator[](Int index) const { return m_begin[index]; }
};

struct Rva007603A0ModelConditionInfo
{
	unsigned char m_unreconstructed[0x7c];
	Rva007603A0BarrelVector m_weaponBarrelInfoVec[4];
	unsigned char m_validStuff;
};

struct Rva007603A0RecoilInfo
{
	Int m_state;
	Real m_recoilShift;
	Real m_recoilRate;
};

struct Rva007603A0RecoilVector
{
	Rva007603A0RecoilInfo *m_begin;
	Rva007603A0RecoilInfo *m_end;
	Rva007603A0RecoilInfo *m_capacity;

	Rva007603A0RecoilInfo &operator[](Int index) const { return m_begin[index]; }
};

struct Rva007603A0DrawableView
{
	unsigned char m_unreconstructed[0xfc];
	Object *m_object;
};

struct Rva007603A0ModuleDataView
{
	unsigned char m_unreconstructed[0x54];
	Real m_initialRecoil;
};

class Rva007603A0
{
public:
	Bool handleWeaponFireFX(WeaponSlotType wslot, Int specificBarrelToUse,
		const FXList *fxl, Real weaponSpeed, const Coord3D *victimPos);

private:
	unsigned char m_unreconstructed00[8];
	Rva007603A0ModelConditionInfo *m_curState;
	unsigned char m_unreconstructed0c[0x1c];
	RenderObjClass *m_renderObject;
	unsigned char m_unreconstructed2c[0x74];
	Rva007603A0RecoilVector m_weaponRecoilInfoVec[4];
};

Bool Rva007603A0::handleWeaponFireFX(WeaponSlotType wslot, Int specificBarrelToUse,
	const FXList *fxl, Real weaponSpeed, const Coord3D *victimPos)
{
	if (!m_curState || !(m_curState->m_validStuff & 8))
		return false;

	const Rva007603A0BarrelVector &wbvec = m_curState->m_weaponBarrelInfoVec[wslot];
	if (wbvec.empty())
		return false;

	Bool handled = false;
	if (specificBarrelToUse < 0 || specificBarrelToUse > wbvec.size())
		specificBarrelToUse = 0;

	const Rva007603A0WeaponBarrelInfo &info = wbvec[specificBarrelToUse];
	if (fxl)
	{
		if (info.m_fxBone && m_renderObject)
		{
			Rva007603A0DrawableView *drawable =
				*reinterpret_cast<Rva007603A0DrawableView **>(reinterpret_cast<unsigned char *>(this) - 4);
			const Object *logicObject = drawable->m_object;
			if (!m_renderObject->Is_Hidden() || logicObject == NULL)
			{
				Matrix3D mtx = m_renderObject->Get_Bone_Transform(info.m_fxBone);
				Coord3D pos;
				pos.x = mtx.Get_X_Translation();
				pos.y = mtx.Get_Y_Translation();
				pos.z = mtx.Get_Z_Translation();
				FXList::doFXPos(fxl, &pos, &mtx, weaponSpeed, victimPos);
			}
			else
			{
				Coord3D pos = *logicObject->getPosition();
				FXList::doFXPos(fxl, &pos, logicObject->getTransformMatrix(), weaponSpeed, victimPos);
			}
			handled = true;
		}
	}

	if (info.m_recoilBone || info.m_muzzleFlashBone)
	{
		Rva007603A0RecoilInfo &recoil = m_weaponRecoilInfoVec[wslot][specificBarrelToUse];
		if (recoil.m_state == 0)
		{
			recoil.m_state = 1;
			Rva007603A0ModuleDataView *moduleData =
				*reinterpret_cast<Rva007603A0ModuleDataView **>(reinterpret_cast<unsigned char *>(this) - 8);
			recoil.m_recoilRate = moduleData->m_initialRecoil;
			if (info.m_muzzleFlashBone != 0)
			{
				FlaggedReferenceApplicator *applicator =
					reinterpret_cast<FlaggedReferenceApplicator *>(const_cast<Rva007603A0WeaponBarrelInfo *>(&info));
				applicator->apply(reinterpret_cast<FlaggedReferenceSource *>(m_renderObject), 0);
			}
		}
	}

	return handled;
}
