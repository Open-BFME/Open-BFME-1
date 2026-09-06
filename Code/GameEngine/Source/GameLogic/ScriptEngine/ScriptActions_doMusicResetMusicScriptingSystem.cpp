// cl: /Ireference/shims/stringinline
// Reset the music scripting system and set its initialization flag.

#include "StringInline.h"

class ClientSubsystem
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void pauseAudio(int first, int second, int third);
};

class BFMEScriptEngineFlagLookup
{
public:
	bool *findFlag(AsciiString name);
};

#define TheAudioClientUpdate (*(ClientSubsystem **)0x012ED668)
extern BFMEScriptEngineFlagLookup *TheScriptEngine;

class ScriptActions
{
protected:
	void doMusicResetMusicScriptingSystem(bool fadeout);
};

void ScriptActions::doMusicResetMusicScriptingSystem(bool fadeout)
{
	int pause = !fadeout;
	int *pausePtr = &pause;
	TheAudioClientUpdate->pauseAudio(0, 0, *pausePtr);
	char text[] = "/___MusicScript_Init";
	bool *flag = ((BFMEScriptEngineFlagLookup *)TheScriptEngine)->findFlag(
		AsciiString(text));
	if (flag != 0)
		*flag = true;
}
