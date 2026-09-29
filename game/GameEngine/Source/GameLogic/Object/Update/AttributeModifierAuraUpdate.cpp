// cl: /DNDEBUG /I. /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <list>
#include <algorithm>
#include <bitset>
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const {return m_data == 0 || m_data->length == 0;}
typedef bool Bool;
typedef int Int;
typedef unsigned UnsignedInt;
typedef float Real;
struct Coord3D;
enum IterOrderType {ITER_FASTEST=0};
template<unsigned N> class AuraFlags2803 {
 std::bitset<N> bits;
public:
 enum Init {kInit};
 AuraFlags2803() {}
 AuraFlags2803(Init,int a) {bits.set(a);}
 AuraFlags2803(Init,int a,int b) {bits.set(a);bits.set(b);}
 int count() const {return bits.count();}
 bool test(int n) const {return bits._Unchecked_test(n);}
};

// Filter/iterator ABI is shared with the landed 0x00265150 query.

class Object;
class Player;

// BFME's partition filters have a three-slot surface: scalar destructor,
// predicate, and getPlayerMask.  The ZH header has only the abstract predicate;
// this view preserves the BFME slots without inventing predicate bodies.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// Retail vtable 0x01085DD0; slot 1 is the matched +0x344 bit-3
// same-map-status comparison.
class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

// Retail vtable 0x01083B80; slot 1 is the matched inverse +0x344 bit-0
// effective-dead test.  The neutral address-derived name avoids claiming a
// canonical owner for this BFME vtable.
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

// Retail vtable 0x010A5158.  The matched slot-1 body is
// BfmeThingRJ::bfmeCheckRJ(void*); fields are the proven +8/+C/+10 shape.
class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

// The relationship table and all three of its methods are independently
// matched.  This is the canonical name for the BFME-compatible view.
class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

// The matched 0x009F2960 wrapper has a four-byte hidden result followed by
// (position, radius, order, filter-head, flag).  The generic decorated
// wrapper name does not assert the semantic owner; this BFME ABI view does.
class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

extern PartitionManager *ThePartitionManager;

// Retail 0x002803F0..0x002809AF (1471 bytes). Mislabelled destructor in the old lift.
// Named ctor 0x002800D0 installs 0x010BAFA0 at primary+0x10;
// slot 0 -> ILT 0x00011036 -> this update body. Actual dtor is 0x0027FF70.
// Receiver is the +0x10 UpdateModuleInterface view, as in DelayedLuaEventUpdate.
// Data offsets are directly witnessed in retail; name_oracle has no class witness.
template<class T> inline T &field2803(void *p, int offset) {
 return *reinterpret_cast<T *>(static_cast<char *>(p)+offset);
}
typedef AuraFlags2803<192> AuraKindMask2803;
class Rva0025F2D0KindOfAnyFilter : public PartitionFilter {
public:
 Rva0025F2D0KindOfAnyFilter(const AuraKindMask2803 &mask) : m_mask(mask) {}
 virtual ~Rva0025F2D0KindOfAnyFilter() {}
 virtual Bool allow(Object *);
 AuraKindMask2803 m_mask;
};
class Gen_009f2b10 {public: void m();};
class Rva003679B0 { public: void set(int,unsigned); };
class AttributeModifierPoolUpdate;
enum KindOfType {AURA_KIND_59=59};
struct KindOfMask : AuraFlags2803<192> {
 KindOfMask(int a,int b) : AuraFlags2803<192>(kInit,a,b) {}
};
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const; bool isAnyKindOf(const KindOfMask &) const;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const; int getLayer() const; bool applyAttributeModifier(const AsciiString &,int); private: friend class AttributeModifierAuraUpdate; AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"

