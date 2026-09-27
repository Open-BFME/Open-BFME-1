// cl: /DNDEBUG /MD /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include

// Open-BFME5 conversions.
#include "Lib/BaseType.h"


class BfmeX1011;

class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};

extern BfmeLook1011 *g_bfmeLook1011;

class BfmeA1011
{
public:
	void bfmeGo1011A(int a, int b, int c, int d, int e);
	void bfmeSend1011(int a, int b, int c, int d, int e);

	char m_bfmePad[0x8c];
	int m_bfmeId;
	char m_bfmePad2[0x39];
	char m_bfmeFlag;
};

void BfmeA1011::bfmeGo1011A(int a, int b, int c, int d, int e)
{
	BfmeX1011 *x = g_bfmeLook1011->bfmeFind1011(m_bfmeId);

	if (x && m_bfmeFlag)
		return;

	bfmeSend1011(a, b, c, d, e);
}

class BfmeHeld1011
{
public:
	virtual void bfmeRelease1011(int n);
};

struct BfmeSlot1011
{
	char m_bfmePad[0x14];
	BfmeHeld1011 *m_bfmeHeld;
};

class BfmeB1011
{
public:
	void bfmeGo1011B(void *a, BfmeHeld1011 *b);
	BfmeSlot1011 *bfmeFind1011B(void *a);
	void **bfmeAdd1011(void *a);

	BfmeSlot1011 *m_bfmeEnd;
};

void BfmeB1011::bfmeGo1011B(void *a, BfmeHeld1011 *b)
{
	BfmeSlot1011 *s = bfmeFind1011B(a);

	if (s != m_bfmeEnd) {
		BfmeHeld1011 *h = s->m_bfmeHeld;

		if (h)
			h->bfmeRelease1011(1);

		s->m_bfmeHeld = b;
		return;
	}

	*bfmeAdd1011(a) = b;
}

class SpecialPowerTemplate;
struct Rva002A8260Data {
	char pad000[0x1d8]; const SpecialPowerTemplate* m_specialPowerTemplate;
	char pad1dc[0x44]; int m_unpackTime;
	char pad224[0x1c]; bool m_skipPackingWithNoTarget;
	char pad241[0xd]; bool field24e;
};
class SpecialAbilityUpdate;
class SpecialPowerModuleInterface {
public:
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
	virtual void slot3c(bool);
};
enum SpecialPowerType { Rva002A8260PowerDummy };
class Object
{
public:
	void setStatusBit(int,bool);
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate*) const;
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType) const;
};
class Gen_002A6DE0
{
public:
	void bfmeGo1274();
};
class BfmeThingEW
{
public:
	void bfmeSwapEW();
};
class BfmeThingBZ
{
public:
	void bfmeGoBZ();
};
enum CommandSourceType { Rva002A8260CommandDummy };
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType);
};
class UpdateModule
{
public:
	void setWakeFrame(Object*,int);
};
class SpecialAbilityUpdate
{
public:
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
	virtual void slot2c(bool,bool);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot3c();
	Rva002A8260Data* data; Object* object;
};
class Rva002A8260AI
{
public:
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
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual bool slot134();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual int slot200();
};
template<class T> inline T& at(void* p,int n) { return *(T*)((char*)p+n); }
class Rva002A8260
{
public:
	char pad000[4]; int field004; int field008; int field00c; int field010;
	char pad014[0x74]; int field088; char pad08c[4]; Coord3D field090;
	char pad09c[0xc]; int field0a8; char pad0ac[8]; unsigned field0b4;
	char pad0b8[4]; bool field0bc,field0bd,field0be,field0bf;
	bool field0c0,field0c1,field0c2,field0c3,field0c4,field0c5;
	SpecialAbilityUpdate* full() { return (SpecialAbilityUpdate*)((char*)this-0x20); }
};

void BfmeA1011::bfmeSend1011(int powerArg, int targetArg, int positionArg, int options, int count)
{
	Rva002A8260 *self=(Rva002A8260*)this;
	Rva002A8260Data* data=self->full()->data;
	if(data->m_specialPowerTemplate!=(const SpecialPowerTemplate*)powerArg) return;
	m_bfmeId=0;
	self->field090.zero();
	self->field0b4=options;
	self->field0a8 = 0;
	self->field004 = 0;
	self->field00c = 0;
	self->field088 = 0;
	self->field008 = 0;
	self->field010 = 3;
	self->field0c0 = false;
	self->field0c1 = false;
	self->field0c2 = false;
	self->field0c4 = false;
	self->field0c5 = false;
	SpecialAbilityUpdate* base=(SpecialAbilityUpdate*)((char*)self-0x20);
	((Gen_002A6DE0*)base)->bfmeGo1274();
	bool option=(self->field0b4&0x20000000)!=0;
	if(targetArg) m_bfmeId=at<int>((Object*)targetArg,0x74);
	else if(positionArg) { self->field090=*(const Coord3D*)positionArg; self->field0a8=count; }
	else if(data->field24e) {
		base->slot3c();
		const SpecialPowerTemplate* modulePower=base->data->m_specialPowerTemplate;
		SpecialPowerModuleInterface* module=base->object->getSpecialPowerModule(modulePower);
		if(module) module->slot3c(false);
		base->slot2c(false,true); return;
	}
	Rva002A8260AI* ai=at<Rva002A8260AI*>(self->full()->object,0x204);
	if(!ai) return;
	self->full()->object->setStatusBit(23,true);
	at<bool>(ai,0x338)=true;
	if(ai->slot200()==2) {
		if(!ai->slot134() && !option) {
			((BfmeThingEW*)ai)->bfmeSwapEW();
			((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)2);
		}
	} else {
		((BfmeThingEW*)ai)->bfmeSwapEW();
		((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)2);
	}
	if(!at<int>(ai,0x34)) ((BfmeThingBZ*)ai)->bfmeGoBZ();
	((AICommandInterface*)((char*)ai+0x20))->aiIdle((CommandSourceType)2);
	self->field0bf=!targetArg && !positionArg;
	if(!data->m_unpackTime || (self->field0bf && data->m_skipPackingWithNoTarget)) self->field010 = 4;
	self->field0bc = true;
	self->field0bd = true;
	SpecialAbilityUpdate* disable=self->full()->object->findSpecialAbilityUpdate((SpecialPowerType)26);
	if(disable && disable!=(SpecialAbilityUpdate*)((char*)self-0x20)) disable->slot2c(false,true);
	disable=self->full()->object->findSpecialAbilityUpdate((SpecialPowerType)22);
	if(disable && disable!=(SpecialAbilityUpdate*)((char*)self-0x20)) disable->slot2c(false,true);
	disable=self->full()->object->findSpecialAbilityUpdate((SpecialPowerType)23);
	if(disable && disable!=(SpecialAbilityUpdate*)((char*)self-0x20)) disable->slot2c(false,true);
	((UpdateModule*)base)->setWakeFrame(self->full()->object,1);
}
