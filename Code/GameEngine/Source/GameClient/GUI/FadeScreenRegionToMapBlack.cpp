// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

typedef bool Bool;
typedef int Int;

struct RGBColor;

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass
{
public:
	RecorderModeType getMode();
	void stopRecording();
};
extern RecorderClass *TheRecorder;

class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool unknown);
};
extern BfmeGameLogicPause *TheGameLogic;

class Glo012F7048Type
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void setEnabled(Bool enabled);
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void setMode(Int mode, Bool enabled);
};
extern Glo012F7048Type *Glo012F7048;

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class TransitionHandler
{
public:
	bool isFinished();
};

class Rva004893D0ByteClear
{
public:
	void clear();
};

class BfmeZ1100
{
public:
	void bfmeEnd1100(Int visible);
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
	virtual void setCursor(Int cursor);
};
extern BfmeZ1100 *TheMouse;

class Mouse
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
	virtual void setCursor(Int cursor);
	void setCursorTooltip(UnicodeString tooltip, Int delay, const RGBColor *color, float width);
};

// ?fade005651F0@@YAIM_N@Z
unsigned fade005651F0(float, Bool firstCall)
{
	unsigned result = 1;

	if (firstCall)
	{
		if (TheRecorder->getMode() == RECORDERMODETYPE_RECORD)
			TheRecorder->stopRecording();
		TheGameLogic->clearGameData(false, false);
		TheTransitionHandler->setGroup(AsciiString("FadeScreenRegionToMapBlack"));
		((Rva004893D0ByteClear *)TheTransitionHandler)->clear();
		Glo012F7048->setEnabled(true);
		Glo012F7048->setMode(3, false);
	}
	else if (((TransitionHandler *)TheTransitionHandler)->isFinished())
	{
		result = 3;
		((Mouse *)TheMouse)->setCursor(1);
		TheMouse->bfmeEnd1100(1);
		((Mouse *)TheMouse)->setCursorTooltip(
			*reinterpret_cast<const UnicodeString *>(0x01336E54), -1, 0, 1.0f);
		Glo012F7048->setMode(1, false);
	}

	return result;
}
