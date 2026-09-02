// cl: /O2 /Ob0

class AsciiString;
class Object;
class CommandSet;
class CommandButton;
class ControlBar;

class Drawable
{
public:
	char m_padding[0xFC];
	Object *m_object;
};

class Object
{
public:
	const AsciiString &getCommandSetString() const;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

class SpecialPowerTemplate
{
public:
	char m_padding[0x14];
	unsigned int m_id;
};

class Overridable
{
public:
	void *m_unused;
	Overridable *m_next;

	const Overridable *friend_getFinalOverride() const;
};

class CommandButton
{
public:
	char m_padding0[0x10];
	int m_commandType;
	char m_padding1[0x20];
	Overridable *m_specialPower;
};

#define RVA005A7E20_SLOT(n) virtual void slot##n();
class BfmeR1254
{
public:
	RVA005A7E20_SLOT(0) RVA005A7E20_SLOT(1) RVA005A7E20_SLOT(2)
	RVA005A7E20_SLOT(3) RVA005A7E20_SLOT(4) RVA005A7E20_SLOT(5)
	RVA005A7E20_SLOT(6) RVA005A7E20_SLOT(7) RVA005A7E20_SLOT(8)
	RVA005A7E20_SLOT(9) RVA005A7E20_SLOT(10) RVA005A7E20_SLOT(11)
	RVA005A7E20_SLOT(12) RVA005A7E20_SLOT(13) RVA005A7E20_SLOT(14)
	RVA005A7E20_SLOT(15) RVA005A7E20_SLOT(16) RVA005A7E20_SLOT(17)
	RVA005A7E20_SLOT(18) RVA005A7E20_SLOT(19) RVA005A7E20_SLOT(20)
	RVA005A7E20_SLOT(21) RVA005A7E20_SLOT(22) RVA005A7E20_SLOT(23)
	RVA005A7E20_SLOT(24) RVA005A7E20_SLOT(25) RVA005A7E20_SLOT(26)
	RVA005A7E20_SLOT(27) RVA005A7E20_SLOT(28) RVA005A7E20_SLOT(29)
	RVA005A7E20_SLOT(30) RVA005A7E20_SLOT(31) RVA005A7E20_SLOT(32)
	RVA005A7E20_SLOT(33) RVA005A7E20_SLOT(34) RVA005A7E20_SLOT(35)
	RVA005A7E20_SLOT(36) RVA005A7E20_SLOT(37) RVA005A7E20_SLOT(38)
	RVA005A7E20_SLOT(39) RVA005A7E20_SLOT(40) RVA005A7E20_SLOT(41)
	RVA005A7E20_SLOT(42) RVA005A7E20_SLOT(43) RVA005A7E20_SLOT(44)
	RVA005A7E20_SLOT(45) RVA005A7E20_SLOT(46) RVA005A7E20_SLOT(47)
	RVA005A7E20_SLOT(48) RVA005A7E20_SLOT(49) RVA005A7E20_SLOT(50)
	RVA005A7E20_SLOT(51) RVA005A7E20_SLOT(52) RVA005A7E20_SLOT(53)
	RVA005A7E20_SLOT(54) RVA005A7E20_SLOT(55) RVA005A7E20_SLOT(56)
	RVA005A7E20_SLOT(57) RVA005A7E20_SLOT(58) RVA005A7E20_SLOT(59)
	RVA005A7E20_SLOT(60) RVA005A7E20_SLOT(61) RVA005A7E20_SLOT(62)
	RVA005A7E20_SLOT(63) RVA005A7E20_SLOT(64)
	virtual Drawable *getSelectedDrawable();
};
#undef RVA005A7E20_SLOT

extern BfmeR1254 *g_bfme1254;
extern ControlBar *TheControlBar;

class Rva005A7E20SpecialPowerButtonFinder
{
public:
	const CommandButton *find(unsigned int specialPowerID) const;
};

const CommandButton *Rva005A7E20SpecialPowerButtonFinder::find(
	unsigned int specialPowerID) const
{
	Drawable *drawable = g_bfme1254->getSelectedDrawable();
	Object *object = drawable->m_object;
	const CommandSet *set = TheControlBar->findCommandSet(object->getCommandSetString());
	if (set)
	{
		for (int i = 0; i < 20; ++i)
		{
			const CommandButton *button = set->getCommandButton(i);
			if (button && button->m_commandType == 0x17)
			{
				const Overridable *power = button->m_specialPower;
				const Overridable *next = power->m_next;
				if (next)
				{
					const Overridable *final = next->m_next;
					if (final)
						next = final->friend_getFinalOverride();
					power = next;
				}
				if (reinterpret_cast<const SpecialPowerTemplate *>(power)->m_id == specialPowerID)
					return button;
			}
		}
	}
	return 0;
}
