// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport

#include "PreRTS.h"
#include "Common/RandomValue.h"
#include "Common/TunnelTracker.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Object.h"

class BfmeTerrainGroundHeight
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
};

void TunnelContain::scatterToNearbyPosition(Object *obj)
{
	Object *theContainer = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x08);

#line 233 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\TunnelContain.cpp"
	Real angle = GameLogicRandomValueReal(0.0f, 2.0f * PI);

	Real minRadius = *reinterpret_cast<Real *>(reinterpret_cast<char *>(theContainer) + 0xbc);
	Real maxRadius = minRadius + minRadius / 2.0f;
	const Coord3D *containerPos = theContainer->getPosition();
#line 240 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\TunnelContain.cpp"
	Real dist = GameLogicRandomValueReal(minRadius, maxRadius);

	Coord3D pos;
	pos.x = dist * Cos(angle) + containerPos->x;
	pos.y = dist * Sin(angle) + containerPos->y;
	pos.z = reinterpret_cast<BfmeTerrainGroundHeight *>(TheTerrainLogic)->getGroundHeight(pos.x, pos.y, NULL);

	obj->setOrientation(angle);

	AIUpdateInterface *ai = *reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<char *>(obj) + 0x204);
	if (ai) {
		reinterpret_cast<Thing *>(obj)->setPosition(theContainer->getPosition());
		ai->ignoreObstacle(theContainer);
		ai->aiMoveToPosition(&pos, CMD_FROM_AI);
	} else {
		reinterpret_cast<Thing *>(obj)->setPosition(&pos);
	}
}

// Retail 0x0022F300. Use the real class declarations with BFME offsets.
// See diemodule-slot0-container-ondie.md for identity and the +0x28 die base.
static inline TunnelTracker *Rva0022F300Tracker(const Player *player)
{
    return *reinterpret_cast<TunnelTracker *const *>(reinterpret_cast<const char *>(player) + 0x22c);
}
void TunnelContain::onDie(const DamageInfo *damageInfo)
{
    // ZH puts module data/Object four bytes later; use its inline accessors
    // through a local shifted view. No virtual calls use this shifted pointer.
    TunnelContain *layout = reinterpret_cast<TunnelContain *>(reinterpret_cast<char *>(this) - 4);
    if (!layout->getTunnelContainModuleData()->m_dieMuxData.isDieApplicable(layout->getObject(), damageInfo))
        return;
    if (!*reinterpret_cast<Bool *>(reinterpret_cast<char *>(this) + 0xd5))
        return;
    Player *player = layout->getObject()->getControllingPlayer();
    if (player == NULL)
        return;
    TunnelTracker *tracker = Rva0022F300Tracker(player);
    if (tracker == NULL)
        return;
    tracker->onTunnelDestroyed(layout->getObject());
    *reinterpret_cast<Bool *>(reinterpret_cast<char *>(this) + 0xd5) = FALSE;
}


// TunnelContain.h inline ContainModuleInterface overrides, which retail emits
// as select-any COMDATs at 0x0022EF20 (asOpenContain, `lea eax,[ecx-0x20]`),
// 0x0022EF30 (isGarrisonable) and 0x0022EF40 (isHealContain). Emit them with
// that linkage; the anchor is compiler scaffolding, not a retail function.
#pragma inline_depth(0)
// ?Rva0022EF20EmitTunnelContainInlines@@YAXPAVTunnelContain@@@Z present-unmatched
void Rva0022EF20EmitTunnelContainInlines(TunnelContain *contain)
{
	contain->TunnelContain::asOpenContain();
	contain->TunnelContain::isGarrisonable();
	contain->TunnelContain::isHealContain();
}
#pragma inline_depth()
