// cl: /DNDEBUG /MD /EHsc

class __declspec(novtable) GameEngine
{
public:
    virtual ~GameEngine();
};

__declspec(naked) GameEngine::~GameEngine()
{
    __asm {
        _emit 06Ah
        _emit 001h
        _emit 0E8h
        _emit 066h
        _emit 0EAh
        _emit 080h
        _emit 000h
        _emit 08Bh
        _emit 00Dh
        _emit 05Ch
        _emit 06Eh
        _emit 033h
        _emit 001h
        _emit 08Bh
        _emit 001h
        _emit 083h
        _emit 0C4h
        _emit 004h
        _emit 0FFh
        _emit 050h
        _emit 060h
        _emit 08Bh
        _emit 00Dh
        _emit 05Ch
        _emit 06Eh
        _emit 033h
        _emit 001h
        _emit 08Bh
        _emit 011h
        _emit 06Ah
        _emit 000h
        _emit 06Ah
        _emit 000h
        _emit 0FFh
        _emit 052h
        _emit 06Ch
        _emit 08Bh
        _emit 010h
        _emit 068h
        _emit 0F0h
        _emit 05Fh
        _emit 007h
        _emit 001h
        _emit 08Bh
        _emit 0C8h
        _emit 0FFh
        _emit 052h
        _emit 038h
        _emit 08Bh
        _emit 010h
        _emit 06Ah
        _emit 001h
        _emit 08Bh
        _emit 0C8h
        _emit 0FFh
        _emit 052h
        _emit 04Ch
        _emit 0B8h
        _emit 064h
        _emit 0A9h
        _emit 047h
        _emit 000h
        _emit 0C3h
    }
}
