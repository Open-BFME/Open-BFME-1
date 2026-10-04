// cl: /DNDEBUG /MD /EHsc
// Open-BFME: HordeAIUpdate::update, retail 0x002C4790.
//
// The constructor installs the HordeAIUpdate vtable at +0x10. Its slot zero
// points at this body, while the primary AI vtable keeps isIdle at slot 96.
// The HordeAIUpdate module factory and the constructor identify the class.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Object;

template <int N>
class HordeAIUpdateVirtualSlots : public HordeAIUpdateVirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class HordeAIUpdateVirtualSlots<0>
{
};

class HordeContainInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void updateFormation(int value) = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void slot90() = 0;
	virtual void notifyMember(Object *object) = 0;
	virtual Bool slot98() = 0;
	virtual Bool slot9c() = 0;
	virtual void slota0() = 0;
	virtual void slota4() = 0;
	virtual void slota8() = 0;
	virtual void slotac() = 0;
	virtual void slotb0() = 0;
	virtual void slotb4() = 0;
	virtual void slotb8() = 0;
	virtual void slotbc() = 0;
	virtual void slotc0() = 0;
	virtual void slotc4() = 0;
	virtual void update() = 0;
	virtual void slotcc() = 0;
	virtual void slotd0() = 0;
	virtual void slotd4() = 0;
	virtual void slotd8() = 0;
	virtual void slotdc() = 0;
	virtual void slote0() = 0;
	virtual void slote4() = 0;
	virtual void slote8() = 0;
	virtual void slotec() = 0;
	virtual void slotf0() = 0;
	virtual void slotf4() = 0;
	virtual void slotf8() = 0;
	virtual void slotfc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual Bool slot108() = 0;
};

class ContainModuleInterface
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
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9c() = 0;
	virtual void slota0() = 0;
	virtual void slota4() = 0;
	virtual void slota8() = 0;
	virtual void slotac() = 0;
	virtual void slotb0() = 0;
	virtual void slotb4() = 0;
	virtual void slotb8() = 0;
	virtual void slotbc() = 0;
	virtual void slotc0() = 0;
	virtual void slotc4() = 0;
	virtual void slotc8() = 0;
	virtual void slotcc() = 0;
	virtual void slotd0() = 0;
	virtual void slotd4() = 0;
	virtual void slotd8() = 0;
	virtual void slotdc() = 0;
	virtual void slote0() = 0;
	virtual void slote4() = 0;
	virtual void slote8() = 0;
	virtual void slotec() = 0;
	virtual void slotf0() = 0;
	virtual void slotf4() = 0;
	virtual void slotf8() = 0;
	virtual void slotfc() = 0;
	virtual void *getContainerInterface(int value) = 0;
};

class Object
{
public:
	unsigned char m_padding00[0x90];
	unsigned char m_status;
	unsigned char m_padding91[0x1fc - 0x91];
	ContainModuleInterface *m_contain;
};

class BfmeHordeOwner
{
public:
};

class GameLogic
{
public:
	unsigned char m_padding00[0x3c];
	UnsignedInt m_frame;
};

// The retail global at 0x012F0898; dir32_addresses.csv records it as
// ?TheGameLogic@@3PAVGameLogic@@A, the name the rest of the tree uses.
extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();

private:
	UnsignedInt m_14;
	UnsignedInt m_18;
	UnsignedInt m_1c;
};

class BfmeHordeMember : public HordeAIUpdateVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;

	UnsignedInt m_04;
	Object *m_object;
};

class HordeAIUpdateIface1
{
public:
	virtual void slot00() = 0;
};

class HordeAIUpdateIface3
{
public:
	virtual void slot00() = 0;
};

class HordeAIUpdateIface4
{
public:
	virtual void slot00() = 0;
	unsigned char m_padding04[0x318];
};

class HordeAIUpdateIface5
{
public:
	virtual void slot00() = 0;
};

class HordeAIUpdate : public BfmeHordeMember,
	public HordeAIUpdateIface1,
	public AIUpdateInterface,
	public HordeAIUpdateIface3,
	public HordeAIUpdateIface4,
	public HordeAIUpdateIface5
{
public:
	virtual UpdateSleepTime update();
};

// Retail reaches the base update through the 5-byte ILT 0x00028772
// (?j_00028772@@YAXXZ), not the body itself. The ILT is entered with ECX at the
// AIUpdateInterface subobject (this + 0x10); passing it through a __fastcall
// pointer keeps ECX as the only register argument.
extern void j_00028772();
// Retail enters these two through their 5-byte ILTs
// (?j_00044774@@YAXXZ and ?j_00023727@@YAXXZ), not the bodies themselves, and
// each ILT is entered with ECX holding the thiscall object. A member pointer
// initialised from the ILT address therefore reproduces the direct call the
// object file makes, with no linker alias standing in for a name that nothing
// defines.
extern void j_00044774();
extern void j_00023727();

// The formation-refresh predicate this body used to call is a member of the
// polymorphic BfmeHordeMember, and a pointer-to-member of a polymorphic class
// can still need virtual dispatch, so the compiler emits an indirect call
// through it. This plain, non-polymorphic holder takes the same signature and
// keeps the single direct call the thunk receives.
class Ilt44774Holder
{
};

// ?update@HordeAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime HordeAIUpdate::update()
{
	Object *object = m_object;
	ContainModuleInterface *contain = object->m_contain;
	HordeContainInterface *horde = contain->getHordeContainInterface();
	if (horde->slot108() == 1)
		return ((UpdateSleepTime (__fastcall *)(void *))j_00028772)((char *)this + 0x10);

	{
		contain = object->m_contain;
		void *container = contain->getContainerInterface(0);
		Bool ready = horde->slot9c();
		if (!container)
		{
			if (isIdle() && ready && !(object->m_status & 8))
				horde->notifyMember(object);
		}
	}

	typedef Bool (Ilt44774Holder::*BlocksFormationRefresh)();
	union { void (*fn)(); BlocksFormationRefresh call; } blocks = { j_00044774 };

	if (!(((Ilt44774Holder *)this)->*blocks.call)())
	{
		UnsignedInt frame = TheGameLogic->m_frame;
		typedef UnsignedInt (BfmeHordeOwner::*FormationRefreshValue)();
		union { void (*fn)(); FormationRefreshValue call; } refresh = { j_00023727 };
		if ((((BfmeHordeOwner *)m_object)->*refresh.call)() < frame - 5)
		{
			if (horde->slot98())
			{
				horde->updateFormation(1);
			}
		}
	}
	horde->update();
	return ((UpdateSleepTime (__fastcall *)(void *))j_00028772)((char *)this + 0x10);
}
