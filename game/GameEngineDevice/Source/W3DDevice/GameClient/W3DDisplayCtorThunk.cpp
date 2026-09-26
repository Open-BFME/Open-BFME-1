// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??0W3DDisplay@@QAE@XZ: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
    W3DDisplay();
};

__declspec(naked) W3DDisplay::W3DDisplay()
{
    __asm {
        _emit 0E9h
        _emit 0F9h
        _emit 081h
        _emit 06Fh
        _emit 000h
    }
}
