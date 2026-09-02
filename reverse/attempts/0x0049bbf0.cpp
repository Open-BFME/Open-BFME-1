// ??0CommandButton@@QAE@XZ
// partial score=0.62 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc
// readable body of ?newCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// readable body of ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <typename T>
class StringBase
{
public:
	StringBase() : m_text(0) {}
	StringBase(const T *text);
	void releaseBuffer();

private:
	T *m_text;
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	AsciiString &operator =(const AsciiString &that);
	void clear()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

template <typename T>
class BfmeCommandButtonVector
{
public:
	BfmeCommandButtonVector() : m_first(0), m_last(0), m_end(0) {}
	~BfmeCommandButtonVector()
	{
		m_first = 0;
		m_last = 0;
		m_end = 0;
	}

	void clear()
	{
		T *source = m_last;
		T *destination = m_first;
		int count = (int)(m_last - source);
		if (count > 0)
		{
			do
			{
				*destination = *source;
				++destination;
				++source;
				--count;
			} while (count != 0);
		}
		m_last = destination;
	}

private:
	T *m_first;
	T *m_last;
	T *m_end;
};

// BFME's CommandButton gained several parsed fields after the Zero Hour
// layout. These small value types preserve the proven retail sizes while
// retaining real C++ construction and destruction for the string/vector
// members.
struct BfmeCommandButtonAudioBlock
{
	BfmeCommandButtonAudioBlock() : m_data1(0), m_data2(0) {}

	AsciiString m_name;
	int m_data1;
	int m_data2;
};

struct BfmeCommandButtonAffectsKindOf
{
	BfmeCommandButtonAffectsKindOf()
	{
		int *destination = m_data;
		int zero = 0;
		destination[0] = zero;
		destination[1] = zero;
		destination[2] = zero;
		destination[3] = zero;
		destination[4] = zero;
		destination[5] = zero;
	}

	void clear()
	{
		int *destination = m_data;
		int zero = 0;
		destination[0] = zero;
		destination[1] = zero;
		destination[2] = zero;
		destination[3] = zero;
		destination[4] = zero;
		destination[5] = zero;
	}

	int m_data[6];
};

struct BfmeCommandButtonModelConditions
{
	BfmeCommandButtonModelConditions()
	{
		for (int i = 0; i < 10; ++i)
			m_data[i] = 0;
	}

	void clear()
	{
		for (int i = 0; i < 10; ++i)
			m_data[i] = 0;
	}

	int m_data[10];
};

// The reference Overridable base has a virtual MemoryPoolObject base, then
// its next-override pointer and override flag at +4/+8. novtable suppresses
// the transient base-vtable write; retail installs CommandButton's vtable
// after those two fields.
class MemoryPoolObject
{
public:
	virtual void anchor();
};

class __declspec(novtable) BfmeOverridable : public MemoryPoolObject
{
public:
	BfmeOverridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~BfmeOverridable() {}

private:
	BfmeOverridable *m_nextOverride;
	bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton : public BfmeOverridable
{
public:
	CommandButton();
	virtual ~CommandButton() {}

	void setName(const AsciiString &name)
	{
		*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(this) + 0x0C) = name;
	}

