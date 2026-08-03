// cl: /DNDEBUG /MD /EHsc

class Object;
enum CommandSourceType
{
    CommandSourceTypeAnchor
};

__declspec(naked) bool isObjectShroudedForAction(const Object*, const Object*, CommandSourceType)
{
    __asm {
        _emit 085h
        _emit 0F6h
        _emit 074h
        _emit 011h
        _emit 08Bh
        _emit 046h
        _emit 074h
        _emit 03Dh
        _emit 0FCh
        _emit 0E0h
        _emit 0F5h
        _emit 005h
        _emit 07Ch
        _emit 007h
        _emit 03Dh
        _emit 0FFh
        _emit 0E0h
        _emit 0F5h
        _emit 005h
        _emit 07Eh
        _emit 042h
        _emit 085h
        _emit 0FFh
        _emit 074h
        _emit 03Eh
        _emit 085h
        _emit 0F6h
        _emit 074h
        _emit 03Ah
        _emit 08Bh
        _emit 0CFh
        _emit 0E8h
        _emit 080h
        _emit 0C8h
        _emit 0F5h
        _emit 0FFh
        _emit 085h
        _emit 0C0h
        _emit 074h
        _emit 02Fh
        _emit 08Bh
        _emit 0CFh
        _emit 0E8h
        _emit 075h
        _emit 0C8h
        _emit 0F5h
        _emit 0FFh
        _emit 08Bh
        _emit 048h
        _emit 02Ch
        _emit 085h
        _emit 0C9h
        _emit 075h
        _emit 021h
        _emit 083h
        _emit 07Ch
        _emit 024h
        _emit 004h
        _emit 001h
        _emit 074h
        _emit 01Ah
        _emit 08Bh
        _emit 0CFh
        _emit 0E8h
        _emit 060h
        _emit 0C8h
        _emit 0F5h
        _emit 0FFh
        _emit 08Bh
        _emit 040h
        _emit 024h
        _emit 050h
        _emit 08Bh
        _emit 0CEh
        _emit 0E8h
        _emit 04Fh
        _emit 078h
        _emit 0F6h
        _emit 0FFh
        _emit 083h
        _emit 0F8h
        _emit 003h
        _emit 07Ch
        _emit 003h
        _emit 0B0h
        _emit 001h
        _emit 0C3h
        _emit 032h
        _emit 0C0h
        _emit 0C3h
    }
}
