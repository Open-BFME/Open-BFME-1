// cl: /DNDEBUG /MD /EHsc
// stlport
// ??0CommandButton@@QAE@XZ
// BFME's CommandButton is the extended 0x1d8-byte record allocated by
// ControlBar::newCommandButton.  The local mirrors below keep the BFME-only
// vector and string layouts out of the shared Zero Hour headers.

#include <string.h>
#include <vector>

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

struct BfmeCommandButtonCommandTrigger
{
	BfmeCommandButtonCommandTrigger() :
		m_string((const char *)0x0107301c)
	{
	}

	BFMERetailAsciiString m_string;
};

class Gen0049B890
{
public:
	virtual ~Gen0049B890();

private:
	unsigned char m_body[0x6c];
};

class Image;

struct BfmeCommandButtonRawString
{
	BfmeCommandButtonRawString() : m_data(0) {}

	void *m_data;
};

enum BfmeScienceType
{
	BFME_SCIENCE_NONE = 0
};

template <typename T> class BfmeCommandButtonVector
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
		volatile T *source = m_last;
		T *destination = m_first;
		int count = (int)(m_last - source);
		if (count > 0)
		{
			do
			{
				T value = *source;
				*destination = value;
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

static void bfmeCommandButtonZeroSix(int *destination)
{
	int zero = 0;
	destination[0] = zero;
	destination[1] = zero;
	destination[2] = zero;
	destination[3] = zero;
	destination[4] = zero;
	destination[5] = zero;
}

static void bfmeCommandButtonZeroTen(int *destination)
{
	int zero = 0;
	destination[0] = zero;
	destination[1] = zero;
	destination[2] = zero;
	destination[3] = zero;
	destination[4] = zero;
	destination[5] = zero;
	destination[6] = zero;
	destination[7] = zero;
	destination[8] = zero;
	destination[9] = zero;
}

template <int WORDS> struct BfmeCommandButtonBitsetBase
{
	BfmeCommandButtonBitsetBase()
	{
		reset();
	}

	void reset()
	{
		memset(m_words, 0, sizeof(m_words));
	}

	unsigned int m_words[WORDS];
};

template <int WORDS> struct BfmeCommandButtonBitset
{
	BfmeCommandButtonBitset() {}

	void reset()
	{
		m_base.reset();
	}

	BfmeCommandButtonBitsetBase<WORDS> m_base;
};

template <int WORDS> struct BfmeCommandButtonBitFlags
{
	BfmeCommandButtonBitFlags() {}

	void clear()
	{
		m_bits.reset();
	}

	BfmeCommandButtonBitset<WORDS> m_bits;
};

typedef BfmeCommandButtonBitFlags<6> BfmeCommandButtonAffectsKindOf;
typedef BfmeCommandButtonBitFlags<10> BfmeCommandButtonModelConditions;

class MemoryPoolObject
{
protected:
 	virtual ~MemoryPoolObject() {}

public:
};

class BfmeOverridable : public MemoryPoolObject
{
public:
	BfmeOverridable() : m_nextOverride(0), m_isOverride(false) {}

private:
	BfmeOverridable *m_nextOverride;
	bool m_isOverride;
};

class CommandButton : public BfmeOverridable
{
public:
	CommandButton();

private:
	BFMERetailAsciiString m_name;
	int m_command;
	CommandButton *m_next;
	unsigned int m_options;
	void *m_thingTemplate;
	void *m_upgradeTemplate;
	void *m_neededUpgrade;
	BfmeCommandButtonVector<BFMERetailAsciiString> m_buildUpgrades;
	void *m_specialPower;
	int m_radiusCursor;
	BFMERetailAsciiString m_cursorName;
	BFMERetailAsciiString m_invalidCursorName;
	BfmeCommandButtonVector<BFMERetailAsciiString> m_textLabel;
	BfmeCommandButtonVector<BFMERetailAsciiString> m_descriptionLabel;
	BFMERetailAsciiString m_purchasedLabel;
	BFMERetailAsciiString m_conflictingLabel;
	BFMERetailAsciiString m_lacksPrerequisiteLabel;
	BfmeCommandButtonRawString m_unparsedLabel;
	int m_weaponSlot;
	int m_weaponSlotToggle1;
	int m_weaponSlotToggle2;
	int m_weaponSlotToggle3;
	unsigned int m_flagsUsedForToggle;
	int m_maxShotsToFire;
	std::vector<BfmeScienceType> m_science;
	int m_buttonBorder;
	BfmeCommandButtonVector<BFMERetailAsciiString> m_buttonImageNames;
	int m_flashCount;
	BFMERetailAsciiString m_audioPrefix;
	BfmeCommandButtonVector<Gen0049B890> m_audio00;
	BfmeCommandButtonVector<Gen0049B890> m_audio01;
	BfmeCommandButtonVector<Gen0049B890> m_audio02;
	BfmeCommandButtonVector<Gen0049B890> m_audio03;
	BfmeCommandButtonVector<Gen0049B890> m_audio04;
	BfmeCommandButtonVector<Gen0049B890> m_audio05;
	BfmeCommandButtonVector<Gen0049B890> m_audio06;
	BfmeCommandButtonVector<Gen0049B890> m_audio07;
	BfmeCommandButtonVector<Gen0049B890> m_audio08;
	BfmeCommandButtonVector<Gen0049B890> m_audio09;
	BfmeCommandButtonVector<Gen0049B890> m_audio10;
	BfmeCommandButtonVector<Gen0049B890> m_audio11;
	BfmeCommandButtonVector<const Image *> m_buttonImages;
	int m_audioTail2;
	int m_audioTail3;
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
	BfmeCommandButtonCommandTrigger m_commandTrigger;
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
	m_audioTail2(0),
	m_audioTail3(0)
{
	m_affectsKindOf.clear();
	m_science.clear();
	m_flagsUsedForToggle = 0;
	m_enableOnModelCondition.clear();
	m_disableOnModelCondition.clear();
	((BFMERetailAsciiString *)&m_unparsedLabel)->releaseBuffer();
}
