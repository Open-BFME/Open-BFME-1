// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The two movie actions:
//
//   0x002F3FF0  doMoviePlayFullScreen  MOVIE_PLAY_FULLSCREEN
//   0x002F59C0  doPlayMovieInGame      MOVIE_PLAY_INGAME
//
// Both build the movie name in place through the by-value wrapper and hand it
// to TheDisplay. The full-screen form bails out on low detail and while a movie
// is already playing, and sets the viewport first; the in-game form pauses the
// movie system, plays, and marks the display as playing.
//
// They call DIFFERENT vtable entries, and this was worth settling from the
// image rather than assumed, because the two entries share a name and sit next
// to each other. Retail says so directly -- 0x002F3FF0+0x60 is
// `call dword ptr [edx + 0xe4]` after pushing 0x40, -1, -1 and the string,
// while 0x002F59C0+0x27 is `call dword ptr [eax + 0xe8]` after pushing 0x30,
// the cancel flag and the string. So +0xE4 takes four arguments and +0xE8 takes
// three; neither file had mis-indexed the other's slot, and declaring both as
// overloads at their own offsets is what lets these two share a TU at all.

#include <stddef.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern float g_bfmeUint32Scale; // retail 0x01075358 (2^32 conversion fixup)

#include "ascii_string.h"

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual UnsignedInt getWidth() = 0;
	virtual UnsignedInt getHeight() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0; virtual void slot56() = 0;
	// These two are DIFFERENT virtuals, not one under two signatures: the call
	// sites reach [edx+0xE4] with four arguments and [eax+0xE8] with three, and
	// 0xE4 and 0xE8 are slots 57 and 58. Only the three-argument one is
	// playLogoMovie -- Display.h declares it as (AsciiString, Int
	// minMovieLength, Int minCopyrightLength) and GameClient.cpp calls it as
	// ("EALogoMovie", 5000, 3000). The four-argument one takes a flags-like int
	// and two -1s and returns a Bool that Map_Roll_LoadGame polls across frames,
	// so it is named for its offset until its owner is known.
	//
	// Declaration order is load-bearing either way, and WHICH rule applies
	// depends on whether the two names match. While both were called
	// playLogoMovie they formed one overload group, and MSVC 7.1 assigns an
	// overload group's slots in REVERSE declaration order, so the
	// three-argument form had to be written first to land at +0xE8. Distinct
	// names are not an overload group and take plain declaration order, so the
	// +0xE4 entry is written first now. Swap these two lines and both bodies
	// compile with each other's offset -- `ff 92 e8` where retail has
	// `ff 92 e4` -- which is how the ordering was established in both
	// arrangements.
	virtual void unidentified_000000e4(BfmeAsciiStringArg, int, int, int) = 0; // +0xE4 -- NOT playLogoMovie: different slot, different arity
	virtual void playLogoMovie(BfmeAsciiStringArg, Int, Int) = 0;      // +0xE8
	virtual void slot59() = 0;
	virtual Bool isMoviePlaying() = 0;

	void rva002ED2E0(Real, Real, Real, Real);
	void setMoviePlaying(Bool playing) { m_moviePlaying = playing; }

private:
	unsigned char m_unmodelled[0x104];
	Bool m_moviePlaying;
};

void Display::rva002ED2E0(Real left, Real top, Real right, Real bottom)
{
	*(Real *)((unsigned char *)this + 0xf8) = (Real)getWidth() * left;
	*(Real *)((unsigned char *)this + 0xfc) = (Real)getHeight() * top;
	*(Real *)((unsigned char *)this + 0x100) = (Real)getWidth() * right;
	*(Real *)((unsigned char *)this + 0x104) = (Real)getHeight() * bottom;
}

struct BfmeGameLODManager
{
	unsigned char m_unreconstructed[0x16c4];
	int m_staticLODLevel;
};

extern Display *TheDisplay;
extern BfmeGameLODManager *TheGameLODManager;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void setMoviePause(Bool) = 0;

protected:
	void doMoviePlayFullScreen(const AsciiString &, Bool);
	void doPlayMovieInGame(const AsciiString &, Bool);
};

// ?doMoviePlayFullScreen@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::doMoviePlayFullScreen(const AsciiString &movieName, Bool skipLowDetail)
{
	if (skipLowDetail && TheGameLODManager->m_staticLODLevel <= 1) {
		return;
	}
	if (TheDisplay->isMoviePlaying()) {
		return;
	}

	TheDisplay->rva002ED2E0(0.0f, 0.0f, 1.0f, 1.0f);
	TheDisplay->unidentified_000000e4(movieName, 64, -1, -1);
}

// ?doPlayMovieInGame@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::doPlayMovieInGame(const AsciiString &movieName, Bool allowCancel)
{
	setMoviePause(true);
	TheDisplay->playLogoMovie(movieName, *(const Int *)&allowCancel, 48);
	TheDisplay->setMoviePlaying(true);
}
