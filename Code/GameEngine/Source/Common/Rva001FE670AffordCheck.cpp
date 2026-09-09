// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE670, 71 bytes.  Affordability test on the secondary value
// interface of the family at 0x001FE380/0x001FE5A0/0x001FE600/0x001FE6D0:
// `this` is the interface embedded at owner+0x20, so the owner's object
// pointer at +0x08 is reached through this-0x18.  The cost comes from the
// same virtual slot 0x2C that the withdrawal body at 0x001FE6D0 calls, is
// rounded through the CRT ceil import at 0x01359394, and is compared against
// Money::countMoney at Player+0x4C.  The comparison is unsigned, which is
// what gives retail the sbb/inc form instead of a setge.
//
// The x87 conversion is the same compiler-level operation the source tree's
// REAL_TO_INT family uses and that the 0x001FE6D0 body needed: a direct C++
// cast emits __ftol2, and /QIfist emits a qword fistp, while retail stores a
// dword.

typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

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
	unsigned char m_unreconstructed_00[4];
	UnsignedInt m_money;
};

class Player
{
public:
	unsigned char m_unreconstructed_00[0x48];
	Money m_money;
};

class Rva001FE670ValueInterface
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

	bool canAffordCost(Player *player);
};

bool Rva001FE670ValueInterface::canAffordCost(Player *player)
{
	if (*(void **)((char *)this - 0x18) == 0)
		return false;

	if (player == 0)
		return false;

	UnsignedInt money = player->m_money.m_money;
	UnsignedInt cost = fast_float2long_round((Real)ceil((double)slot2C(player)));

	return money >= cost;
}
