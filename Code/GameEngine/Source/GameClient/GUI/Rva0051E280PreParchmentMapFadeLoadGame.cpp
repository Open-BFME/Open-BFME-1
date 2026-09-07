// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;

class TransitionHandler
{
public:
	void setGroup(AsciiString name, int immediate);
	bool isFinished(void);
};
extern TransitionHandler *TheTransitionHandler;

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
extern AudioClientUpdate *TheAudioClientUpdate;

// ?rva0051E280PreParchmentMapFadeStartNew@@YAHH_N@Z
int rva0051E280PreParchmentMapFadeStartNew(int, bool start)
{
	const bool go = start;
	int result = 1;
	if (go)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_StartNew"), 0);
		if (g_obj12F4B58)
			g_obj12F4B58->giveBack();
		g_theWindowManager->unidentified_0002e9a1(-1);
	}
	else if (TheTransitionHandler->isFinished())
	{
		TheAudioClientUpdate->slot30(1, 1, 1);
		TheAudioClientUpdate->slot30(2, 1, 1);
		TheAudioClientUpdate->slot30(0, 1, 1);
		result = 3;
	}
	return result;
}
