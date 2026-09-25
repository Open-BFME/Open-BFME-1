// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/GameEngine/Source/GameLogic/Object /ICode/GameEngine/Source/Common/Thing /ICode/GameEngine/Source/Common /ICode/GameEngine/Source/GameLogic /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail RVA 003287E0, 527 bytes; dispatcher ILT 00006852 proves this body.
// Team/target area query with native filter temporary lifetime. Condition and
// kind bit 119 identities remain opaque. Signed five-item loop matches retail.
// Declared BitFlags specialization preserves the witnessed out-of-line ctor.
#define __PLACEMENT_VEC_NEW_INLINE
#include <bitset>
#define ASCIISTRING_H
#include "ascii_string.h"
#define __THING_H_
#define __KINDOF_H_
#include "PreRTS.h"
#include "Common/GameType.h"
class Module;
class PolygonTrigger;
class Team;
#define OBJECT_TU_MEMBERS Module *findModule(NameKeyType) const;
#include "Object/object.h"

class Parameter { public: char opaque[16]; AsciiString text; };
class Player;
class PlayerList { public: Player *getPlayerFromMask(unsigned short); };
class ScriptEngine {
public:
 virtual void slot00()=0; virtual void slot01()=0; virtual void slot02()=0;
 virtual void slot03()=0; virtual void slot04()=0; virtual void slot05()=0;
 virtual void slot06()=0; virtual void slot07()=0; virtual void slot08()=0;
 virtual void slot09()=0; virtual void slot10()=0; virtual void slot11()=0;
 virtual void slot12()=0; virtual void slot13()=0; virtual void slot14()=0;
 virtual void slot15()=0; virtual void slot16()=0;
 virtual Team *getTeamNamed(AsciiString, bool)=0;
 virtual void slot18()=0; virtual void slot19()=0; virtual void slot20()=0;
 virtual void slot21()=0; virtual void slot22()=0; virtual void slot23()=0;
 virtual void slot24()=0; virtual void slot25()=0;
 virtual Object *getUnitNamed(Parameter*)=0;
};
class BfmeScriptEngine_getPlayerMaskFromAsciiString {
public: unsigned short getPlayerMaskFromAsciiString(const AsciiString &, bool *);
};
template<> BitFlags<192>::BitFlags(BitFlags<192>::BogusInitType, Int);
class PartitionFilter { public:
 PartitionFilter():m_next(0){} virtual ~PartitionFilter(){} virtual bool allow(Object*)=0;
 PartitionFilter *link(PartitionFilter*); PartitionFilter *m_next;
};
extern const BitFlags<192> KINDOFMASK_NONE;
class PartitionFilterPlayer:public PartitionFilter {
public: PartitionFilterPlayer(const Player*p,bool match):m_player(p),m_match(match){} virtual bool allow(Object*);
private: const Player*m_player; bool m_match;
};
class PartitionFilterAcceptByKindOf:public PartitionFilter {
public: PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&); virtual bool allow(Object*);
private: BitFlags<192> setBits,clearBits;
};
class PartitionManager { public: Object *getClosestObject(const Coord3D*,float,int,PartitionFilter*); };
class Rva0036DB90Item;
class Rva0036DB90Collection { public: Rva0036DB90Item *itemAt(unsigned int) const; };
class Team {
public:
 Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *) const;
 bool didPartialEnter(PolygonTrigger*,unsigned int) const;
 bool didAllEnter(PolygonTrigger*,unsigned int) const;
 bool didPartialExit(PolygonTrigger*,unsigned int) const;
 bool didAllExit(PolygonTrigger*,unsigned int) const;
};
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva003287E0Condition {
public:
 bool evaluate(Parameter *teamParam, Parameter *targetParam, Parameter *playerParam,
               bool which, bool enabled);
};

bool Rva003287E0Condition::evaluate(Parameter *teamParam, Parameter *targetParam,
                                    Parameter *playerParam, bool which, bool enabled)
{
 Team *team = TheScriptEngine->getTeamNamed(teamParam->text, false);
 if (!team) return false;

 Object *target;
 if (targetParam) {
  target = TheScriptEngine->getUnitNamed(targetParam);
 } else {
  if (!playerParam) return false;
  unsigned short mask = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
      ->getPlayerMaskFromAsciiString(playerParam->text, false);
  Player *player = ThePlayerList->getPlayerFromMask(mask);
  if (player) return false;

  Coord3D teamPosition;
  team->getEstimateTeamPosition_000EDCD0(&teamPosition);
  PartitionFilterPlayer playerFilter(0, true);
  target = ThePartitionManager->getClosestObject(&teamPosition, 1000000.0f, 0,
      PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit, 119),
                                    KINDOFMASK_NONE).link(&playerFilter));
 }
 if (!target) return false;

 static NameKeyType castleBehaviorKey = TheNameKeyGenerator->nameToKey("CastleBehavior");
 Rva0036DB90Collection *collection =
     (Rva0036DB90Collection *)target->findModule(castleBehaviorKey);
 if (collection) {
  int i = 0;
  do {
   ++i;
   PolygonTrigger *item = (PolygonTrigger *)collection->itemAt(i);
   if (!item) break;
   if (which) {
    if (enabled && (team->didPartialEnter(item, 9) || team->didAllEnter(item, 9))) return true;
   } else {
    if (enabled && (team->didPartialExit(item, 9) || team->didAllExit(item, 9))) return true;
   }
  } while (i < 5);
 }
 return false;
}