class GameLogic;
extern GameLogic *TheGameLogic;
enum NameKeyType {};
class NameKeyGenerator {public: NameKeyType nameToKey(const char *);};
extern NameKeyGenerator *TheNameKeyGenerator;
class AttributeModifierDefinitionStore {public: int indexOf(int) const; int valueAt(int) const;};
extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;
// 0x00880E60 forwards through this+0xC to the matched world-point query
// at 0x008814A0. Its callee reads x/y and returns int; the wrapper keeps ret4.
class BfmeTaintManager {public: int queryAt00880E60(const Coord3D *);};
extern BfmeTaintManager *TheTaintManager;
class FXList {public: static void doFXObj(const FXList *,const Object *,const Object *);};
class AuraUpgradeInterface2803 {public: virtual bool slot00();};
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER_2803=0x3fffffff};
class AttributeModifierAuraUpdate {public: virtual UpdateSleepTime update();
 Object *getObject() const {return *(Object **)((char *)this-8);}
};
UpdateSleepTime AttributeModifierAuraUpdate::update() {
 Object *object=getObject();
 void *data=field2803<void *>(this,-12);
 if ((field2803<unsigned char>(object,0x344)&1) && !field2803<bool>(data,0xa2)
     || !reinterpret_cast<AuraUpgradeInterface2803 *>((char *)this+0x10)->slot00())
  return UPDATE_SLEEP_FOREVER_2803;
 if ((field2803<unsigned>(data,0x94)&1) && !(field2803<unsigned>(object,0x128)&0x800)
     || !field2803<bool>(data,0x20) && (field2803<unsigned char>(getObject(),0x114)&0x20))
  return (UpdateSleepTime)(field2803<int>(object,0x74)%5+field2803<int>(data,0x18));
 bool special=getObject()->isKindOf(AURA_KIND_59);
 Rva0025ED50ObjectFilter sameMap(object);
 PartitionFilterRelationship relationship1(object,1,false);
 PartitionFilterRelationship relationship4(object,4,false);
 Rva00265150RJFilter objectFilter((char *)data+0x24,object->getControllingPlayer(),true);
 Rva0025ED50RootFilter root;
 root.link(&sameMap);
 if (!field2803<bool>(data,0xa0) && !field2803<bool>(data,0xa1)) {
  if (field2803<bool>(data,0x21)) root.link(&relationship1);
  else if (!special) root.link(&relationship4);
 }
 root.link(&objectFilter);
 float radius=special ? field2803<float>(getObject(),0xbc) : field2803<float>(data,0x1c);
 Rva0025ED50WideResult iterator=ThePartitionManager->iterate(&field2803<Coord3D>(object,0x38),radius,ITER_FASTEST,&root,true);
 reinterpret_cast<Gen_009f2b10 *>(&sameMap)->m();
 Rva0025F2D0KindOfAnyFilter kind(AuraKindMask2803(AuraKindMask2803::kInit,59));
 Rva0025ED50RootFilter root2;
 root2.link(&sameMap);
 root2.link(&kind);
 bool hasModifier=!field2803<AsciiString>(data,8).isEmpty();
 unsigned endFrame=0;
 int selected=7;
 AuraFlags2803<7> &flags=field2803<AuraFlags2803<7> >(data,0x98);
 if (flags.count()>0) {
  endFrame=field2803<unsigned>(TheGameLogic,0x3c);
  if (hasModifier) {
   unsigned duration=TheAttributeModifierDefinitionStore->valueAt(TheAttributeModifierDefinitionStore->indexOf(TheNameKeyGenerator->nameToKey(field2803<AsciiString>(data,8).str())));
   if(duration>0) endFrame+=duration; else endFrame+=999999;
  }
  for (int i=0;i<7;++i) if(flags.test(i)) {selected=i;break;}
 }
 Object *other;
 while(iterator.next(other)) {
  if(other->isAnyKindOf(KindOfMask(47,150))) continue;
  if(!field2803<bool>(data,0xa3) && other==object) continue;
  if(field2803<bool>(data,0xa0)) {
   void *side=field2803<void *>(other->getControllingPlayer(),4);
   if(side && field2803<bool>(side,0x118)) continue;
  }
  if(field2803<bool>(data,0xa1)) {
   void *side=field2803<void *>(other->getControllingPlayer(),4);
   if(!side || !field2803<bool>(side,0x118)) continue;
  }
  void *experience=field2803<void *>(other,0x210);
  if(experience) {
   int level=field2803<int>(experience,0x28);
   if(field2803<int>(data,0xa4) && level>field2803<int>(data,0xa4)) continue;
  }
  if(special && (other->getLayer()<17 || other->getLayer()>64)) continue;
  if(field2803<unsigned>(data,0x94)&2) {
   if(TheTaintManager->queryAt00880E60(&field2803<Coord3D>(other,0x38))!=2) continue;
  } else if(field2803<unsigned>(data,0x94)&4) {
   if(TheTaintManager->queryAt00880E60(&field2803<Coord3D>(other,0x38))!=1) continue;
  }
  if(endFrame && selected!=7) {
   Rva003679B0 *pool=reinterpret_cast<Rva003679B0 *>(other->findAttributeModifierPoolUpdate());
   pool->set(selected,endFrame);
   if(field2803<void *>(data,0x9c)) FXList::doFXObj(field2803<FXList *>(data,0x9c),other,0);
  }
  if(!field2803<AsciiString>(data,8).isEmpty()) {
   AsciiString name(field2803<AsciiString>(data,8).str());
   other->applyAttributeModifier(name,-1);
  }
 }
 return (UpdateSleepTime)(field2803<int>(object,0x74)%5+field2803<int>(data,0x18));
}

