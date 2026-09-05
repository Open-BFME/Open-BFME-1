// ?update@Rva002995E0@@QAEIXZ
// partial score=0.45 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

// Open-BFME5: address-derived body, retail 0x002995E0 size 309.
// IDENTITY NOT RECOVERED: class, member and field names are all address- or
// role-derived. This "this" pointer is offset +0x10 from the owning
// UpdateModule's own start (moduleData at this-0xc, object at this-8; three
// sibling thunk calls take (char*)this-0x10 as their receiver), so whatever
// real interface owns this override sits behind a second vtable following an
// UpdateModule primary base. The retail body reads Object::m_status90 bit
// 0x8000 to decide whether to look up a "StealthUpdate" module by NAMEKEY
// (Object::findModule) and test a byte at module+0x2d; it always returns the
// literal 5 (an UPDATE_SLEEP-style frame count).

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

enum NameKeyType { NAMEKEY_INVALID };

class NameKeyGenerator
{
public:
	Int nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	unsigned char m_pad_000[0x2d];
	unsigned char m_flag2D;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
	Module *findModule(NameKeyType key) const;

	unsigned char m_pad_000[0x90];
	UnsignedInt m_status90;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_pad_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

// The three thunked sibling calls all take the UpdateModule primary base
// (this - 0x10) as their receiver; only the address matters for the pins.
class Rva002995E0Base
{
public:
	void j000055a6();
	void j00017c79();
	void j0001085c();
};

struct Rva002995E0ModuleData
{
	unsigned char m_pad_000[0xc];
	UnsignedInt m_field0C;
	unsigned char m_pad_010[0x14 - 0x10];
	UnsignedInt m_field14;
};

class Rva002995E0
{
public:
	UnsignedInt update();

private:
	void *m_ownVtable;
	unsigned char m_pad_004[0x14 - 4];
	UnsignedInt m_field14;
	UnsignedInt m_field18;
	unsigned char m_pad_01C[4];
	UnsignedInt m_field20;
};

// ?update@Rva002995E0@@QAEIXZ
UnsignedInt Rva002995E0::update()
{
	Rva002995E0ModuleData *moduleData = *(Rva002995E0ModuleData **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);
	Bool found = false;

	if (object->m_status90 & 0x8000)
	{
		static Int s_key = TheNameKeyGenerator->nameToKey("StealthUpdate");
		Module *module = object->findModule((NameKeyType)s_key);
		if (module && module->m_flag2D)
			found = true;
	}

	UnsignedInt fieldCounter = m_field20;
	UnsignedInt frame = TheBfmeGameLogic->getFrame();

	if (fieldCounter != 0)
	{
		if (frame > moduleData->m_field14 + fieldCounter)
		{
			m_field20 = 0;
			object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 18), true);
			return 5;
		}
	}

	if (m_field18 == 0)
	{
		if (!found)
			return 5;
		m_field18 = frame;
		return 5;
	}

	if (!found)
	{
		if (m_field14 != 0)
			((Rva002995E0Base *)((char *)this - 0x10))->j000055a6();
		return 5;
	}

	if (m_field14 != 0)
		((Rva002995E0Base *)((char *)this - 0x10))->j00017c79();
	else if (frame > moduleData->m_field0C + m_field18)
		((Rva002995E0Base *)((char *)this - 0x10))->j0001085c();

	return 5;
}
