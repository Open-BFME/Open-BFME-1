// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Iinputs/reference/shims/sweep /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "Common/NameKeyGenerator.h"
#include "CastleBehaviorRecovery.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include "../../../GameClient/FXListRetail.h"
enum DamageType { DAMAGE_TYPE_8 = 8 };
enum DeathType { DEATH_TYPE_0 = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_4E = 0x4e };
typedef bool Bool;
class Module;
#define OBJECT_TU_MEMBERS \
	Team* getTeam() const { return m_team; } \
	void kill(DamageType, DeathType); \
	friend class CastleBehavior; \
protected: \
	Module* findModule(NameKeyType) const;
#include "object.h"
// Retail 0x00373B30. CastleBehavior receiver witnessed by neighbouring methods;
// semantic method identity remains unknown. Caller: CastleBehavior update
// interface at 0x00377740 through its ILT. Object layout is the canonical header.
// +0xD0/+0xD4 delimit owned ObjectIDs; +0xA0 selects the construction object.
// Body-interface slots +0x3C/+0x40 return the last damage record and frame.
// The record supplies the player mask at +0xC and damage amount at +0x1C.
// Repeated record calls and the shared effects tail reproduce retail exactly.
// getTeam() intentionally returns by value: direct field access rotates the
// scratch registers and changes the second mask load from xor/mov to movzx.
// The sound call preserves the existing ThingTemplate::getSound callee ABI;
// the pointer comes from Object::getDrawable, not a recovered template field.
// No identity correction of that already-landed callee is claimed here.
class Team;
class Object;
class Player { public: Relationship getRelationship(const Team*) const; };
class GameLogic { public: Object* findObjectByID(int); };
class PlayerList { public: Player* getPlayerFromMask(unsigned short); };
class AudioEventRTS;
class ThingTemplate { public: const AudioEventRTS* getSound(int) const; };
extern GameLogic* TheGameLogic;
extern PlayerList* ThePlayerList;
class AudioManager;
extern AudioManager* TheAudio;
template<class T> inline T& at(void* p,int n) { return *(T*)((char*)p+n); }
struct DamageRecord00373B30 { char field00[12]; unsigned short field0c; char field0e[14]; float field1c; };
class DamageSource00373B30 {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38();
 virtual DamageRecord00373B30* record();
 virtual unsigned frame();
};
class HealingDispatch00373B30 {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void slot28();
 virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void dispatch(float,Object*);
};
struct Audio00373B30 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void v40(); virtual void add(const AudioEventRTS*);
};
class Rva00373B30Receiver {
public:
 void update();
 void reset(bool b) { ((CastleBehavior*)this)->rva00372bd0(b); }
};
void Rva00373B30Receiver::update() {
 if(at<int*>(this,0xd0)==at<int*>(this,0xd4)) return;
 Object* object=TheGameLogic->findObjectByID(at<int>(this,0xa0));
 if(!object || object->m_constructionPercent<8.0f) return;
 void* data=at<void*>(this,4);
 bool hostile=false;
 bool expired=false;
 for(int i=(at<int*>(this,0xd4)-at<int*>(this,0xd0))-1;i>=0;--i) {
  Object* child=TheGameLogic->findObjectByID(at<int*>(this,0xd0)[i]);
  if(!child) continue;
  DamageSource00373B30* damage=(DamageSource00373B30*)child->m_body;
  if(damage && damage->frame()>=at<unsigned>(this,0xb0) && damage->record() && damage->record()->field1c>0.0f) {
   Player* player=ThePlayerList->getPlayerFromMask(damage->record()->field0c);
   if(player && player->getRelationship(object->getTeam())==0 && ((StringBase<char>*)((char*)player+0x1c))->compare("PlyrCreeps")!=0) { hostile=true; break; }
  }
 }
 DamageSource00373B30* damage=(DamageSource00373B30*)object->m_body;
 if(damage && damage->frame()>=at<unsigned>(this,0xb0) && damage->record() && damage->record()->field1c>0.0f) {
  Player* player=ThePlayerList->getPlayerFromMask(damage->record()->field0c);
  if(player && player->getRelationship(object->getTeam())==0 && ((StringBase<char>*)((char*)player+0x1c))->compare("PlyrCreeps")!=0) hostile=true;
 }
 if(!(object->m_constructionPercent>=99.0f)) {
  if(at<unsigned>(TheGameLogic,0x3c)>=at<unsigned>(this,0xb0)+at<unsigned>(data,0x44)) expired=true;
  if(!hostile || !expired) goto effects;
 }
 {
  reset(false);
  ((HealingDispatch00373B30*)object)->dispatch(9999.0f,object);
  object->m_constructionPercent=100.0f;
  ThingTemplate* t=(ThingTemplate*)object->getDrawable();
  if(t) { const AudioEventRTS* sound=t->getSound(13); if(sound) ((Audio00373B30*)TheAudio)->add(sound); }
 }
effects:
 if((unsigned)(at<int*>(this,0xd4)-at<int*>(this,0xd0))>0 && at<unsigned>(TheGameLogic,0x3c)%at<unsigned>(data,0x48)==0) {
  const FXList* fx=at<FXList*>(data,0x4c);
  if(fx) FXList::doFXObj(fx,at<Object*>(this,8),0);
 }
}

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

