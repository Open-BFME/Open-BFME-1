// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

#include "PreRTS.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
    void doAmbientSoundsPause(bool);
};

__declspec(naked) void ScriptActions::doAmbientSoundsPause(bool)
{
    __asm {
        _emit 08Ah
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 033h
        _emit 0C0h
        _emit 084h
        _emit 0C9h
        _emit 08Bh
        _emit 00Dh
        _emit 068h
        _emit 0D6h
        _emit 02Eh
        _emit 001h
        _emit 08Bh
        _emit 011h
        _emit 00Fh
        _emit 094h
        _emit 0C0h
        _emit 050h
        _emit 06Ah
        _emit 001h
        _emit 06Ah
        _emit 000h
        _emit 0FFh
        _emit 052h
        _emit 070h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
