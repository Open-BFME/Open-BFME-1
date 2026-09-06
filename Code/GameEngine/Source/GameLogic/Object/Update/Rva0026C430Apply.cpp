// stlport
// Scratch reconstruction for retail 0x0026C430.
// The final source must retain the observed ToggleMountedSpecialAbilityUpdate
// base layout and use the already-landed BFME helper identities.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

template <int NUMBITS>
class BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

enum ModelConditionFlagType
{
	MODELCONDITION_TOGGLE_MOUNTED = 248
};

class SpecialPowerTemplate;
class ModuleData;

// The target calls the ninth slot of the ModuleInterface subobject at +0x20.
// Keep all preceding slots so the indirect call is a real interface dispatch.
class ModuleInterface
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
	virtual Bool canToggle(UnsignedInt);

	unsigned char m_data[196];
};

class ToggleMountedSpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad00[0x1d8];
	SpecialPowerTemplate *m_specialPowerTemplate;
};

enum CommandSourceType
{
	COMMAND_SOURCE_AI = 2
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void doSpecialPower(UnsignedInt) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType commandSource);
};

class AIPrimaryInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	virtual void slot91() = 0;
	virtual void slot92() = 0;
	virtual void slot93() = 0;
	virtual void slot94() = 0;
	virtual void slot95() = 0;
	virtual void slot96() = 0;
	virtual Bool isAttacking() const = 0;
	unsigned char m_pad00[0x1c];
};

class AIUpdateInterface : public AIPrimaryInterface, public AICommandInterface
{
};

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *) const;
	Int bfmeHasSignificantPreferredLocomotorHeight() const;
	void setStatusBit(Int bit, Bool set);
	void notifyModelConditionChanged();

	unsigned char m_pad00[0x110];
	BitFlags<288> m_modelConditionFlags;
	unsigned char m_pad134[0xd0];
	AIUpdateInterface *m_ai;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Rva0026C430Owner
{
public:
	void apply(Object *object);

private:
	void *m_vtable00;
	ToggleMountedSpecialAbilityUpdateModuleData *m_moduleData;
	unsigned char m_pad08[0x18];
	ModuleInterface m_moduleInterface;
	UnsignedInt m_lastFrame;
};

// ?apply@Rva0026C430Owner@@QAEXPAVObject@@@Z
void Rva0026C430Owner::apply(Object *object)
{
	if (!m_moduleInterface.canToggle(0))
		return;

	AIUpdateInterface *ai = object->m_ai;
	if (ai == 0)
		return;

	ToggleMountedSpecialAbilityUpdateModuleData *data = m_moduleData;
	SpecialPowerModuleInterface *power = object->getSpecialPowerModule(
		*(SpecialPowerTemplate **)((char *)data + 0x1d8));
	if (power != 0)
		power->doSpecialPower(1);
	if ((unsigned char)object->bfmeHasSignificantPreferredLocomotorHeight() != 0 ||
		ai->isAttacking())
	{
		ai->aiIdle(COMMAND_SOURCE_AI);
	}

	m_lastFrame = TheBfmeGameLogic->m_frame;
	object->setStatusBit(15, true);
	object->setStatusBit(16, true);

	if (!object->m_modelConditionFlags.test(
		MODELCONDITION_TOGGLE_MOUNTED))
	{
		object->m_modelConditionFlags.set(
			MODELCONDITION_TOGGLE_MOUNTED);
		object->notifyModelConditionChanged();
	}
}
