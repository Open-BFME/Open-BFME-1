// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;
typedef float Real;

// 0x003BE150 (121B). Load-game Map_Roll movie step: Display viewport + the
// slot-57 movie call on start, else poll Display+0xF8 and GlobalData+0xA7D.
//
// This used to call the slot-57 entry playLogoMovie, and so did
// ScriptActions_doMoviePlayFullScreen_Thunk.cpp, while Display.h, GameClient.cpp
// and ScriptActions_doPlayMovieInGame_Thunk.cpp gave that name to a three-argument
// void. One name, two arities. They are two different virtuals and the vtable
// offsets say so outright: this body calls [eax+0xE4] after pushing four
// arguments -- the AsciiString, 0xC0, -1, -1 -- and doMoviePlayFullScreen calls
// [edx+0xE4] with four of its own, movieName, 0x40, -1, -1. doPlayMovieInGame
// calls [eax+0xE8] after pushing three. 0xE4 and 0xE8 are slots 57 and 58, so
// nothing here is one function under two signatures and the pair must not be
// merged.
//
// Slot 58 is the one that earns the name. Display.h declares
// `void playLogoMovie(AsciiString, Int minMovieLength, Int minCopyrightLength)`
// and GameClient.cpp calls it as ("EALogoMovie", 5000, 3000) -- three arguments,
// a movie with minimum display times, exactly what slot 58 takes. Slot 57 takes
// a small flags-like first int, two -1s, and returns a Bool this file polls
// across frames, which is a different operation whatever it is called. So the
// name on slot 57 was the wrong one, in both files that used it, and is now
// spelled unidentified_000000e4 after the convention already used below for
// unidentified_000000f8. No better name is claimed: naming it needs whatever
// implements slot 57 in Display's vtable.

class Display
{
public:
	virtual void slot00(); virtual void slot01();
	virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55();
	virtual void slot56();
	virtual Bool unidentified_000000e4(AsciiString name, int a, int b, int c);
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual Bool unidentified_000000f8(void);

	void rva002ED2E0(Real, Real, Real, Real);
};
extern Display *TheDisplay;

class GlobalData
{
public:
	unsigned char m_pad[0xA7D];
	Bool m_unidentifiedA7D;
};
extern GlobalData *TheWritableGlobalData;

// ?mapRollLoadGame@@YAHH_N@Z
int mapRollLoadGame(int, bool start)
{
	const bool go = start;
	Display *display = TheDisplay;
	int result = 1;
	if (go)
	{
		display->rva002ED2E0(0.0f, 0.0f, 1.0f, 1.0f);
		if (!TheDisplay->unidentified_000000e4(AsciiString("Map_Roll"), 0xC0, -1, -1))
			result = 3;
	}
	else if (display->unidentified_000000f8() || TheWritableGlobalData->m_unidentifiedA7D)
		result = 3;
	return result;
}
