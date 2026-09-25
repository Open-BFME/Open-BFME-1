// ?ObjectCountNearbyEnemies@@YAHPAUlua_State@@@Z
// partial score=0.55 date=2026-09-25
// ?ObjectCountNearbyEnemies@@YAHPAUlua_State@@@Z
// scratch experiment: order filter construction before float radius materialization
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

struct lua_State;
extern "C" int lua_type(lua_State *, int);
extern "C" double lua_tonumber(lua_State *, int);
extern "C" void lua_pushnil(lua_State *);
extern "C" void lua_pushnumber(lua_State *, double);
unsigned Rva00990030Lookup(lua_State *, int);

class Object { public: unsigned char m_pad00[0x38]; Coord3D m_position; };
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;

class PartitionFilter {
public:
  PartitionFilter() : m_next(0) {}
  virtual ~PartitionFilter() {}
  virtual Bool allow(Object *);
  virtual Int getPlayerMask();
  PartitionFilter *link(PartitionFilter *next);
  PartitionFilter *m_next;
};
class Rva0025ED50ObjectFilter : public PartitionFilter {
public:
  explicit Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
  virtual ~Rva0025ED50ObjectFilter() {}
  virtual Bool allow(Object *);
  Object *m_object;
};
class Rva0025ED50RootFilter : public PartitionFilter {
public:
  Rva0025ED50RootFilter() {}
  virtual ~Rva0025ED50RootFilter() {}
  virtual Bool allow(Object *);
};
class PartitionFilterRelationship : public PartitionFilter {
public:
  PartitionFilterRelationship(Object *object, Int flags, Bool match)
      : m_object(object), m_flags(flags), m_match(match) {}
  virtual ~PartitionFilterRelationship() {}
  virtual Bool allow(Object *);
  virtual Int getPlayerMask();
  Object *m_object;
  Int m_flags;
  Bool m_match;
};

struct Rva002E8130Entry { Object *object; unsigned distanceBits; };
struct Rva009F39F0Payload {
  _STL::vector<Rva002E8130Entry> entries;
  Rva002E8130Entry *current;
  int references;
};
struct BfmeWideResult {
  Rva009F39F0Payload *value;
  BfmeWideResult();
  BfmeWideResult(const BfmeWideResult &);
  ~BfmeWideResult() { if (--value->references == 0) delete value; }
};
class BfmeWideForwardC {
public: BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};
extern BfmeWideForwardC *ThePartitionManager;

inline BfmeWideResult Rva002E8130Forward(BfmeWideForwardC *manager,
    int position, int filter, int radius)
{
  union { float real; int bits; } radiusWord;
  return manager->bfmeForwardWideC(
      position, (radiusWord.real = (float)radius, radiusWord.bits),
      0, filter, 1);
}

int ObjectCountNearbyEnemies(lua_State *state) {
  unsigned objectID = Rva00990030Lookup(state, 1);
  if (!objectID && lua_type(state, 1) != 1) {
    lua_pushnil(state);
    return 0;
  }
  volatile int radius = (int)lua_tonumber(state, 2);
  Object *object = TheGameLogic->findObjectByID((int)objectID);
  if (object != 0) {
    BfmeWideResult iterator = Rva002E8130Forward(ThePartitionManager,
        (int)((char *)object + 0x38),
        (int)PartitionFilterRelationship(object, 1, false).link(
            Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter(object))),
        radius);
    Rva009F39F0Payload *payload = iterator.value;
    int count = payload->entries.size();
    lua_pushnumber(state, (double)count);
    return 1;
  }
  lua_pushnumber(state, 0.0);
  return 1;
}
