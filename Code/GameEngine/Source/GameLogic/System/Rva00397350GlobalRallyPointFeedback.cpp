// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Rally-point feedback the dispatcher calls with (Object *, const Coord3D &);
// no symbol proves a historical owner, so the name keeps the retail address.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "ascii_string.h"

// unicode_string.h declares the default ctor out of line; retail inlines it.
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}
	void __cdecl format(UnicodeString format, ...);

private:
	void *m_data;
};

class Drawable;
class Player;

class Object
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
	virtual Drawable *getDrawable();

	Bool isLocallyControlled() const;
	Player *getControllingPlayer() const;
};

typedef void (__cdecl *ObjectIterateFunc)(Object *, void *);

class Player
{
public:
	void iterateObjects(ObjectIterateFunc routine, void *state) const;

	unsigned char m_unmodelled[0x24];
	Int m_playerIndex;

	Int getPlayerIndex() const { return m_playerIndex; }
};

class Drawable
{
public:
	unsigned char m_unmodelled[0x3AC];
	Bool m_selected;

	Bool isSelected() const { return m_selected; }
};

class GameTextInterface
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
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

class InGameUI
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
	virtual void slot3C();
	virtual void message(UnicodeString format, ...);
};

enum ObjectID
{
	INVALID_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID = INVALID_ID);
	virtual void slot00();
	~AudioEventRTS();
	void setPosition(const Coord3D *position);
	void setPlayerIndex(Int playerIndex);

private:
	unsigned char m_unmodelled[0x6C];
};

class AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(04) AUDIO_SLOT(08) AUDIO_SLOT(0C)
	AUDIO_SLOT(10) AUDIO_SLOT(14) AUDIO_SLOT(18) AUDIO_SLOT(1C)
	AUDIO_SLOT(20) AUDIO_SLOT(24) AUDIO_SLOT(28) AUDIO_SLOT(2C)
	AUDIO_SLOT(30) AUDIO_SLOT(34) AUDIO_SLOT(38) AUDIO_SLOT(3C)
	AUDIO_SLOT(40)
	virtual void addAudioEvent(AudioEventRTS *event);
#undef AUDIO_SLOT
};

class ControlBar
{
public:
	unsigned char m_unmodelled[0x24];
	Bool m_uiDirty;

	void markUIDirty() { m_uiDirty = true; }
};

struct BfmeReferenceOwner;
struct BfmeReferenceResolveState;

extern Int bfmeResolveReferenceIfEnabled(
	BfmeReferenceOwner *owner, BfmeReferenceResolveState *state);

// Position copied from the caller plus the resolved count at +0x0c, which the
// landed callback bfmeResolveReferenceIfEnabled increments.
struct Rva00397350ResolveState
{
	Coord3D m_position;
	Int m_resolvedCount;
};

#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheInGameUI (*(InGameUI **)0x012F148C)
#define TheAudioClientUpdate (*(AudioClient **)0x012ED668)
#define TheControlBar (*(ControlBar **)0x012F33F8)

void Rva00397350GlobalRallyPointFeedback(
	Object *object, const Coord3D &position)
{
	Bool isLocal = object->isLocallyControlled();
	Rva00397350ResolveState state;
	state.m_position.x = position.x;
	state.m_position.y = position.y;
	state.m_position.z = position.z;
	state.m_resolvedCount = 0;

	object->getControllingPlayer()->iterateObjects(
		(ObjectIterateFunc)bfmeResolveReferenceIfEnabled,
		(void *)&state);

	if (isLocal && state.m_resolvedCount > 0)
	{
		UnicodeString message;
		message.format(TheGameText->fetch("GUI:GlobalRallyPointSet"));
		TheInGameUI->message(message);

		static AudioEventRTS rallyPointSet("RallyPointSet");
		rallyPointSet.setPosition(&position);
		rallyPointSet.setPlayerIndex(object->getControllingPlayer()->getPlayerIndex());
		TheAudioClientUpdate->addAudioEvent(&rallyPointSet);

		Drawable *drawable = object->getDrawable();
		if (drawable && drawable->isSelected())
			TheControlBar->markUIDirty();
	}
}
