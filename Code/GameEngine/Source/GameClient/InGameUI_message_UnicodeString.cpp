// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
    virtual void message(UnicodeString, ...);
};

__declspec(naked) void InGameUI::message(UnicodeString, ...)
{
    __asm {
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 0E9h
        _emit 0E7h
        _emit 0A2h
        _emit 044h
        _emit 000h
    }
}
