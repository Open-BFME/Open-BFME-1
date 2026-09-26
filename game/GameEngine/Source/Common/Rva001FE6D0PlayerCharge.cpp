// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE6D0, 86 bytes.  This is the primary-module side of the
// adjacent secondary-interface family at 0x001FE5A0/0x001FE600/0x001FE670:
// ObjectModule's object is at +0x08, the polymorphic value interface is at
// +0x20, and the rounded amount is retained at +0x38.
//
// The retail callees pin the operation: Object::getControllingPlayer at
// 0x00020824, CRT ceil through the import at 0x01359394, and
// Money::withdraw at 0x00041894. GettingBuiltBehavior's constructor at
// 0x001FE380 and destructor at 0x001FEB50 establish this family and the
// secondary-interface vtable 0x010A45E0 at +0x20. The local owner spelling
// remains address-derived; m_value is a view of that real secondary base.

typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// MSVC 7.1's x87 conversion is part of the retail shape.  The inline helper is
// the same compiler-level operation used by the source tree's REAL_TO_INT
// family; measured direct C++ casts emit __ftol2 instead of retail's dword
// fistp, while /QIfist emits a qword store. The upstream basetype.h helper
// and matched 0x00069790/13 body independently establish this exact operation.
__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, bool playSound);
};

class Player
{
public:
	unsigned char m_unreconstructed_00[0x48];
	Money m_money;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva001FE6D0ValueInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual Real slot2C(Player *player);
};

class Rva001FE6D0Owner
{
public:
	void withdrawPlayerCost();

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
	unsigned char m_unreconstructed_0C[0x14];
	Rva001FE6D0ValueInterface m_value;
	unsigned char m_unreconstructed_24[0x14];
	UnsignedInt m_lastAmount;
};

void Rva001FE6D0Owner::withdrawPlayerCost()
{
	Object *object = m_object;
	if (!object)
		return;

	Player *player = object->getControllingPlayer();
	if (!player)
		return;

	UnsignedInt amount = fast_float2long_round(
		(Real)ceil((double)m_value.slot2C(player)));
	m_lastAmount = amount;
	player->m_money.withdraw(amount, true);
}
