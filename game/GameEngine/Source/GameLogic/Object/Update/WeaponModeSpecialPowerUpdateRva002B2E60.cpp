// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern unsigned char g_bfmeTableDH[];

#include "ascii_string.h"

class ModuleData002B2E60
{
private:
	unsigned char m_pad[0x1d0];

public:
	AsciiString m_attribute;
	Int m_duration;
	Int m_weaponLock;
	union
	{
		UnsignedInt m_mask;
		unsigned char m_maskBytes[4];
	};
};

class Rva002B2E60WeaponModeSpecialPowerUpdate;

class FiringTracker
{
	friend class Rva002B2E60WeaponModeSpecialPowerUpdate;

	void coolDown(Bool forceReset);
};

#define OBJECT_TU_MEMBERS \
	void setWeaponLock(Int weaponSlot, Int lockType); \
	void actionA(Int condition); \
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
#include "../object.h"

class Gen001C9A10
{
public:
	void handle(Int condition);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class WeaponModeSpecialPowerUpdateBase
{
	protected:
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);
};

class UpdateModule : public WeaponModeSpecialPowerUpdateBase
{
public:
	using WeaponModeSpecialPowerUpdateBase::setWakeFrame;
};

class TailInterface002B2E60
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
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot40();
};

class Rva002B2E60WeaponModeSpecialPowerUpdate
{
public:
	void rva002B2E60(Int, Int, Int, Int, Int);
};

void Rva002B2E60WeaponModeSpecialPowerUpdate::rva002B2E60(
	Int, Int, Int, Int, Int)
{
	char *self = reinterpret_cast<char *>(this);
	Object *object = *reinterpret_cast<Object **>(self - 0x18);
	Int weaponLock = (*reinterpret_cast<ModuleData002B2E60 **>(self - 0x1c))
		->m_weaponLock;
	if (weaponLock != 3)
	{
		object->setWeaponLock(weaponLock, 2);
	}
	else
	{
		unsigned char *first = reinterpret_cast<unsigned char *>(
			*reinterpret_cast<ModuleData002B2E60 **>(self - 0x1c)) + 0x1dc;
		unsigned char *last = first + 4;
		Int total = 0;
		while (first < last)
		{
			total += g_bfmeTableDH[*first];
			++first;
		}
		if (total != 0)
		{
			for (Int i = 0; i < 0x1d; ++i)
			{
				if ((*reinterpret_cast<ModuleData002B2E60 **>(self - 0x1c))
					->m_mask & (1 << (i & 0x1f)))
					reinterpret_cast<Gen001C9A10 *>(object)->handle(i);
			}
		}
	}
	ModuleData002B2E60 *data =
		*reinterpret_cast<ModuleData002B2E60 **>(self - 0x1c);
	object->applyAttributeModifier(data->m_attribute, data->m_duration);
	reinterpret_cast<UpdateModule *>(self - 0x20)->setWakeFrame(
		object,
		static_cast<UpdateSleepTime>(
			(*reinterpret_cast<ModuleData002B2E60 **>(self - 0x1c))->m_duration));
	*reinterpret_cast<unsigned char *>(self + 0x18) = 1;
	reinterpret_cast<TailInterface002B2E60 *>(self + 4)->slot40();
	object->m_firingTracker->coolDown(true);
}