	void friend_addToList(CommandButton **list)
	{
		*reinterpret_cast<CommandButton **>(reinterpret_cast<char *>(this) + 0x14) = *list;
		*list = this;
	}

private:
	AsciiString m_name;
	int m_command;
	CommandButton *m_next;
	unsigned int m_options;
	void *m_thingTemplate;
	void *m_upgradeTemplate;
	void *m_neededUpgrade;
	BfmeCommandButtonVector<void *> m_buildUpgrades;
	void *m_specialPower;
	int m_radiusCursor;
	AsciiString m_cursorName;
	AsciiString m_invalidCursorName;
	BfmeCommandButtonVector<AsciiString> m_textLabel;
	BfmeCommandButtonVector<AsciiString> m_descriptionLabel;
	AsciiString m_purchasedLabel;
	AsciiString m_conflictingLabel;
	AsciiString m_lacksPrerequisiteLabel;
	StringBase<char> m_unparsedLabel;
	int m_weaponSlot;
	int m_weaponSlotToggle1;
	int m_weaponSlotToggle2;
	int m_weaponSlotToggle3;
	unsigned int m_flagsUsedForToggle;
	int m_maxShotsToFire;
	BfmeCommandButtonVector<int> m_science;
	int m_buttonBorder;
	BfmeCommandButtonVector<AsciiString> m_buttonImage;
	int m_flashCount;
	AsciiString m_audioPrefix;
	BfmeCommandButtonAudioBlock m_audio00;
	BfmeCommandButtonAudioBlock m_audio01;
	BfmeCommandButtonAudioBlock m_audio02;
	BfmeCommandButtonAudioBlock m_audio03;
	BfmeCommandButtonAudioBlock m_audio04;
	BfmeCommandButtonAudioBlock m_audio05;
	BfmeCommandButtonAudioBlock m_audio06;
	BfmeCommandButtonAudioBlock m_audio07;
	BfmeCommandButtonAudioBlock m_audio08;
	BfmeCommandButtonAudioBlock m_audio09;
	BfmeCommandButtonAudioBlock m_audio10;
	BfmeCommandButtonAudioBlock m_audio11;
	AsciiString m_audioTail0;
	AsciiString m_audioTail1;
	int m_audioTail2;
	int m_audioTail3;
	int m_audioTail4;
	unsigned char m_doubleClick;
	unsigned char m_radial;
	unsigned char m_inPalantir;
	unsigned char m_showProductionCount;
	unsigned char m_showProductionCount2;
	unsigned char m_isClickable;
	unsigned char m_showButton;
	unsigned char m_requiresValidContainer;
	int m_requireLevel;
	unsigned char m_autoAbility;
	BfmeCommandButtonAffectsKindOf m_affectsKindOf;
	unsigned char m_affectsAllies;
	unsigned char m_triggerWhenReady;
	int m_presetRange;
	int m_autoDelay;
	unsigned char m_needDamagedTarget;
	AsciiString m_commandTrigger;
	BfmeCommandButtonModelConditions m_enableOnModelCondition;
	BfmeCommandButtonModelConditions m_disableOnModelCondition;
};

CommandButton::CommandButton() :
	m_command(0),
	m_next(0),
	m_options(0),
	m_thingTemplate(0),
	m_upgradeTemplate(0),
	m_neededUpgrade(0),
	m_specialPower(0),
	m_radiusCursor(0),
	m_weaponSlot(0),
	m_weaponSlotToggle1(3),
	m_weaponSlotToggle2(3),
	m_weaponSlotToggle3(3),
	m_flagsUsedForToggle(0),
	m_maxShotsToFire(0x7fffffff),
	m_buttonBorder(0),
	m_flashCount(-1),
	m_audioTail2(0),
	m_audioTail3(0),
	m_audioTail4(0),
	m_doubleClick(0),
	m_radial(0),
	m_inPalantir(0),
	m_showProductionCount(0),
	m_showProductionCount2(0),
	m_isClickable(1),
	m_showButton(1),
	m_requiresValidContainer(0),
	m_requireLevel(0),
	m_autoAbility(0),
	m_affectsAllies(0),
	m_triggerWhenReady(0),
	m_presetRange(0),
	m_autoDelay(0),
	m_needDamagedTarget(0),
	m_commandTrigger("Lang\\%s\\Lotr.csf")
{
	volatile int spare = 0;
	m_science.clear();
	m_enableOnModelCondition.clear();
	m_disableOnModelCondition.clear();
	m_affectsKindOf.clear();
	m_flagsUsedForToggle = 0;
	m_unparsedLabel.releaseBuffer();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	CommandSet(const AsciiString & name);
	void friend_addToList(CommandSet **list);

private:
	unsigned char m_retailLayout[100];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CommandButton *newCommandButton(const AsciiString & name);
	CommandSet *newCommandSet(const AsciiString & name);

private:
	unsigned char m_prefix[0x28];
	CommandButton *m_commandButtons;
	CommandSet *m_commandSets;
};

CommandButton *ControlBar::newCommandButton(const AsciiString &name)
{
	CommandButton *button = new CommandButton;
	button->setName(name);
	button->friend_addToList(&m_commandButtons);
	return button;
}

CommandSet *ControlBar::newCommandSet(const AsciiString & name)
{
	CommandSet *set = new CommandSet(name);
	set->friend_addToList(&m_commandSets);
	return set;
}
