// ?onRemoving@TransportContain@@UAEXPAVObject@@@Z
// partial score=0.990881459 date=2026-09-28
// ?onContaining@TransportContain@@UAEXPAVObject@@_N@Z
// Reconstructed from retail 0x0022E340; BFME exit path differs from ZH.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME TransportContain::onContaining, retail 0x0022DD10 (865 bytes).
//
// Identity is established by the matched RiderChangeContain::onContaining
// caller at 0x0022B3E0 and the existing TransportContain callee pin.  The
// retail body is the ContainModuleInterface secondary view: module data is at
// this-0x1c and the owning Object is at this-0x18.  This TU keeps that BFME
// view local; the vendored Zero Hour TransportContain layout is not used.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty()const{return !m_data||!m_data->length;}
template<> inline const char* StringBase<char>::str()const{return m_data?m_data->data:"";}
#include "ascii_string.h"
struct Coord3D {float x,y,z;};
class Matrix3D;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
void j_0000e68d();
namespace _STL {
template<> inline _List_base<Object*,allocator<Object*> >::~_List_base() {
 typedef _List_base<Object*,allocator<Object*> > Base;
 union { void (*raw)(); void (Base::*member)(); } call;
 call.raw=&j_0000e68d; (this->*call.member)();
}
template<> __declspec(noinline) list<Object*,allocator<Object*> >::list(const allocator<Object*>& a) : _Base(a) {}
}
class Player;

enum KindOfType
{
	KINDOF_BFME_66 = 0x66,
	KINDOF_BFME_6C = 0x6c
};

void j_0003f288(); void j_00046a1f();
class Drawable
{
public:
	void applyPendingModelConditionFlags(Bool pending);
	void bfmeDelayA(Int frames) { union {void (*raw)(); void(Drawable::*member)(int);} c; c.raw=&j_0003f288; (this->*c.member)(frames); }
	void bfmeDelayB(Int frames) { union {void (*raw)(); void(Drawable::*member)(int);} c; c.raw=&j_00046a1f; (this->*c.member)(frames); }
};

template<int N> class BitFlags {public: _STL::bitset<N> bits;};
extern const BitFlags<116> KINDOFMASK_NONE;
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
 void convertBonePosToWorldPos(const Coord3D*,const Matrix3D*,Coord3D*,Matrix3D*)const;
 void setPosition(const Coord3D*);
 void setOrientation(float);
 char pad000[0x44]; float m_cachedAngle;
 float getOrientation()const{return m_cachedAngle;}

	template <int NUMBITS>
	class KindOfMask
	{
	public:
		_STL::bitset<NUMBITS> m_bits;
 Bool any() const { return m_bits.any(); }
	};

	typedef KindOfMask<192> KindOfMaskType;
	Bool isKindOfMulti(const BitFlags<116>&,const BitFlags<116>&) const;
};

void j_000348ec();
enum ObjectStatusTypes { STATUS_003B=0x3b };
enum DisabledType { DISABLED_HELD=3 };
enum Relationship { RELATIONSHIP_ENEMY=2 };
class Object
{
public:
	// Object::getDrawable is vtable slot 10 (+0x28) in the BFME Object view.
	virtual void objectSlot00() = 0;
	virtual void objectSlot01() = 0;
	virtual void objectSlot02() = 0;
	virtual void objectSlot03() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot05() = 0;
	virtual void objectSlot06() = 0;
	virtual void objectSlot07() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot09() = 0;
	virtual Drawable *getDrawable() const;

 struct ModelFlags { _STL::bitset<320> bits; unsigned test(unsigned bit)const{return ((const unsigned*)&bits)[bit>>5]&(1u<<(bit&31));} void set(unsigned bit){bits.set(bit);} };
 char pad004[0x10c];
 ModelFlags m_modelConditionFlags;
 const ModelFlags& getFlags() const { return m_modelConditionFlags; }
 __forceinline void setModelCondition(unsigned bit) { if(!getFlags().test(bit)) { m_modelConditionFlags.set(bit); notifyModelConditionChanged(); } }

	void setDisabled(DisabledType);
 bool clearDisabled(DisabledType);
 __forceinline void clearModelCondition(unsigned bit) { unsigned &f=((unsigned*)&m_modelConditionFlags)[bit>>5]; if(f&(1u<<(bit&31))) {f&=~(1u<<(bit&31));notifyModelConditionChanged();} }
	void notifyModelConditionChanged();
	Int getTransportSlotCount() const;
	void *unidentified_001BFE20() const;
	void setStatusBit(Int mode, bool value);
 void clearStatus(ObjectStatusTypes);
	void clearCondition(Int mode) { union {void (*raw)();void(Object::*member)(int);} c;c.raw=&j_000348ec;(this->*c.member)(mode); }
	Relationship getRelationship(const Object *other) const;
};

