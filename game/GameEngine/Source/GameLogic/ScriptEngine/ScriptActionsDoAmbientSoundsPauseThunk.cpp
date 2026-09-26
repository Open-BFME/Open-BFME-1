// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doAmbientSoundsPause(bool);
};

// The BFME audio client keeps the pause/resume entry at vtable slot 28.  The
// global is written as an absolute overlay so this TU emits the same DIR32
// literal as the retail call site (and does not require a guessed global
// declaration or a new linker alias).
class BfmeAudioClient
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
    virtual void slot27();
    virtual void pauseAmbient(int first, int second, int third);
};

#define TheAudioClientUpdate (*(BfmeAudioClient **)0x012ED668)

void ScriptActions::doAmbientSoundsPause(bool pause)
{
    int shouldPause = !pause;
    int *pausePtr = &shouldPause;
    TheAudioClientUpdate->pauseAmbient(0, 1, *pausePtr);
}
