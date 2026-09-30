// cl: /DNDEBUG /MD /EHs-c-
// stlport
// Retail RVA 0x00222640, 187 bytes, ret 4 at +0xB8 (carved boundary).
//
// Callees (tools/callees.py): DieMuxData::isDieApplicable via ILT 0x000357D8,
// Gen_00411DD0::bfmeSet via ILT 0x00008337 and GameLogic::destroyObject via
// ILT 0x0001D0DE. The rider loop calls Object vtable +0x28 (getDrawable, as in
// GarrisonContain_onContaining.cpp) twice and passes true to bfmeSet. No caller
// proves the owner or method name, so the owner keeps an address-derived name.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

class DamageInfo;

class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Gen_00411DD0 *getDrawable() = 0;
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern const float BfmeZeroRange;
extern GameLogic *TheBfmeGameLogic;

struct Rva00222640ModuleData
{
	unsigned char m_pad000[8];
	DieMuxData m_dieMuxData;
	unsigned char m_pad009[0x13c - 9];
	float m_damagePercent;
	unsigned char m_pad140[0x12];
	Bool m_flag152;
};

class Rva00222640ContainBase
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36)
	virtual void slot37(Bool value);
	S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
	S(70) S(71) S(72) S(73) S(74) S(75) S(76)
#undef S
	virtual void slot77();
};

class Rva00222640ModuleBase
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23)
#undef S
	virtual void slot24();
};

class Rva00222640Owner
{
public:
	void dispatch(const DamageInfo *damageInfo);

private:
	const Rva00222640ModuleData *getModuleData() const
	{
		return *(const Rva00222640ModuleData *const *)((const char *)this - 0x24);
	}
	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x20);
	}
	Rva00222640ContainBase *getContain()
	{
		return (Rva00222640ContainBase *)((char *)this - 8);
	}
	Rva00222640ModuleBase *getModule()
	{
		return (Rva00222640ModuleBase *)((char *)this - 0x28);
	}

	unsigned char m_pad00[0x10];
	_STL::list<Object *> m_containList;
	unsigned char m_pad14[0x7c];
	Bool m_flag;
};

void Rva00222640Owner::dispatch(const DamageInfo *damageInfo)
{
	m_flag = true;
	if (!getModuleData()->m_dieMuxData.isDieApplicable(getObject(), damageInfo))
		return;

	if (getModuleData()->m_flag152)
	{
		if (getModuleData()->m_damagePercent > BfmeZeroRange)
			getContain()->slot77();
		getModule()->slot24();
		getContain()->slot37(false);
		return;
	}

	for (_STL::list<Object *>::iterator it = m_containList.begin(); it != m_containList.end(); )
	{
		Object *rider = *it;
		++it;
		if (rider != 0)
		{
			if (rider->getDrawable() != 0)
				rider->getDrawable()->bfmeSet(true);
			TheBfmeGameLogic->destroyObject(rider);
		}
	}
}