// Object::unidentified_001BFE20 is the existing address-derived accessor at
// ILT 0x0000D3B9.  Its retail return is an opaque provider used only through
// the virtual slot at +0xf0 below, so keep the return opaque in this TU.
typedef void *(*BfmeOpaqueAccessor)(void);

class BfmeListProvider
{
public:
	virtual void providerSlot00() = 0;
	virtual void providerSlot01() = 0;
	virtual void providerSlot02() = 0;
	virtual void providerSlot03() = 0;
	virtual void providerSlot04() = 0;
	virtual void providerSlot05() = 0;
	virtual void providerSlot06() = 0;
	virtual void providerSlot07() = 0;
	virtual void providerSlot08() = 0;
	virtual void providerSlot09() = 0;
	virtual void providerSlot10() = 0;
	virtual void providerSlot11() = 0;
	virtual void providerSlot12() = 0;
	virtual void providerSlot13() = 0;
	virtual void providerSlot14() = 0;
	virtual void providerSlot15() = 0;
	virtual void providerSlot16() = 0;
	virtual void providerSlot17() = 0;
	virtual void providerSlot18() = 0;
	virtual void providerSlot19() = 0;
	virtual void providerSlot20() = 0;
	virtual void providerSlot21() = 0;
	virtual void providerSlot22() = 0;
	virtual void providerSlot23() = 0;
	virtual void providerSlot24() = 0;
	virtual void providerSlot25() = 0;
	virtual void providerSlot26() = 0;
	virtual void providerSlot27() = 0;
	virtual void providerSlot28() = 0;
	virtual void providerSlot29() = 0;
	virtual void providerSlot30() = 0;
	virtual void providerSlot31() = 0;
	virtual void providerSlot32() = 0;
	virtual void providerSlot33() = 0;
	virtual void providerSlot34() = 0;
	virtual void providerSlot35() = 0;
	virtual void providerSlot36() = 0;
	virtual void providerSlot37() = 0;
	virtual void providerSlot38() = 0;
	virtual void providerSlot39() = 0;
	virtual void providerSlot40() = 0;
	virtual void providerSlot41() = 0;
	virtual void providerSlot42() = 0;
	virtual void providerSlot43() = 0;
	virtual void providerSlot44() = 0;
	virtual void providerSlot45() = 0;
	virtual void providerSlot46() = 0;
	virtual void providerSlot47() = 0;
	virtual void providerSlot48() = 0;
	virtual void providerSlot49() = 0;
	virtual void providerSlot50() = 0;
	virtual void providerSlot51() = 0;
	virtual void providerSlot52() = 0;
	virtual void providerSlot53() = 0;
	virtual void providerSlot54() = 0;
	virtual void providerSlot55() = 0;
	virtual void providerSlot56() = 0;
	virtual void providerSlot57() = 0;
	virtual void providerSlot58() = 0;
	virtual void providerSlot59() = 0;
	virtual void fill(_STL::list<Object *> *objects) = 0; // vtable +0xf0
};

void j_0001da34();
class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player) { union {void (*raw)(); bool(Rva2225E0Filter::*member)(Object*,Player*);} c;c.raw=&j_0001da34;return (this->*c.member)(object,player); }
};

class TransportContainModuleData
{
public:
	char pad000[0x17c]; unsigned m_exitDelay;
 float exitValue220()const{return *(const float*)((const char*)this+0x220);}
 Thing::KindOfMaskType *kindOfMask180() const
	{
		return reinterpret_cast<Thing::KindOfMaskType *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x180);
	}

	Thing::KindOfMaskType *kindOfMask198() const
	{
		return reinterpret_cast<Thing::KindOfMaskType *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x198);
	}

	void *createList() const
	{
		return *reinterpret_cast<void *const *>(
			reinterpret_cast<const char *>(this) + 0x200);
	}

	Bool keepStatus() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}

	Rva2225E0Filter *filter() const
	{
		return reinterpret_cast<Rva2225E0Filter *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x20c);
	}

	Bool applyPassengerDelay() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x210);
	}

	float passengerDelay() const
	{
		return *reinterpret_cast<const float *>(
			reinterpret_cast<const char *>(this) + 0x214);
	}

	Bool scalePassengerDelay() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0x21c);
	}
};

struct Coord3D;
class WeaponTemplate;
class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate*, const Object*, const Coord3D*);
};

extern "C" WeaponStore *g_bfmeRegistryAS;

class OpenContain
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected);
 virtual void onRemoving(Object* rider);
};

