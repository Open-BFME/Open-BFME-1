// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas

// SuperweaponInfo's constructor, 0x0043D8C0, the body the
// SuperweaponInfoCtorThunk.cpp lift carried as a naked __emit copy.
//
// The declaration is BFME1's, not Zero Hour's, and three places say so:
//
//   ret 0x28, ten stack words.  ZH's ctor takes an eleventh
//   (evaReadyPlayed) between `ready` and the font, so ZH's body cleans 0x2c
//   and reads its colour/template pair at [esp+0x3c]/[esp+0x40].  Retail
//   reads them at [esp+0x38], and the ninth word of the frame is the last
//   argument.  ZH's own source has no other reading of the body.
//
//   The tail byte at +0x23 is the last store in the constructor, so the
//   object has three flag bytes (hiddenByScript, hiddenByScience, ready) and
//   one more (m_forceUpdateText) with no fifth between ready and it: the
//   layout below ends at 0x23 with nothing after.
//
//   The two virtual calls in each half reach +0x14 and +0x04 on the
//   DisplayString, and +0x24 on the DisplayStringManager, which is BFME's
//   one-base-virtual DisplayString (the Zero Hour header injects
//   getObjectMemoryPool ahead of setText and moves both by a word) and the
//   six-extra-slots DisplayStringManager.  Both offsets are already proven
//   by matched bodies: 0x0040C230 (CreditsLine::~CreditsLine) calls
//   freeDisplayString through +0x28, and 0x0043DA90 (SuperweaponInfo::
//   setText, game/GameEngine/Source/GameClient/SuperweaponInfoSetText.cpp)
//   calls setText through +0x04.
//
// UnicodeString is the languagefilter shim's, so the empty-string copy
// encodes 0x00888400 = ??0?$StringBase@G@@AAE@ABV0@@Z, the same instruction
// the matched 0x004B4E00 (GadgetComboBoxGetText) emits for
// `return UnicodeString::TheEmptyString`, and so the by-value temporary
// registers its EH saved-esp before loading its own address the way retail
// does.  setText takes its string BY VALUE, which is what makes the callee
// own the temporary: retail never calls a destructor for it, and only the
// one unwind action in the map (destroying m_powerName at this+0x14,
// python3 tools/eh_info.py 0x0043D8C0) belongs to this constructor.

#include "Common/UnicodeString.h"

// BFME's Color is a class in GameClient/Color.h, but every offset these
// bodies touch is a plain int, and the constructor passes the colour straight
// through, so the int keeps the `I` the ten-word decoration carries.
typedef int Color;

class AsciiString
{
public:
	// The one member this body builds is a zero, and retail stores it in
	// place (`mov [esi+0x14],eax` with eax already 0) rather than calling a
	// default constructor, so the default constructor is inline here.
	AsciiString() : m_data(0) {}
	~AsciiString();

	const char *str() const { return (const char *)m_data; }

private:
	const char *m_data;
};

class GameFont;

// BFME1 DisplayString vtable: the destructor is the only base virtual, then
// the declared order.  setText at +0x04 and reset at +0x14 are the two slots
// this body calls; setFont at +0x18 is what SuperweaponInfo.cpp's matched
// setFont reaches.
class DisplayString
{
public:
	virtual ~DisplayString() {}
	virtual void setText(UnicodeString text);
	virtual void getText();
	virtual void getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
	virtual void getFont();
	virtual void setWordWrap(Int wordWrap) = 0;
	virtual void setWordWrapCentered(Bool isCentered) = 0;
	virtual void draw(Int x, Int y, Color color, Color dropColor) = 0;
	virtual void draw(Int x, Int y, Color color, Color dropColor, Int xDrop, Int yDrop) = 0;
	virtual void getSize(Int *width, Int *height) = 0;
	virtual Int getWidth(Int charPos = -1) = 0;
	virtual void setUseHotkey(Bool useHotkey, Color hotKeyColor) = 0;
	virtual void setClipRegion(void *region);
	virtual void removeLastChar();
	virtual void appendChar(WideChar c);
	DisplayString *next();
};

