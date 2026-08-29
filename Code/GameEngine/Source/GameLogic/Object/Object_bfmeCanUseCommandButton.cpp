// cl: /DNDEBUG /MD /EHsc

// Open-BFME: retail 0x001C4A30. A button with a special-power template must
// have a matching module on this Object, and the exact button pointer must be
// present in the Object's current 20-slot command set.

typedef int Int;
typedef bool Bool;

class AsciiString {};
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
private:
	unsigned char m_unreconstructed[0x34];
	const SpecialPowerTemplate *m_specialPower;

public:
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPower;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate) const;
	const AsciiString &getCommandSetString() const;
	Bool bfmeCanUseCommandButton(const CommandButton *button) const;
};

Bool Object::bfmeCanUseCommandButton(const CommandButton *button) const
{
	const SpecialPowerTemplate *power = button->getSpecialPowerTemplate();
	if (power != 0 && getSpecialPowerModule(power) == 0)
		return false;

	const CommandSet *set = TheControlBar->findCommandSet(getCommandSetString());
	if (set != 0)
	{
		for (Int index = 0; index < 20; ++index)
		{
			if (set->getCommandButton(index) == button)
				return true;
		}
	}
	return false;
}
