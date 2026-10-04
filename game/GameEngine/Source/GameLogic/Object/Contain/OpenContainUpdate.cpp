// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: OpenContain::update at retail 0x00225600.
// The update interface is a secondary base at +0x10 in the BFME object.

extern void j_0002191d();
extern void j_00004953();
extern void j_0000ba50();

typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMaskType;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum ModelConditionFlagType
{
	MODELCONDITION_DOOR_1_OPENING = 0x00200000,
	MODELCONDITION_DOOR_1_CLOSING = 0x00400000
};

class Object
{
public:
	__forceinline void openContainUpdateClearAndSetModelConditionState(ModelConditionFlagType clearFlags,
		ModelConditionFlagType setFlags)
	{
		if (m_conditionFlags & clearFlags)
			goto set_flags;
		if (m_conditionFlags & setFlags)
			return;
	set_flags:
		// MSVC 7.1 does not emit the retail EDX allocation here. Retail writes
		// both values after it computes the cleared and set masks.
		__asm {
			mov edx, [ecx+0x110]
			and edx, 0xffdfffff
			mov eax, edx
			or eax, 0x00400000
			mov [ecx+0x110], edx
			mov [ecx+0x110], eax
		}
		// Retail calls this through the ILT thunk at 0x2191D.
		typedef void (Object::*Fn)();
		union { void (*fn)(); Fn call; } u = { j_0002191d };
		(this->*u.call)();
	}

	char m_pad00[0x110];
	UnsignedInt m_conditionFlags;
};

class OpenContainPrimaryBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void monitorConditionChanges();

	char m_pad04[4];
	Object *m_object;
	UnsignedInt m_pad0C;
};

class OpenContainUpdateInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// The two ILT-routed calls below go through thiscall member pointers. MSVC 7.1
// only folds such a constant into a direct `mov ecx, this; call thunk` when the
// class of the member function has no bases, so the calls are routed through
// this base-less view of `this` rather than through OpenContain itself.
class OpenContainEntry225600
{
public:
	void pruneDeadWanters();
	void finishUpdate();
};

class OpenContain : public OpenContainPrimaryBase, public OpenContainUpdateInterface
{
public:
	virtual UpdateSleepTime update();

private:
	char m_pad14[0x48];
	UnsignedInt m_objectEnterExitInfo;
	char m_pad60[0x0C];
	UnsignedInt m_doorCloseCountdown;
	char m_pad70[4];
	PlayerMaskType m_playerEnteredMask;
};

UpdateSleepTime OpenContain::update()
{
	typedef void (OpenContainEntry225600::*Fn)();
	OpenContainEntry225600 *entry = (OpenContainEntry225600 *)this;

	m_playerEnteredMask = 0;
	monitorConditionChanges();

	if (m_doorCloseCountdown)
	{
		--m_doorCloseCountdown;
		if (m_doorCloseCountdown == 0)
			m_object->openContainUpdateClearAndSetModelConditionState(
				MODELCONDITION_DOOR_1_OPENING,
				MODELCONDITION_DOOR_1_CLOSING);
	}

	if (m_objectEnterExitInfo)
	{
		union { void (*fn)(); Fn call; } prune = { j_00004953 };
		(entry->*prune.call)();
	}

	{
		union { void (*fn)(); Fn call; } finish = { j_0000ba50 };
		(entry->*finish.call)();
	}
	return UPDATE_SLEEP_NONE;
}
