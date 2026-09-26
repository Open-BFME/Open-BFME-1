// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class GameWindow;
class UnicodeString {};

GameWindow *MessageBoxOk(UnicodeString, UnicodeString, void (*)(void));

class MessageBoxOkShim
{
public:
    static GameWindow *run(UnicodeString title, UnicodeString body, void (*cb)(void));
};

GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body, void (*cb)(void))
{
    return MessageBoxOkShim::run(title, body, cb);
}
