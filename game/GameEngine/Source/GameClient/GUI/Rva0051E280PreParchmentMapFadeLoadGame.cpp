// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;

// The global at retail 0x012F3330 is EA's singleton, declared and defined once
// as GameWindowTransitionsHandler *TheTransitionHandler in
// GameWindowTransitions.cpp (?TheTransitionHandler@@3PAVGameWindowTransitionsHandler@@A).
// Members are reached through this file's own view of the object, cast at the
// use, so the called ILT thunks (0x00045C28 setGroup, 0x00042E6F isFinished)
// stay the ones retail calls.
// Retail's two transition calls leave through the ILT thunks 0x00045C28
// (setGroup) and 0x00042E6F (isFinished), which reach the real bodies
// 0x0048AD80 and 0x0048A4D0. Both are members of GameWindowTransitionsHandler
// and are defined once, in GameWindowTransitionsHandler.cpp and
// GameWindowTransitions_isFinished.cpp; this TU must spell them under that
// real class name, not a TU-local `TransitionHandler` view.
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name, bool immediate);
	bool isFinished(void);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell).
class Shell
{
};

// game/GameEngine/Source/Common/S3GuardedIndirectRelease.cpp owns the
// giveBack body at 0x0057F100, so the call is made through that view, exactly
// as Rva0051DD10StartBattleSchool.cpp does.
class Rva0057F100
{
public:
	void giveBack(void);
};
extern Shell *TheShell;

class WindowManager
{
public:
	void unidentified_0002e9a1(int value);
};
// Retail loads 0x012F19E8 here; that VA is the WindowManager singleton defined
// once as g_rva012F19E8WindowManager in GUI/WindowManager.cpp. `g_theWindowManager`
// matched EA's spelling but pointed at no definition at all.
extern WindowManager *g_rva012F19E8WindowManager;

class AudioClientUpdate
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
	virtual void slot30(int, int, int);
};
// retail reads the audio manager singleton (0x012ED668) here; defined in
// game/GameEngine/Source/Common/Audio/GameAudio.cpp.
class AudioManager;
extern AudioManager *TheAudio;

// ?rva0051E280PreParchmentMapFadeStartNew@@YAHH_N@Z
int rva0051E280PreParchmentMapFadeStartNew(int, bool start)
{
	const bool go = start;
	int result = 1;
	if (go)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_StartNew"), 0);
		if (TheShell)
			((Rva0057F100 *)TheShell)->giveBack();
		g_rva012F19E8WindowManager->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
	{
		((AudioClientUpdate *)TheAudio)->slot30(1, 1, 1);
		((AudioClientUpdate *)TheAudio)->slot30(2, 1, 1);
		((AudioClientUpdate *)TheAudio)->slot30(0, 1, 1);
		result = 3;
	}
	return result;
}
