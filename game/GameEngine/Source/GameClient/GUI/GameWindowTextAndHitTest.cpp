// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Two GameWindow members that sit next to each other in the image, 0x00479660
// and 0x00479770:
//
//   winSetText       0x00479660  114 B  UAE (public virtual)
//   winPointInChild  0x00479770  399 B  QAE (public)
//
// One sets the caption and tells the callback; the other walks the child list
// looking for the window under a point. Between them they describe the same
// object from opposite ends -- the text setter knew the callback at +0x04 and
// the instance data at +0x30, the hit test knew the status word and geometry
// at +0x08..+0x24 and the four list pointers at +0x1f8 -- and neither had any
// reason to mention the other's half. Declared once, the run reads:
//
//   +0x04 callback   +0x08 status   +0x0c size   +0x14 region
//   +0x30 instance data              +0x1f8 next/prev/parent/child
//
// GameWindowDestructorThunk.cpp, the third body in this run (0x00479CD0), does
// NOT join them, and the reason is the stand-in-name rule again: it reaches the
// instance data at +0x30 through a destructor thunk pinned as
// ??1Gen_uw_00021431@@QAE@XZ at 0x00021431, while winSetText reaches the SAME
// member through a setter thunk pinned as
// ?setText@WinInstanceDataShim@@QAEXVUnicodeString@@@Z at 0x00004205. One TU
// can give that member one type name, so one of the two pins would stop
// existing. Same member, two thunks, two stand-in names, each one load-bearing.

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	~AudioEventRTS();

private:
	char m_data[0x70];
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

class UnicodeString;

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

// Shim so the call keeps retail's ILT thunk at 0x00004205 rather than resolving
// to the matched WinInstanceData::setText body directly.
class WinInstanceDataShim
{
public:
	void setText(UnicodeString text);
};

class GameWindowCallback
{
public:
	virtual void callbackSlot0();
	virtual void callbackSlot1();
	virtual void callbackSlot2();
	virtual void onTextChanged(UnicodeString *text);	///< vtable +0xC
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual int winSetText(UnicodeString text);

	GameWindow *winPointInChild(Int x, Int y, Bool ignoreEnableCheck, Bool playDisabledSound);

	GameWindowCallback *m_callback;				// this+0x04
	unsigned int m_status;					// this+0x08
	Int m_sizeX;						// this+0x0c
	Int m_sizeY;						// this+0x10
	Int m_regionLoX;					// this+0x14
	Int m_regionLoY;					// this+0x18
	Int m_regionHiX;					// this+0x1c
	Int m_regionHiY;					// this+0x20
	char m_pad24[0x30 - 0x24];
	WinInstanceDataShim m_instData;				// this+0x30
	char m_pad34[0x1F8 - 0x34];
	GameWindow *m_next;					// this+0x1f8
	GameWindow *m_prev;					// this+0x1fc
	GameWindow *m_parent;					// this+0x200
	GameWindow *m_child;					// this+0x204
};

// The by-value parameter is copied once for the instance-data setter and then
// passed by address to the callback's fourth virtual, and MSVC destroys the
// parameter in the callee, which is the trailing releaseBuffer call.
// ?winSetText@GameWindow@@UAEHVUnicodeString@@@Z
int GameWindow::winSetText(UnicodeString text)
{
	m_instData.setText(text);

	if (m_callback != 0)
	{
		m_callback->onTextChanged(&text);
	}

	return 0;
}

// ?winPointInChild@GameWindow@@QAEPAV1@HH_N0@Z
GameWindow *GameWindow::winPointInChild(Int x, Int y, Bool ignoreEnableCheck, Bool playDisabledSound)
{
	GameWindow *child;

	for (child = m_child; child; child = child->m_next)
	{
		Int originX = child->m_regionLoX;
		Int originY = child->m_regionLoY;
		GameWindow *parent = child->m_parent;

		while (parent)
		{
			originX += parent->m_regionLoX;
			originY += parent->m_regionLoY;
			parent = parent->m_parent;
		}

		if (x >= originX && x <= originX + child->m_sizeX &&
			y >= originY && y <= originY + child->m_sizeY)
		{
			Bool enabled = ignoreEnableCheck || (child->m_status & 0x08) != 0;
			Bool hidden = ((child->m_status >> 4) & 1) != 0;

			if (!hidden)
			{
				if (enabled)
				{
					return child->winPointInChild(x, y, ignoreEnableCheck, playDisabledSound);
				}
				else if ((child->m_status & 0x20000000) != 0)
				{
					return child->winPointInChild(x, y, ignoreEnableCheck, playDisabledSound);
				}
				else if (playDisabledSound)
				{
					AudioEventRTS disabledClick((const char *)0x010f77bc, (ObjectID)2);
					if (TheAudio)
					{
						TheAudio->addAudioEvent(&disabledClick);
					}
				}
			}
		}
	}

	return this;
}
