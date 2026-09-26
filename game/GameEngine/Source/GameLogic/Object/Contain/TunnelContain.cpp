// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport

#include "PreRTS.h"
#include "Common/RandomValue.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Object.h"

class BfmeThingPositionSetter
{
public:
	void setPosition(const Coord3D *position);
};

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
		reinterpret_cast<BfmeThingPositionSetter *>(obj)->setPosition(theContainer->getPosition());
		ai->ignoreObstacle(theContainer);
		ai->aiMoveToPosition(&pos, CMD_FROM_AI);
	} else {
		reinterpret_cast<BfmeThingPositionSetter *>(obj)->setPosition(&pos);
	}
}
