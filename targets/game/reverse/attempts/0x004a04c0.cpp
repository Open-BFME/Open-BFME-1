// ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z
// partial score=0.86 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Clean BFME reconstruction of the 624-byte retail body at 0x004A04C0.
//
// The retail layout is narrower than the ZH ControlBar header: the five
// shortcut buttons occupy +0xCC, the five parent windows +0xE0, and the live
// count is at +0xF4.  BFME also keeps the command-button list at +0x28 and
// copies the matching purchase-science button's images directly.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum
{
	GUI_COMMAND_PURCHASE_SCIENCE = 0x18
};

struct AsciiStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

class AsciiString
{
	AsciiStringData *m_data;

public:
	AsciiString(const char *text);
	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

class GameWindow
{
public:
	void winHide(Bool hide);
	Int winEnable(Bool enable);
	Bool winIsHidden();
};

class PlayerTemplate
{
	unsigned char m_unreconstructed_00[0xAC];
	AsciiString m_specialPowerShortcutCommandSet;

public:
	const AsciiString &getSpecialPowerShortcutCommandSet() const
	{
		return m_specialPowerShortcutCommandSet;
	}
};

class Player
{
	unsigned char m_unreconstructed_00[4];
	PlayerTemplate *m_playerTemplate;

public:
	PlayerTemplate *getPlayerTemplate() const
	{
		return m_playerTemplate;
	}
	Bool isLocalPlayer() const;
	Bool hasScience(ScienceType science) const;
};

class SpecialPowerTemplate
{
public:
	ScienceType getRequiredScience() const;
};

struct ScienceVec
{
	ScienceType *m_begin;
	ScienceType *m_end;

	UnsignedInt size() const
	{
		return m_end - m_begin;
	}
	Bool empty() const
	{
		return m_begin == m_end;
	}
	ScienceType operator[](Int index) const
	{
		return m_begin[index];
	}
};

class CommandButton
{
	unsigned char m_unreconstructed_00[0x10];
	Int m_command;
	CommandButton *m_next;
	UnsignedInt m_options;
	unsigned char m_unreconstructed_1C[0x18];
	const SpecialPowerTemplate *m_specialPower;
	unsigned char m_unreconstructed_38[0x4C];
	ScienceVec m_science;

public:
	Int getCommandType() const
	{
		return m_command;
	}
	CommandButton *getNext() const
	{
		return m_next;
	}
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPower;
	}
	const ScienceVec &getScienceVec() const
	{
		return m_science;
	}
	signed char getOptions() const
	{
		return static_cast<signed char>(m_options);
	}
	void copyImagesFrom(const CommandButton *button, Bool markUIDirtyIfChanged) const;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class ControlBar
{
	unsigned char m_unreconstructed_00[0x28];
	CommandButton *m_commandButtons;
	unsigned char m_unreconstructed_2C[8];
	GameWindow *m_contextParent;
	unsigned char m_unreconstructed_38[0x94];
	GameWindow *m_specialPowerShortcutButtons[5];
	GameWindow *m_specialPowerShortcutButtonParents[5];
	Int m_currentlyUsedSpecialPowersButtons;
	unsigned char m_unreconstructed_F8[4];
	GameWindow *m_specialPowerShortcutParent;

public:
	const CommandSet *findCommandSet(const AsciiString &name);
	void showSpecialPowerShortcut();
	void animateSpecialPowerShortcut(Bool on);

protected:
	void updateSpecialPowerShortcut();
	void populateSpecialPowerShortcut(Player *player);

private:
	void setControlCommand(GameWindow *window, const CommandButton *command);
};

extern ControlBar *TheControlBar;

void GadgetButtonSetAltSound(GameWindow *window, AsciiString sound);

// ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z
void ControlBar::populateSpecialPowerShortcut(Player *player)
{
	Player *localPlayer = player;
	ControlBar *self = this;
	const CommandSet *commandSet;
	const AsciiString *commandSetName;
	Int i;
	Int currentButton = 0;
	const CommandButton *commandButton;
	if (!localPlayer || !localPlayer->getPlayerTemplate()
			|| !localPlayer->isLocalPlayer() || self->m_currentlyUsedSpecialPowersButtons == 0
			|| !self->m_specialPowerShortcutButtons || !self->m_specialPowerShortcutButtonParents)
		return;

	for (i = 0; i < self->m_currentlyUsedSpecialPowersButtons; ++i)
	{
		if (self->m_specialPowerShortcutButtons[i])
			self->m_specialPowerShortcutButtons[i]->winHide(true);
		if (self->m_specialPowerShortcutButtonParents[i])
			self->m_specialPowerShortcutButtonParents[i]->winHide(true);
	}

	commandSetName = &localPlayer->getPlayerTemplate()->getSpecialPowerShortcutCommandSet();
	if (commandSetName->isEmpty())
		return;
	commandSet = TheControlBar->findCommandSet(*commandSetName);
	if (!commandSet)
		return;

	for (i = 0; i < self->m_currentlyUsedSpecialPowersButtons; ++i)
	{
		commandButton = commandSet->getCommandButton(i);
		if (!commandButton)
			continue;

		if (commandButton->getOptions() < 0)
		{
			const SpecialPowerTemplate *power = commandButton->getSpecialPowerTemplate();
			if (power && power->getRequiredScience() != SCIENCE_INVALID)
			{
				if (!localPlayer->hasScience(power->getRequiredScience()))
					continue;

				Int bestIndex = -1;
				for (Int scienceIndex = 0;
					scienceIndex < commandButton->getScienceVec().size(); ++scienceIndex)
				{
					ScienceType science = commandButton->getScienceVec()[scienceIndex];
					if (localPlayer->hasScience(science))
						bestIndex = scienceIndex;
					else
						break;
				}

				if (bestIndex != -1)
				{
					ScienceType science = commandButton->getScienceVec()[bestIndex];
					for (CommandButton *purchase = self->m_commandButtons;
						purchase; purchase = purchase->getNext())
					{
						if (purchase->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE
								&& !purchase->getScienceVec().empty()
								&& purchase->getScienceVec()[0] == science)
							commandButton->copyImagesFrom(purchase, true);
					}
				}
			}
		}

		self->m_specialPowerShortcutButtons[currentButton]->winHide(false);
		self->m_specialPowerShortcutButtonParents[currentButton]->winHide(false);
		self->m_specialPowerShortcutButtons[currentButton]->winEnable(true);
		self->m_specialPowerShortcutButtonParents[currentButton]->winEnable(true);
		self->setControlCommand(self->m_specialPowerShortcutButtons[currentButton], commandButton);
		GadgetButtonSetAltSound(self->m_specialPowerShortcutButtons[currentButton],
			AsciiString("GUIGenShortcutClick"));
		++currentButton;
	}

	if (self->m_contextParent && !self->m_contextParent->winIsHidden()
			&& self->m_specialPowerShortcutParent->winIsHidden())
	{
		self->showSpecialPowerShortcut();
		self->animateSpecialPowerShortcut(true);
	}
	self->updateSpecialPowerShortcut();
}
