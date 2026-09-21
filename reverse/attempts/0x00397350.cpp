// ?d_00397350@@YAXXZ
// partial score=0.62 date=2026-09-18
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00397350 (390 bytes).  The dispatcher calls this BFME helper with
// an Object and a Coord3D.  It walks that object's controlling player's
// objects through bfmeResolveReferenceIfEnabled; when the walk resolves one
// or more references, the local player receives the GlobalRallyPointSet text,
// a TransitionDamageFX audio event is positioned, and the selected drawable
// dirties the control bar.  No surviving symbol or vtable slot proves a
// historical class owner, so the function and its small state carrier keep
// the retail address in their names.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

protected:
	struct Data
	{
		Int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	void format(UnicodeString format, ...);
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
};

class Drawable
{
public:
	unsigned char m_unmodelled[0x3AC];
	Bool m_selected;
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
	virtual void message(UnicodeString text);
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, Int extra);
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
};

struct BfmeReferenceOwner;
struct BfmeReferenceResolveState;

extern Int bfmeResolveReferenceIfEnabled(
	BfmeReferenceOwner *owner, BfmeReferenceResolveState *state);

// The first three words are the position copied from the caller.  The last
// word is the count field at +0x0c in the independently landed reference
// resolver's state layout; the callback only relies on that trailing field.
struct Rva00397350ResolveState
{
	Coord3D m_position;
	Int m_resolvedCount;
};

#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheInGameUI (*(InGameUI **)0x012F148C)
#define TheAudioClientUpdate (*(AudioClient **)0x012ED668)
#define TheControlBar (*(ControlBar **)0x012F33F8)

inline void *operator new(unsigned int, void *place)
{
	return place;
}

// Retail's function-local static occupies 0x012F0D00 and owns the guard at
// 0x012F0D88.  Keeping those addresses explicit preserves the proven global
// identity while leaving construction and destruction as ordinary C++.
#define Rva00397350AudioEvent (*(AudioEventRTS *)0x012F0D00)
#define Rva00397350AudioGuard (*(unsigned int *)0x012F0D88)

extern "C" int __cdecl atexit(void (__cdecl *function)());

static void __cdecl Rva00397350DestroyAudioEvent()
{
	Rva00397350AudioEvent.~AudioEventRTS();
}

void Rva00397350GlobalRallyPointFeedback(
	Object *object, const Coord3D *position)
{
	Bool isLocal = object->isLocallyControlled();
	Rva00397350ResolveState state;
	state.m_position = *position;
	state.m_resolvedCount = 0;

	Player *player = object->getControllingPlayer();
	player->iterateObjects(
		(ObjectIterateFunc)bfmeResolveReferenceIfEnabled,
		(void *)&state);

	if (!isLocal || state.m_resolvedCount <= 0)
		return;

	UnicodeString message;
	message.format(TheGameText->fetch("GUI:GlobalRallyPointSet"));
	TheInGameUI->message(message);

	if ((Rva00397350AudioGuard & 1) == 0)
	{
		Rva00397350AudioGuard |= 1;
		AsciiString eventName("TransitionDamageFX");
		new ((void *)0x012F0D00) AudioEventRTS(eventName, 0);
		atexit(Rva00397350DestroyAudioEvent);
	}

	AudioEventRTS *event = (AudioEventRTS *)0x012F0D00;
	event->setPosition(position);
	event->setPlayerIndex(object->getControllingPlayer()->m_playerIndex);
	TheAudioClientUpdate->addAudioEvent(event);

	Drawable *drawable = object->getDrawable();
	if (drawable != 0 && drawable->m_selected)
		TheControlBar->m_uiDirty = true;
}
