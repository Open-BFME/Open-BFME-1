// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?onRemoving@TransportContain@@UAEXPAVObject@@@Z
// Open-BFME: TransportContain::onRemoving, retail 0x0022E340, 987 bytes.
//
// Identity: TransportContain's ContainModuleInterface vtable 0x010AD268 slot 18
// (+0x48) reaches this body through ILT 0x00041E34; the same slot of
// OpenContain's secondary vtable 0x010AC038 is the matched
// OpenContain::onRemoving (0x00227DC0), which this body calls first as its
// base (ILT 0x00032E61). Slot 17 is TransportContain::onContaining (0x0022DD10).
// The body is the Zero Hour TransportContain::onRemoving (exit bone, orient,
// slot count, loaded condition, AI attitude/mood, scatter, exit delay) with a
// BFME tail: model-condition bits 86/87/88, a drawable hand-off, a passenger
// kind-of scan and the passenger fade driven by module data +0x211/+0x218 (the
// FieldParse keys FadePassengerOnExit and ExitFadeTime).
//
// `this` is the ContainModuleInterface subobject: module data is at this-0x1c,
// the owning Object at this-0x18 and the OpenContain object at this-0x20.
// Members name_oracle cannot witness keep their offsets in their names.
//
// Codegen notes: the exit delay is `TheGameLogic->getFrame() + d->m_exitDelay`
// through Zero Hour's out-of-class inline getFrame(), which loads the frame
// first as retail does; the orient-on-exit flag is read through an inline
// accessor, which is what keeps the Object in EDI and the module data in EBP.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty()const{return !m_data||!m_data->length;}
#include "ascii_string.h"
struct Coord3D {float x,y,z;};
class Matrix3D;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
// Retail destroys the passenger list through ILT 0x0000E68D (0x000CEBD0).
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
	KINDOF_BFME_6C = 0x6c
};

// ILT 0x00046A1F -> 0x00410D80, a Drawable member taking a frame count.
void j_00046a1f();
class Drawable
{
public:
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
	};

	typedef KindOfMask<192> KindOfMaskType;
	Bool isKindOfMulti(const BitFlags<116>&,const BitFlags<116>&) const;
};

enum DisabledType { DISABLED_HELD=3 };
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

	struct ModelFlags { _STL::bitset<320> bits; };
	char pad004[0x10c];
	ModelFlags m_modelConditionFlags;

	bool clearDisabled(DisabledType);
	__forceinline void clearModelCondition(unsigned bit) { unsigned &f=((unsigned*)&m_modelConditionFlags)[bit>>5]; if(f&(1u<<(bit&31))) {f&=~(1u<<(bit&31));notifyModelConditionChanged();} }
	void notifyModelConditionChanged();
	Int getTransportSlotCount() const;
	void *unidentified_001BFE20() const;
};

// The provider returned by Object::unidentified_001BFE20 fills a list of
// objects through its vtable slot +0xf0.
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

// Module data +0x20c: its member at 0x003A04A0 (ILT 0x0001DA34) decides
// whether the rider fades.
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
	const AsciiString& exitBone()const{return *(const AsciiString*)((const char*)this+0x170);}
	Bool orientLikeContainerOnExit()const{return *(const Bool*)((const char*)this+0x1fb);}
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

	Rva2225E0Filter *filter() const
	{
		return reinterpret_cast<Rva2225E0Filter *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0x20c);
	}
};

class OpenContain
{
public:
	virtual void onRemoving(Object* rider);
};

class TransportContain
{
public:
	// The BFME ContainModuleInterface view; the body calls +0xdc and +0x100.
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

	UnsignedInt &extraSlotsInUse() const
	{
		return *reinterpret_cast<UnsignedInt *>(
			const_cast<char *>(reinterpret_cast<const char *>(this)) + 0xb8);
	}
};

class BFMEDrawableBoneQuery { public:int getPristineBonePositions(const char*,int,Coord3D*,Matrix3D*,int,int)const;};
enum CommandSourceType { COMMANDSOURCE_SCRIPT=2 };
class AICommandInterface {public:void aiIdle(CommandSourceType);};

// Calls this body makes through ILT thunks whose targets have no proven
// signature under their current ledger names; the helper names say what the
// Zero Hour twin does at the same point.
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

class GameLogic { public: UnsignedInt getFrame( void ); private: char pad[0x3c]; UnsignedInt m_frame; };
inline UnsignedInt GameLogic::getFrame( void ) { return m_frame; }
extern GameLogic *TheGameLogic;

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
 if(data->orientLikeContainerOnExit()) ((Thing*)rider)->setOrientation(((Thing*)getObject())->getOrientation());
 extraSlotsInUse() -= rider->getTransportSlotCount()-1;
 if(getContainCount(0)==0) owner->clearModelCondition(86);
 rider->clearModelCondition(87);
 ExitCalls0022E340* ai=*(ExitCalls0022E340**)((char*)rider+0x204);
 if(ai) ((AICommandInterface*)((char*)ai+0x20))->aiIdle(COMMANDSOURCE_SCRIPT);
 if(*(const bool*)((const char*)data+0x1fc) && ai) ai->attitude(2);
 if((*(unsigned char*)((char*)getObject()+0x344)&1) && !(*(unsigned char*)((char*)rider+0x344)&1)) ((ExitCalls0022E340*)((char*)this-0x20))->scatter(rider);
 if(*(const bool*)((const char*)data+0x1fd) && ai) ai->mood();
 m_exitFrame=TheGameLogic->getFrame()+data->m_exitDelay;
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
