// ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ reconstruction of the 624-byte retail body at 0x004A04C0, in its
// own TU because the BFME ControlBar layout is narrower than the Zero Hour
// header ControlBar.cpp compiles against: the five shortcut buttons sit at
// +0xCC, their five parent windows at +0xE0, the live count at +0xF4 and the
// shortcut bar's own parent at +0xFC. ControlBar_setControlCommand_GameWindow.cpp
// and ControlBar_updateSpecialPowerShortcut.cpp are the same pattern.
//
// IDENTITY. Two byte-matched callers name this symbol:
// ?showSpecialPowerShortcut@ControlBar@@QAEXXZ (0x004A07D0, landed in
// ControlBar.cpp) and ?update@ControlBar@@UAEXXZ (0x004A2F80,
// ControlBarUpdateVirtual.cpp, which declares the member and calls it at +0xBD).
// The BFME body is much narrower than the Zero Hour source the member carried
// in ControlBar.cpp: BFME walks the player's own command-button list
// (m_commandButtons at +0x28) for the matching GUI_COMMAND_PURCHASE_SCIENCE
// button rather than looking up the three rank-N purchase-science command sets,
// and it has no UpgradeTemplate path and no SELECT_ALL_UNITS_OF_TYPE check.
//
// The NEED_SPECIAL_POWER_SCIENCE test is the 0x80 bit of CommandButton::m_options
// (+0x18, the CommandButton FieldParse table at 0x00CFA3B8), which is the same
// flag Zero Hour spells BitTest( getOptions(), NEED_SPECIAL_POWER_SCIENCE ).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum
{
	GUI_COMMAND_PURCHASE_SCIENCE = 0x18,
	NEED_SPECIAL_POWER_SCIENCE = 0x00000080
};

struct AsciiStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

