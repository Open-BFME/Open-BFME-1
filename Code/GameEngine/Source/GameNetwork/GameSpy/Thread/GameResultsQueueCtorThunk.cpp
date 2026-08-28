// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0GameResultsQueue@@QAE@XZ: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp

class GameResultsQueue
{
public:
    GameResultsQueue();
};

__declspec(naked) GameResultsQueue::GameResultsQueue()
{
    __asm {
        _emit 0E9h
        _emit 07Eh
        _emit 005h
        _emit 063h
        _emit 000h
    }
}
