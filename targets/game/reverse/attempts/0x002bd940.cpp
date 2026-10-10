// ?bfmeGo002BD940@Rva002BD940Owner@@QAEXXZ
// partial score=0.8966 date=2026-10-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define BFME_STLP_NODE_ALLOC 1
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/KindOf.h"

extern "C" const BitFlags<192> __identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B");

// Object position and the scalar at +0xBC are read directly in retail.
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
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *objOther) = 0;
	virtual int getPlayerMask();
	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(const BitFlags<181> &mustBeSet, const BitFlags<181> &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual bool allow(Object *objOther);
private:
	BitFlags<181> m_mustBeSet, m_mustBeClear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc, PartitionFilter *filter);
};

extern PartitionManager *ThePartitionManager;
extern float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// The matched 0x002C12E0 caller passes this receiver without adjustment.
class Rva002BD940Owner
{
public:
	void bfmeGo002BD940();

	unsigned char m_unreconstructed_00[8];
	Object *m_owner008;
};

// ?bfmeGo002BD940@Rva002BD940Owner@@QAEXXZ
void Rva002BD940Owner::bfmeGo002BD940()
{
	Object *owner = m_owner008;
	float rawRadius = owner->m_unreconstructed_bc;
	Coord3D pos;
	pos.x = owner->m_position.x;
	pos.y = owner->m_position.y;
	pos.z = owner->m_position.z;

	PartitionFilterAcceptByKindOf filterKind(BitFlags<181>(BitFlags<181>::kInit, 7, 10, 11), *(const BitFlags<181> *)&__identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B"));

	Object *target = ThePartitionManager->getClosestObject(&pos, rawRadius * 2.0f, 0, &filterKind);
	if (target)
	{
		Coord3D delta;
		delta.x = pos.x - target->m_position.x;
		delta.y = pos.y - target->m_position.y;
		delta.z = 0.0f;
		delta.normalize();

		delta.scale(2.0f);
		delta.x += GetGameLogicRandomValueReal(-0.1f, 0.1f, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp", 3655);
		delta.y += GetGameLogicRandomValueReal(-0.1f, 0.1f, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp", 3656);
		pos.add(&delta);
		((Thing *)owner)->setPosition(&pos);
	}
}