// BFME1 DisplayStringManager vtable: freeDisplayString is proven at +0x28 by
// the matched 0x0040C230, so newDisplayString is the slot before it.
class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void slot04() {}
	virtual void slot08() {}
	virtual void slot0c() {}
	virtual void slot10() {}
	virtual void slot14() {}
	virtual void slot18() {}
	virtual void slot1c() {}
	virtual void slot20() {}
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

enum ObjectID { OBJECTID_NONE = 0 };

class SpecialPowerTemplate;

// One declaration for the class, holding the layout its four already-matched
// methods in SuperweaponInfo.cpp reach (the two display strings at +0x04 and
// +0x08, the colour at +0x0c, the template at +0x10, the power name at
// +0x14) plus the saved fields only the constructor writes.
class SuperweaponInfo
{
protected:
	// Declared, never defined: the body is already matched at 0x0043D9F0 in
	// SuperweaponInfo.cpp, and the vtable pointer this constructor installs
	// comes from that definition.
	virtual ~SuperweaponInfo();

public:
	SuperweaponInfo(
		ObjectID id,
		UnsignedInt timestamp,
		Bool hiddenByScript,
		Bool hiddenByScience,
		Bool ready,
		const AsciiString &superweaponNormalFont,
		Int superweaponNormalPointSize,
		Bool superweaponNormalBold,
		Color c,
		const SpecialPowerTemplate *spt);

	void setFont(const AsciiString &superweaponNormalFont, Int superweaponNormalPointSize, Bool superweaponNormalBold);

private:
	DisplayString *m_nameDisplayString;
	DisplayString *m_timeDisplayString;
	Color m_color;
	const SpecialPowerTemplate *m_powerTemplate;
	AsciiString m_powerName;
	ObjectID m_id;
	UnsignedInt m_timestamp;
	Bool m_hiddenByScript;
	Bool m_hiddenByScience;
	Bool m_ready;
	Bool m_forceUpdateText;
};

// ??0SuperweaponInfo@@QAE@W4ObjectID@@I_N11ABVAsciiString@@H1HPBVSpecialPowerTemplate@@@Z
//
// Everything the constructor saves goes in the member list, in the order the
// class declares it, because that is the order retail stores it in, and
// because a plain assignment in the body is a store MSVC can see the
// newDisplayString() result overwrite and drops: retail keeps the zero at
// +0x04 and +0x08 and writes the manager's answer over both. m_powerName is
// left out so its default constructor stays inline.
SuperweaponInfo::SuperweaponInfo(
	ObjectID id,
	UnsignedInt timestamp,
	Bool hiddenByScript,
	Bool hiddenByScience,
	Bool ready,
	const AsciiString &superweaponNormalFont,
	Int superweaponNormalPointSize,
	Bool superweaponNormalBold,
	Color c,
	const SpecialPowerTemplate *spt) :
	m_nameDisplayString(0),
	m_timeDisplayString(0),
	m_color(c),
	m_powerTemplate(spt),
	m_id(id),
	m_timestamp(timestamp),
	m_hiddenByScript(hiddenByScript),
	m_hiddenByScience(hiddenByScience),
	m_ready(ready),
	m_forceUpdateText(false)
{
	m_nameDisplayString = TheDisplayStringManager->newDisplayString();
	m_nameDisplayString->reset();
	m_nameDisplayString->setText(UnicodeString::TheEmptyString);

	m_timeDisplayString = TheDisplayStringManager->newDisplayString();
	m_timeDisplayString->reset();
	m_timeDisplayString->setText(UnicodeString::TheEmptyString);

	setFont(superweaponNormalFont, superweaponNormalPointSize, superweaponNormalBold);
}