// The by-value AsciiString argument of GadgetButtonSetAltSound is built by the
// StringBase<char> const char * constructor, retail 0x00888BC0, reached through
// the INLINE forwarding constructor on AsciiString, so the call this body emits
// is ??0?$StringBase@D@@QAE@PBD@Z. The length is a 16-bit field, which is the
// `cmp word ptr [ecx+4],0` retail inlines for isEmpty() at +0xA2.
//
// The forwarding constructors also keep the class non-trivially copyable, which
// is load-bearing: MSVC 7.1 then constructs the by-value argument in place
// (`push ecx` / `mov [esp+0x20],esp` / `mov ecx,esp` + call, retail
// +0x1F9..+0x208). A trivially copyable spelling builds a local at
// [esp+0x20] and copies it, which is 8 bytes short and one extra store.
template <typename T> class StringBase
{
	friend class AsciiString;

protected:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	AsciiStringData *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	Bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

class GameWindow
{
public:
	Bool winIsHidden(void);
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
};

class PlayerTemplate
{
	unsigned char m_unreconstructed_00[0xAC];
	AsciiString m_specialPowerShortcutCommandSet;	///< +0xAC

public:
	const AsciiString &getSpecialPowerShortcutCommandSet() const
	{
		return m_specialPowerShortcutCommandSet;
	}
};

class Player
{
	unsigned char m_unreconstructed_00[4];
	PlayerTemplate *m_playerTemplate;				///< +0x04

public:
	PlayerTemplate *getPlayerTemplate() const
	{
		return m_playerTemplate;
	}
	Bool isLocalPlayer(void) const;
	Bool hasScience(ScienceType science) const;
};

class SpecialPowerTemplate
{
public:
	ScienceType getRequiredScience(void) const;
};

// The tail of CommandSet::m_science at +0x84: two pointers. The bounded size
// MSVC emits is the difference divided by four, which is what retail's
// `sub eax,[esi+0x84]` / `sar eax,2` pair reads.
struct ScienceVec
{
	ScienceType *m_begin;
	ScienceType *m_end;

	UnsignedInt size(void) const
	{
		return m_end - m_begin;
	}
	Bool empty(void) const
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
	Int m_command;								///< +0x10
	CommandButton *m_next;						///< +0x14
	UnsignedInt m_options;						///< +0x18
	unsigned char m_unreconstructed_1C[0x18];
	const SpecialPowerTemplate *m_specialPower;	///< +0x34
	unsigned char m_unreconstructed_38[0x4C];
	ScienceVec m_science;						///< +0x84

public:
	Int getCommandType(void) const
	{
		return m_command;
	}
	CommandButton *getNext(void) const
	{
		return m_next;
	}
	const SpecialPowerTemplate *getSpecialPowerTemplate(void) const
	{
		return m_specialPower;
	}
	const ScienceVec &getScienceVec(void) const
	{
		return m_science;
	}
	signed char getOptions(void) const
	{
		return static_cast<signed char>(m_options);
	}
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

// The image copy at retail +0x1B0 is the landed body
// ?bfmeCopyFrom@Gen_0049C4B0@@QAEXPAV1@_N@Z at 0x0049C4B0 (140 bytes, the
// vector empty-and-refill with the dirty flag). ControlBar.cpp already reaches
// it the same way, through the Gen_0049C4B0 view of the button.
class Gen_0049C4B0
{
public:
	void bfmeCopyFrom(Gen_0049C4B0 *source, bool notify);
};

class ControlBar
{
	unsigned char m_unreconstructed_00[0x28];
	CommandButton *m_commandButtons;				///< +0x28
	unsigned char m_unreconstructed_2C[8];
	GameWindow *m_contextParent;				///< +0x34
	unsigned char m_unreconstructed_38[0x94];
	GameWindow *m_specialPowerShortcutButtons[5];		///< +0xCC
	GameWindow *m_specialPowerShortcutButtonParents[5];///< +0xE0
	Int m_currentlyUsedSpecialPowersButtons;	///< +0xF4
	unsigned char m_unreconstructed_F8[4];
	GameWindow *m_specialPowerShortcutParent;	///< +0xFC

public:
	const CommandSet *findCommandSet(const AsciiString &name);
	void showSpecialPowerShortcut(void);
	void animateSpecialPowerShortcut(Bool on);

protected:
	void updateSpecialPowerShortcut(void);
	void populateSpecialPowerShortcut(Player *player);

private:
	void setControlCommand(GameWindow *window, const CommandButton *command);
};

extern ControlBar *TheControlBar;

void GadgetButtonSetAltSound(GameWindow *window, AsciiString sound);

// ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z
void ControlBar::populateSpecialPowerShortcut(Player *player)
{
	const CommandSet *commandSet;
	const AsciiString *commandSetName;
	Int i;
	Int currentButton = 0;
	const CommandButton *commandButton;
	// Hide every shortcut button the bar currently shows, then bail out on a
	// player that cannot have special-power shortcuts at all.
	if (!player || !player->getPlayerTemplate()
			|| !player->isLocalPlayer() || m_currentlyUsedSpecialPowersButtons == 0
			|| !m_specialPowerShortcutButtons || !m_specialPowerShortcutButtonParents)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
	{
		if (m_specialPowerShortcutButtons[i])
			m_specialPowerShortcutButtons[i]->winHide(true);
		if (m_specialPowerShortcutButtonParents[i])
			m_specialPowerShortcutButtonParents[i]->winHide(true);
	}

	// The command set comes from the player's own template.
	commandSetName = &player->getPlayerTemplate()->getSpecialPowerShortcutCommandSet();
	if (commandSetName->isEmpty())
		return;
	commandSet = TheControlBar->findCommandSet(*commandSetName);
	if (!commandSet)
		return;

	for (i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i)
	{
		commandButton = commandSet->getCommandButton(i);
		if (!commandButton)
			continue;

		// Commands that require sciences we don't have are hidden, so they never
		// show up: we can never pick "another" general technology in a game.
		if (commandButton->getOptions() & NEED_SPECIAL_POWER_SCIENCE)
		{
			const SpecialPowerTemplate *power = commandButton->getSpecialPowerTemplate();
			if (power && power->getRequiredScience() != SCIENCE_INVALID)
			{
				if (!player->hasScience(power->getRequiredScience()))
					continue;

				// We do have the special power. Now decide whether the button's
				// images need the enhancement an upgraded version carries, which
				// the command button states as its science vector. Take the last
				// science we have from the front of that vector.
				Int bestIndex = -1;
				for (Int scienceIndex = 0;
					scienceIndex < commandButton->getScienceVec().size(); ++scienceIndex)
				{
					ScienceType science = commandButton->getScienceVec()[scienceIndex];
					if (player->hasScience(science))
						bestIndex = scienceIndex;
					else
						break;
				}

				if (bestIndex != -1)
				{
					// Copy the images off the matching purchase-science button,
					// which BFME keeps on the player's own command-button list.
					ScienceType science = commandButton->getScienceVec()[bestIndex];
					for (CommandButton *purchase = m_commandButtons;
						purchase; purchase = purchase->getNext())
					{
						if (purchase->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE
								&& !purchase->getScienceVec().empty()
								&& purchase->getScienceVec()[0] == science)
							((Gen_0049C4B0 *)commandButton)->bfmeCopyFrom(
								(Gen_0049C4B0 *)purchase, true);
					}
				}
			}
		}

		// Make sure the window is shown and enabled...
		m_specialPowerShortcutButtons[currentButton]->winHide(false);
		m_specialPowerShortcutButtonParents[currentButton]->winHide(false);
		m_specialPowerShortcutButtons[currentButton]->winEnable(true);
		m_specialPowerShortcutButtonParents[currentButton]->winEnable(true);

		// ...and populate the visible button with data from the command button.
		setControlCommand(m_specialPowerShortcutButtons[currentButton], commandButton);
		GadgetButtonSetAltSound(m_specialPowerShortcutButtons[currentButton],
			AsciiString("GUIGenShortcutClick"));
		++currentButton;
	}

	// The bar only becomes visible once the context bar is.
	if (m_contextParent && !m_contextParent->winIsHidden()
			&& m_specialPowerShortcutParent->winIsHidden())
	{
		showSpecialPowerShortcut();
		animateSpecialPowerShortcut(true);
	}
	updateSpecialPowerShortcut();
}
