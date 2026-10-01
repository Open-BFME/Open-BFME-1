// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002AD380, 594 bytes. Identity: StealthUpdate status bit 17,
// m_detectionExpiresFrame +0x24, reveal/disguise fields +0x34..0x42 and
// ZH StealthUpdate::markAsDetected. BFME adds container propagation as arg 2.
// The old receiveGrant(bool,unsigned) pin has reversed argument semantics:
// retail reads arg 1 as an unsigned duration and arg 2 as a propagation byte.
// ModuleData offsets are witnessed by name_oracle; other layouts follow the
// retail instructions and the existing StealthUpdate_disguiseAsObject.cpp.
// Native disguise helper visibility is needed for the inlined clear path.
// The local team copy preserves MSVC 7.1 scratch-register allocation.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
class ThingTemplate;
class Object;
class Team;
class Module;
enum NameKeyType { NAMEKEY_NONE };
enum Relationship { ENEMIES };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;
template<int N> class BitFlags { _STL::bitset<N> bits; public:
 enum Init { kInit }; BitFlags(Init,int n) { bits.set(n); } bool test(int n) const { return bits.test(n); }
};
class Player { public:
 Relationship getRelationship(const Team*) const;
 void iterateObjects(void (__cdecl*)(Object*,void*),void*) const;
 int getPlayerIndex() const { return *(const int*)((const char*)this+0x24); }
 char pad[0x230]; Team* team;
};
class PlayerList { public: Player* getNthPlayer(int); char pad[0x10]; int count; };
extern PlayerList* ThePlayerList;
// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp. Referencing it
// under the canonical spelling gives the linker one symbol; the frame field is
// read through this TU-local view of the retail layout.
class GameLogic;
extern GameLogic* TheGameLogic;
struct Rva002AD380GameLogic { char pad[0x3c]; unsigned frame; unsigned getFrame() const {return frame;} };
static __forceinline Rva002AD380GameLogic* stealthGameLogic() { return (Rva002AD380GameLogic*)TheGameLogic; }
struct Rva002AD380ControlBar { char pad[0x24]; bool dirty; };
extern Rva002AD380ControlBar* TheControlBar;
struct Rva002AD380Drawable { char pad[0x3ac]; bool selected; };
namespace _STL {
 template<> list<Object*>::list(const list<Object*>&);
 template<> _List_base<Object*,allocator<Object*> >::~_List_base();
}
typedef _STL::list<Object*> ObjectList002AD380;
class BfmeObjAS { public: BfmeObjAS* bfmeParentAS(int); };
int setWakeupIfInRange(Object*,void*);
class Rva002AD380Contain { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual const ObjectList002AD380& slotEC();
};
class Object { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual Rva002AD380Drawable* getDrawable();

 const ThingTemplate* getTemplate() const;
 Player* getControllingPlayer() const;
 Module* findModule(NameKeyType) const;
 void setStatus(const BitFlags<86>&,bool);
 
 void* unidentified_001BFE20() const;
 char pad004[0x8c]; BitFlags<86> status;
};
struct StealthUpdateModuleData {
 char pad000[8]; unsigned m_stealthDelay; unsigned m_stealthLevel;
 char pad010[0x24]; bool m_orderIdleEnemiesToAttackMeUponReveal;
 char pad035[0x1f]; unsigned m_disguiseTransitionFrames; unsigned m_disguiseRevealTransitionFrames;
};
class UpdateModule { public: void setWakeFrame(Object*,int); };
class StealthUpdate { public:
 void markAsDetected(unsigned frames,bool propagate);


 void* vptr; StealthUpdateModuleData* data; Object* object;
 char pad00c[0x18]; unsigned m_detectionExpiresFrame;
 char pad028[4]; Bool m_enabled; char pad02d[7]; int m_disguiseAsPlayerIndex; const ThingTemplate* m_disguiseAsTemplate;
 unsigned m_disguiseTransitionFrames; unsigned char m_disguiseHalfpointReached;
 unsigned char m_transitioningToDisguise; unsigned char m_disguised;
 __forceinline void clearDisguise(const Object *target)
{
	Object *self = object;
	const StealthUpdateModuleData *data =
		this->data;

	if (target && target->getControllingPlayer())
	{
		static NameKeyType key_StealthUpdate =
			TheNameKeyGenerator->nameToKey("StealthUpdate");
		StealthUpdate *stealth =
			(StealthUpdate *)target->findModule(key_StealthUpdate);
		if (stealth && stealth->m_disguiseAsTemplate)
		{
			m_disguiseAsTemplate = stealth->m_disguiseAsTemplate;
			m_disguiseAsPlayerIndex = stealth->m_disguiseAsPlayerIndex;
		}
		else
		{
			m_disguiseAsTemplate = target->getTemplate();
			m_disguiseAsPlayerIndex =
				target->getControllingPlayer()->getPlayerIndex();
		}

		m_enabled = 1;
		m_transitioningToDisguise = 1;
		m_disguiseTransitionFrames = data->m_disguiseTransitionFrames;
		m_disguiseHalfpointReached = 0;
		((UpdateModule*)this)->setWakeFrame(object,1);
	}
	else if (m_disguised)
	{
		m_disguiseAsTemplate = 0;
		m_disguiseAsPlayerIndex = 0;
		m_disguiseTransitionFrames =
			data->m_disguiseRevealTransitionFrames;
		m_transitioningToDisguise = 0;
		m_disguiseHalfpointReached = 0;
	}

	Rva002AD380Drawable *draw = self->getDrawable();
	if (draw && draw->selected)
		TheControlBar->dirty=true;
}

};
void StealthUpdate::markAsDetected(unsigned frames,bool propagate) {
 Object* self=object;
 const StealthUpdateModuleData* d=data;
 if(!self->status.test(17)) {
  if(propagate) {
   Object* owner=(Object*)((BfmeObjAS*)self)->bfmeParentAS(0);
   if(owner && ((d->m_stealthLevel & 0x100) || owner==self)) {
    Rva002AD380Contain* contain=(Rva002AD380Contain*)owner->unidentified_001BFE20();
    if(!contain) return;
    static NameKeyType key=TheNameKeyGenerator->nameToKey("StealthUpdate");
    StealthUpdate* stealth=(StealthUpdate*)owner->findModule(key);
    if(stealth) stealth->markAsDetected(frames,false);
    ObjectList002AD380 list(contain->slotEC());
    for(ObjectList002AD380::const_iterator it=list.begin();it!=list.end();++it) {
     StealthUpdate* child=(StealthUpdate*)(*it)->findModule(key);
     if(child) child->markAsDetected(frames,false);
    }
    return;
   }
  }
  self->setStatus(BitFlags<86>(BitFlags<86>::kInit,17),true);
  Player* thisPlayer=self->getControllingPlayer();
  if(m_disguiseAsTemplate) clearDisguise(0);
  if(d->m_orderIdleEnemiesToAttackMeUponReveal) {
   int count=ThePlayerList->count;
   for(int n=0;n<count;++n) {
    Player* player=ThePlayerList->getNthPlayer(n);
    if(!player) continue;
    Team* team=thisPlayer->team;
    if(player->getRelationship(team)!=ENEMIES) continue;
    player->iterateObjects((void (__cdecl*)(Object*,void*))setWakeupIfInRange,self);
   }
  }
 }
 unsigned now=stealthGameLogic()->frame;
 if(!frames) m_detectionExpiresFrame=now+d->m_stealthDelay;
 else if(m_detectionExpiresFrame<now+frames) m_detectionExpiresFrame=now+frames;
}
