// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// RVA 00328A80: condition dispatcher resolves the unit and either a named
// target or the nearest filtered object. The exact condition name is unknown.
// CastleBehavior is the retail literal; its indexed collection is represented
// by the existing address-derived 0036DB90 view, without inventing item names.
// The filter temporary ends with the query expression, and the player filter
// ends with the else block. Both are destroyed before the target is tested.
// The loop increments before itemAt; that native form reproduces retail's
// shared loop header and receiver/register lifetimes.
#include <bitset>
#include "ascii_string.h"
#include "coord3d.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class Module; class PolygonTrigger;
#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS Module *findModule(NameKeyType) const; bool didEnter(const PolygonTrigger*) const; bool didExit(const PolygonTrigger*) const;
#include "../Object/object.h"
class Parameter { public: char opaque[16]; AsciiString text; };
class Player;
class PlayerList { public: Player *getPlayerFromMask(unsigned short); };
class ScriptEngine { public:
virtual void slot00()=0;
virtual void slot01()=0;
virtual void slot02()=0;
virtual void slot03()=0;
virtual void slot04()=0;
virtual void slot05()=0;
virtual void slot06()=0;
virtual void slot07()=0;
virtual void slot08()=0;
virtual void slot09()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual Object *getUnitNamed(Parameter*)=0;
};
class BfmeScriptEngine_getPlayerMaskFromAsciiString { public: unsigned short getPlayerMaskFromAsciiString(const AsciiString&,bool*); };
template<size_t N> class BitFlags { public: enum BogusInitType { kInit=0 }; BitFlags(BogusInitType,int); private: _STL::bitset<N> m_bits; };
extern const BitFlags<192> KINDOFMASK_NONE;
class PartitionFilter { public: PartitionFilter():m_next(0){} virtual ~PartitionFilter(){} virtual bool allow(Object*)=0; PartitionFilter *link(PartitionFilter*); PartitionFilter *m_next; };
class PartitionFilterPlayer:public PartitionFilter { public: PartitionFilterPlayer(const Player*p,bool match):m_player(p),m_match(match){} virtual bool allow(Object*); private: const Player*m_player;bool m_match; };
class PartitionFilterAcceptByKindOf:public PartitionFilter { public: PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&); virtual bool allow(Object*); private: BitFlags<192> setBits,clearBits; };
class PartitionManager { public: Object *getClosestObject(const Coord3D*,float,int,PartitionFilter*); };
// WWMath defines Coord3D as a class; the existing engine pin spells the same 12-byte type as struct.
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
class Rva0036DB90Item;
class Rva0036DB90Collection { public: Rva0036DB90Item *itemAt(unsigned int) const; };
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva00328A80Condition { public: bool evaluate(Parameter*,Parameter*,Parameter*,bool); };
bool Rva00328A80Condition::evaluate(Parameter *unitParam, Parameter *targetParam, Parameter *playerParam, bool check)
{
 Object *unit=TheScriptEngine->getUnitNamed(unitParam);
 if (!unit) return false;
 Object *target;
 if (targetParam) target=TheScriptEngine->getUnitNamed(targetParam);
 else {
  if (!playerParam) return false;
  unsigned short mask=((BfmeScriptEngine_getPlayerMaskFromAsciiString*)TheScriptEngine)->getPlayerMaskFromAsciiString(playerParam->text,0);
  Player *player=ThePlayerList->getPlayerFromMask(mask);
  if(player) return false;
  PartitionFilterPlayer playerFilter(0,true);
  target=ThePartitionManager->getClosestObject(&unit->m_cachedPos,1000000.0f,0,PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit,119),KINDOFMASK_NONE).link(&playerFilter));
 }
 if(!target) return false;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleBehavior");
 Rva0036DB90Collection *collection=(Rva0036DB90Collection*)target->findModule(key);
 if(collection) {
  int i=0;
  do {
   ++i;
   PolygonTrigger *item=(PolygonTrigger*)collection->itemAt(i);
   if(!item) break;
   if(check && (unit->didEnter(item)||unit->didExit(item))) return true;
  } while(i<5);
 }
 return false;
}
