// ?bfmeGo002BD940@Rva002BD940Owner@@QAEXXZ
// partial score=0.4 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfmekindof /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define BFME_STLP_NODE_ALLOC 1
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/KindOf.h"

// Address-derived: no named caller (ILT-mediated only) and no vtable/string
// proves the owning class, so identity stays opaque per docs/naming_evidence.md.
// The kind-of mask (bit7=STRUCTURE, bit10/11=BFME_HOLE_10/11 per the shim's
// enum comment) plus the getClosestObject/normalize/setPosition shape place
// this in the GiantBird-neighbourhood cluster (0x002BD8B0..0x002BDB30) without
// proving a specific state class.

// Coord3D and Thing are already declared for real via PreRTS.h's include chain
// (Lib/BaseType.h and Common/Thing.h); Thing::setPosition is used through a
// cast below, matching the already-landed GiantBirdAIUpdate.cpp convention.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unreconstructed_00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed_44[0xbc - 0x44];
	float m_unreconstructed_bc;
};

class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *objOther) = 0;
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear);
	virtual bool allow(Object *objOther) { return true; }
private:
	KindOfMaskType m_mustBeSet, m_mustBeClear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc, PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;
extern float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// The owning class/method are unproven (see header comment); +0x8 is the only
// witnessed this-relative field (the brief's evidence pack).
class Rva002BD940Owner
{
public:
	void bfmeGo002BD940();

	unsigned char m_unreconstructed_00[8];
	Object *m_owner008;
};

void Rva002BD940Owner::bfmeGo002BD940()
{
	Object *owner = m_owner008;
	float rawRadius = owner->m_unreconstructed_bc;
	Coord3D pos;
	pos.x = owner->m_position.x;
	pos.y = owner->m_position.y;
	pos.z = owner->m_position.z;

	PartitionFilterAcceptByKindOf filterKind(KindOfMaskType(KindOfMaskType::kInit, 7, 10, 11), KINDOFMASK_NONE);

	Object *target = ThePartitionManager->getClosestObject(&pos, rawRadius * 2.0f, 0, &filterKind);
	if (target)
	{
		Coord3D delta;
		delta.x = pos.x - target->m_position.x;
		delta.y = pos.y - target->m_position.y;
		delta.z = 0.0f;
		delta.normalize();

		float jitterX = GetGameLogicRandomValueReal(-0.1f, 0.1f, __FILE__, 3655);
		float finalX = jitterX + delta.x * 2.0f;
		float jitterY = GetGameLogicRandomValueReal(-0.1f, 0.1f, __FILE__, 3656);
		float finalY = jitterY + delta.y * 2.0f;

		Coord3D newPos;
		newPos.x = pos.x + finalX;
		newPos.y = pos.y + finalY;
		newPos.z = pos.z;

		((Thing *)owner)->setPosition(&newPos);
	}
}
