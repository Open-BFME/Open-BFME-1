// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;

// The global at retail 0x012F3330 is EA's singleton, declared and defined once
// as GameWindowTransitionsHandler *TheTransitionHandler in
// GameWindowTransitions.cpp (?TheTransitionHandler@@3PAVGameWindowTransitionsHandler@@A).
// Members are reached through this file's own view of the object, cast at the
// use, so the called ILT thunks (0x00045C28 setGroup, 0x00042E6F isFinished)
// stay the ones retail calls.
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class TransitionHandler
{
public:
	void setGroup(AsciiString name, int immediate);
	bool isFinished(void);
};

class Rva0057F100
{
public:
	void giveBack(void);
};
extern Rva0057F100 *g_obj12F4B58;

class WindowManager
{
public:
	void unidentified_0002e9a1(int value);
};
extern WindowManager *g_theWindowManager;

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
		((TransitionHandler *)TheTransitionHandler)->setGroup(AsciiString("PreParchmentMapFade_StartNew"), 0);
		if (g_obj12F4B58)
			g_obj12F4B58->giveBack();
		g_theWindowManager->unidentified_0002e9a1(-1);
	}
	else if (((TransitionHandler *)TheTransitionHandler)->isFinished())
	{
		((AudioClientUpdate *)TheAudio)->slot30(1, 1, 1);
		((AudioClientUpdate *)TheAudio)->slot30(2, 1, 1);
		((AudioClientUpdate *)TheAudio)->slot30(0, 1, 1);
		result = 3;
	}
	return result;
}