typedef _STL::hash_map<int, Object *, _STL::hash<int>,
	_STL::equal_to<int> > CastleObjectMap00372BD0;

struct Rva00367E30Logic
{
	__forceinline Object *findObjectByID(int id)
	{
		if (id == 0)
			return 0;

		CastleObjectMap00372BD0::iterator it = m_objects.find(id);
		if (it == m_objects.end())
			return 0;

		return (*it).second;
	}

private:
	unsigned char m_pad00[0xb0];
	CastleObjectMap00372BD0 m_objects;
};

static inline Rva00367E30Logic *bfmeLogicView00373B30() { return (Rva00367E30Logic *)TheGameLogic; }


class Rva00372BD0Calls {};

template <class R>
__forceinline R call0(void (*p)(), void *self)
{
	typedef R (Rva00372BD0Calls::*F)();
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00372BD0Calls *)self)->*u.f)();
}

template <class R, class A>
__forceinline R call1(void (*p)(), void *self, A a)
{
	typedef R (Rva00372BD0Calls::*F)(A);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00372BD0Calls *)self)->*u.f)(a);
}

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (Rva00372BD0Calls::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00372BD0Calls *)self)->*u.f)(a, b);
}

extern void j_00026094();
extern void j_0002ec44();
extern void j_0003bf11();
extern void j_00045827();


// The matched update at RVA 0x00373B30 calls through ILT 0x00013935 and passes
// a boolean. Matched CastleBehavior method 0x00371EE0 identifies the receiver.
// Retail strings identify the EntEnragedUpdate and LifetimeUpdate lookups.
// The method's purpose remains unproven, so its name keeps RVA 0x00372BD0.
void CastleBehavior::rva00372bd0(Bool killOwnedObjects)
{
	ObjectID *ownedEnd = m_ownedObjectsD0.end();
	ObjectID *id = m_ownedObjectsD0.begin();
	if (id != ownedEnd) {
		do {
			if (*id != 0) {
				Object *child = bfmeLogicView00373B30()->findObjectByID(*id);
				if (child != 0) {
					call1<void>(j_00045827, this, child);
					if (killOwnedObjects) {
						child->kill((DamageType)8, (DeathType)0);
					} else {
						static NameKeyType enragedKey =
							TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
						Module *enraged = child->findModule(enragedKey);
						if (enraged != 0)
							call2<void>(j_0002ec44, enraged,
								(unsigned char)1, (unsigned char)1);

						static NameKeyType lifetimeKey =
							TheNameKeyGenerator->nameToKey("LifetimeUpdate");
						Module *lifetime = child->findModule(lifetimeKey);
						if (lifetime != 0)
							call0<void>(j_0003bf11, lifetime);
					}
				}
			}
			++id;
		} while (id != m_ownedObjectsD0.end());
	}

	if (m_ownedObjectsD0.size() > 0 && !killOwnedObjects) {
		FXList *effects = m_moduleData->m_effects;
		if (effects != 0) {
			Object *owner = m_object;
			if (!effects->bfmeIsBlocked())
				effects->doFXObj(owner, (Object *)0);
		}
	}

	m_ownedObjectsD0.clear();
	call2<void>(j_00026094, this, (ObjectStatusTypes)0x4e, false);
}