class TransportContain
{
public:
	// The BFME ContainModuleInterface view has these established slots.  The
	// body calls +0x58, +0xa0, +0xd8 and +0x100 directly through this view.
	virtual void containSlot00() = 0;
	virtual void containSlot01() = 0;
	virtual void containSlot02() = 0;
	virtual void containSlot03() = 0;
	virtual void containSlot04() = 0;
	virtual void containSlot05() = 0;
	virtual void containSlot06() = 0;
	virtual void containSlot07() = 0;
	virtual void containSlot08() = 0;
	virtual void containSlot09() = 0;
	virtual void containSlot10() = 0;
	virtual void containSlot11() = 0;
	virtual void containSlot12() = 0;
	virtual void containSlot13() = 0;
	virtual void containSlot14() = 0;
	virtual void containSlot15() = 0;
	virtual void containSlot16() = 0;
	virtual void containSlot17() = 0;
	virtual void containSlot18() = 0;
	virtual void containSlot19() = 0;
	virtual void containSlot20() = 0;
	virtual void containSlot21() = 0;
	virtual void containSlot22(Object *rider, Bool value) = 0; // +0x58
	virtual void containSlot23() = 0;
	virtual void containSlot24() = 0;
	virtual void containSlot25() = 0;
	virtual void containSlot26() = 0;
	virtual void containSlot27() = 0;
	virtual void containSlot28() = 0;
	virtual void containSlot29() = 0;
	virtual void containSlot30() = 0;
	virtual void containSlot31() = 0;
	virtual void containSlot32() = 0;
	virtual void containSlot33() = 0;
	virtual void containSlot34() = 0;
	virtual void containSlot35() = 0;
	virtual void containSlot36() = 0;
	virtual void containSlot37() = 0;
	virtual void containSlot38() = 0;
	virtual void containSlot39() = 0;
	virtual Bool containSlot40() const = 0; // +0xa0
	virtual void containSlot41() = 0;
	virtual void containSlot42() = 0;
	virtual void containSlot43() = 0;
	virtual void containSlot44() = 0;
	virtual void containSlot45() = 0;
	virtual void containSlot46() = 0;
	virtual void containSlot47() = 0;
	virtual void containSlot48() = 0;
	virtual void containSlot49() = 0;
	virtual void containSlot50() = 0;
	virtual void containSlot51() = 0;
	virtual void containSlot52() = 0;
	virtual void containSlot53() = 0;
	virtual void containSlot54(Object *rider) = 0; // +0xd8
	virtual void containSlot55() = 0;
	virtual void containSlot56() = 0;
	virtual void containSlot57() = 0;
	virtual void containSlot58() = 0;
	virtual void containSlot59() = 0;
	virtual void containSlot60() = 0;
	virtual void containSlot61() = 0;
	virtual void containSlot62() = 0;
	virtual void containSlot63() = 0;
	virtual Int getContainCount(Int argument) const = 0; // +0x100
	virtual void onContaining(Object *rider, Bool wasSelected);
 virtual void onRemoving(Object* rider);

private:
 unsigned char pad004[0xb4];
 unsigned m_extraSlotsInUse;
 unsigned m_exitFrame;
	TransportContainModuleData *getModuleData() const
	{
		return *reinterpret_cast<TransportContainModuleData *const *>(
			reinterpret_cast<const char *>(this) - 0x1c);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x18);
	}

	Bool payloadCreated() const
	{
		return *reinterpret_cast<const Bool *>(
			reinterpret_cast<const char *>(this) + 0xc0);
	}

	UnsignedInt &extraSlotsInUse() const
	{
		return *reinterpret_cast<UnsignedInt *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0xb8);
	}
};


