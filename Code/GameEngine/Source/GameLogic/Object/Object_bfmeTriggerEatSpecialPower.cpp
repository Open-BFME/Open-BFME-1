// cl: /DNDEBUG /MD /EHsc

// Retail 0x001C49C0. The sole caller is AIUpdateInterface code and passes the
// AI's Object as the argument. The immediate SpecialPowerType is 0x71, which
// the retail SpecialPower name table identifies as SPECIAL_EAT; command source
// 2 is CMD_FROM_AI.

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum SpecialPowerType
{
	SPECIAL_EAT = 0x71
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class SpecialPowerTemplate;
class Object;

class SpecialPowerStore
{
public:
	Bool canUseSpecialPower(Object *object,
		const SpecialPowerTemplate *specialPowerTemplate);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class SpecialPowerModuleInterface
{
public:
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot01() = 0;
	virtual void bfmeSlot02() = 0;
	virtual void bfmeSlot03() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot05() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
	virtual void bfmeSlot07() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot11() = 0;
	virtual void bfmeSlot12() = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *location,
		UnsignedInt commandOptions) = 0;
};

class Object
{
private:
	unsigned char m_unreconstructed00[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed44[0x1a4 - 0x44];
	UnsignedInt m_disabledMask;

public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate) const;
	void bfmeTriggerEatSpecialPower(const Object *target);
};

void Object::bfmeTriggerEatSpecialPower(const Object *target)
{
	SpecialPowerModuleInterface *typeModule =
		findSpecialPowerModuleInterface(SPECIAL_EAT);
	if (typeModule == 0)
		return;

	const SpecialPowerTemplate *specialPowerTemplate =
		typeModule->getSpecialPowerTemplate();
	if (m_disabledMask != 0)
		return;

	if (!TheSpecialPowerStore->canUseSpecialPower(this, specialPowerTemplate))
		return;

	SpecialPowerModuleInterface *module =
		getSpecialPowerModule(specialPowerTemplate);
	if (module != 0)
		module->doSpecialPowerAtLocation(&target->m_position, CMD_FROM_AI);
}
