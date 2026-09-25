// ?request@Rva0016F4F0Owner@@QAEXPAVObject@@0PAVAIUpdateInterface@@@Z
// partial score=0.563786 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/AIUpdate.h"
#define removeGoal removeGoal003E3D20
#include "GameLogic/AIPathfind.h"
#undef removeGoal
#include <math.h>

class Rva0016F4F0Callback
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30(); virtual void slot34(); virtual void slot38(int);
};
struct Rva0016F4F0AIView { char m_opaque00[0xC]; Pathfinder *m_pathfinder; };
struct Rva0016F4F0PositionView { char m_opaque00[0x38]; Coord3D m_position; };
class Rva0016F4F0Owner
{
public:
 void request(Object *origin, Object *target, AIUpdateInterface *ai);
 char m_opaque00[0x1C];
 Rva0016F4F0Callback *m_callback1C;
 char m_opaque20[4];
 Coord3D m_position24;
 char m_opaque30[0x1C];
 unsigned char m_flag4C;
};
void Rva0016F4F0Owner::request(Object *origin, Object *target, AIUpdateInterface *ai)
{
 if (target == 0) return;
 const Coord3D &from = ((Rva0016F4F0PositionView *)origin)->m_position;
 const Coord3D &to = ((Rva0016F4F0PositionView *)target)->m_position;
 Coord3D destination;
 destination.x = to.x;
 destination.y = to.y;
 destination.z = to.z;
 destination.x -= from.x;
 destination.y -= from.y;
 destination.z -= from.z;
 float inverseLength = 1.0f / (float)sqrt(destination.z * destination.z + destination.y * destination.y + destination.x * destination.x);
 destination.x *= inverseLength;
 destination.y *= inverseLength;
 destination.z *= inverseLength;
 destination.x *= 50.0f;
 destination.y *= 50.0f;
 destination.z *= 50.0f;
 destination.x += to.x;
 destination.y += to.y;
 destination.z += to.z;
 m_callback1C->slot38(0);
 ((Rva0016F4F0AIView *)TheAI)->m_pathfinder->removeGoal003E3D20(origin);
 m_flag4C = 0;
 m_position24 = destination;
 ai->requestPath(&destination, true);
}