class BFMEDrawableBoneQuery { public:int getPristineBonePositions(const char*,int,Coord3D*,Matrix3D*,int,int)const;};
enum CommandSourceType { COMMANDSOURCE_SCRIPT=2 };
class AICommandInterface {public:void aiIdle(CommandSourceType);};
void j_00030553();void j_0000da03();void j_0002dbfa();void j_00030d37();void j_0002a6e4();void j_000122ab();void j_00009b01();
class ExitCalls0022E340 { public:
 void attitude(int n){union{void(*raw)();void(ExitCalls0022E340::*member)(int);} c;c.raw=j_00030553;(this->*c.member)(n);}
 void mood(){union{void(*raw)();void(ExitCalls0022E340::*member)();} c;c.raw=j_0000da03;(this->*c.member)();}
 void scatter(Object* n){union{void(*raw)();void(ExitCalls0022E340::*member)(Object*);} c;c.raw=j_0002dbfa;(this->*c.member)(n);}
 void drawableRemove(unsigned n){union{void(*raw)();void(ExitCalls0022E340::*member)(unsigned);} c;c.raw=j_00030d37;(this->*c.member)(n);}
 void drawableValue(float n){union{void(*raw)();void(ExitCalls0022E340::*member)(float);} c;c.raw=j_0002a6e4;(this->*c.member)(n);}
 void status(int n){union{void(*raw)();void(ExitCalls0022E340::*member)(int);} c;c.raw=j_000122ab;(this->*c.member)(n);}
 unsigned id(){union{void(*raw)();unsigned(ExitCalls0022E340::*member)();} c;c.raw=j_00009b01;return (this->*c.member)();}
};
struct Rva00367E30Logic {char pad[0x3c];unsigned frame;unsigned getFrame()const{return frame;}};
extern Rva00367E30Logic* TheBfmeGameLogic;
void TransportContain::onRemoving(Object* rider) {
 ((OpenContain*)this)->OpenContain::onRemoving(rider);
 rider->clearDisabled(DISABLED_HELD); rider->clearModelCondition(88);
 const TransportContainModuleData* data=getModuleData();
 Object* owner=getObject();
 Drawable* ownerDrawable=owner->getDrawable();
 const AsciiString& bone=*(const AsciiString*)((const char*)data+0x170);
 if(!bone.isEmpty()) {
  Drawable* draw=getObject()->getDrawable();
  if(draw) {
   Coord3D bonePos,worldPos;
   if(((BFMEDrawableBoneQuery*)draw)->getPristineBonePositions(bone.str(),0,&bonePos,0,1,0)==1) {
    ((Thing*)getObject())->convertBonePosToWorldPos(&bonePos,0,&worldPos,0);
    ((Thing*)rider)->setPosition(&worldPos);
   }
  }
 }
 if(*(const bool*)((const char*)data+0x1fb)) ((Thing*)rider)->setOrientation(((Thing*)getObject())->getOrientation());
 extraSlotsInUse() -= rider->getTransportSlotCount()-1;
 if(getContainCount(0)==0) owner->clearModelCondition(86);
 rider->clearModelCondition(87);
 ExitCalls0022E340* ai=*(ExitCalls0022E340**)((char*)rider+0x204);
 if(ai) ((AICommandInterface*)((char*)ai+0x20))->aiIdle(COMMANDSOURCE_SCRIPT);
 if(*(const bool*)((const char*)data+0x1fc) && ai) ai->attitude(2);
 if((*(unsigned char*)((char*)getObject()+0x344)&1) && !(*(unsigned char*)((char*)rider+0x344)&1)) ((ExitCalls0022E340*)((char*)this-0x20))->scatter(rider);
 if(*(const bool*)((const char*)data+0x1fd) && ai) ai->mood();
 m_exitFrame=data->m_exitDelay+TheBfmeGameLogic->frame;
 Drawable* riderDrawable=rider->getDrawable();
 if(!(*(unsigned*)((char*)rider+0x94)&0x10000000) && ownerDrawable && riderDrawable) {
  ((ExitCalls0022E340*)ownerDrawable)->drawableRemove(((ExitCalls0022E340*)riderDrawable)->id());
  ((ExitCalls0022E340*)riderDrawable)->drawableValue(data->exitValue220());
 }
 bool first=false,second=false;
 const _STL::list<Object*>& passengers=*(_STL::list<Object*>*)((char*)this+0x18);
 for(_STL::list<Object*>::const_iterator it=passengers.begin();it!=passengers.end();++it) {
  Thing* passenger=(Thing*)*it;
  if(passenger->isKindOfMulti((const BitFlags<116>&)*data->kindOfMask180(),KINDOFMASK_NONE)) first=true;
  else if(passenger->isKindOfMulti((const BitFlags<116>&)*data->kindOfMask198(),KINDOFMASK_NONE)) second=true;
 }
 if(!first) ((ExitCalls0022E340*)owner)->status(4);
 if(!second) ((ExitCalls0022E340*)owner)->status(5);
 containSlot55();
 if(*(const bool*)((const char*)data+0x211) && riderDrawable && *(const float*)((const char*)data+0x218)!=0.0f && data->filter()->accepts(rider,0)) {
  if(((Thing*)rider)->isKindOf(KINDOF_BFME_6C) && rider->unidentified_001BFE20()) {
   _STL::list<Object*> objects;
   ((BfmeListProvider*)rider->unidentified_001BFE20())->fill(&objects);
   for(_STL::list<Object*>::iterator it=objects.begin();it!=objects.end();++it) {
    Object* o=*it;if(o) {Drawable* draw=o->getDrawable();if(draw)draw->bfmeDelayB((int)(*(const float*)((const char*)data+0x218)*0.03f));}
   }
  } else riderDrawable->bfmeDelayB((int)(*(const float*)((const char*)data+0x218)*0.03f));
 }
}
