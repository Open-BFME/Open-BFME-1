// ?privateFollowPathAppend@AIUpdateInterface@@MAEXPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.9578 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_AI };
struct Coord3D { float x,y,z; };
class Object;
struct State { int getID() const { return id; } char prefix[4]; int id; };
class AIStateMachine {
public:
 void addToGoalPath(const Coord3D *);
 int getCurrentStateID() const {
  int id = current ? current->getID() : 999999;
  if (id == 999999) id = fallback ? fallback->getID() : 999999;
  return id;
 }
 char prefix[0x1c]; State *fallback;
 char pad20[4]; Coord3D goal;
 char pad30[0x14]; _STL::vector<Coord3D> goalPath;
 char pad50[8]; State *current;
};
class AIUpdateInterface {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void privateFollowPath(const _STL::vector<Coord3D> *,Object *,CommandSourceType,Bool);
 Bool isMoving() const;
protected:
 virtual void privateFollowPathAppend(const Coord3D *,CommandSourceType);
 void playMoveVoiceResponse(const Coord3D *);
private:
 char pad04[0x2c]; AIStateMachine *machine;
 char pad34[0x31e-0x34]; Bool waiting;
};
#pragma comment(linker, "/alternatename:?isMoving@AIUpdateInterface@@QBE_NXZ=?j_00044774@@YAXXZ")
#pragma comment(linker, "/alternatename:?addToGoalPath@AIStateMachine@@QAEXPBUCoord3D@@@Z=?j_00046a65@@YAXXZ")
void AIUpdateInterface::privateFollowPathAppend(const Coord3D *pos, CommandSourceType command)
{
 Bool effectivelyMoving = isMoving() || waiting;
 if (effectivelyMoving && machine->fallback && machine->fallback->id == 16) effectivelyMoving = false;
 if (machine->getCurrentStateID() == 6 && (int)machine->goalPath.size() > 0 && effectivelyMoving) {
  machine->addToGoalPath(pos);
 } else if (effectivelyMoving) {
  _STL::vector<Coord3D> path;
  path.push_back(machine->goal);
  path.push_back(*pos);
  privateFollowPath(&path,0,command,false);
 } else {
  _STL::vector<Coord3D> path;
  path.push_back(*pos);
  privateFollowPath(&path,0,command,false);
  if (command == CMD_FROM_PLAYER || command == CMD_FROM_AI) playMoveVoiceResponse(pos);
 }
}
