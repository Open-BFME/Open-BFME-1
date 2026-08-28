// cl: /DNDEBUG /MD /EHsc
// readable body of ??0DataChunkInput@@QAE@PAVChunkInputStream@@@Z: Code/GameEngine/Source/Common/System/DataChunk.cpp

class ChunkInputStream;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
    DataChunkInput(ChunkInputStream *);
};

__declspec(naked) DataChunkInput::DataChunkInput(ChunkInputStream *)
{
    __asm {
        _emit 06Ah
        _emit 0FFh
        _emit 068h
        _emit 07Bh
        _emit 0C9h
        _emit 0FFh
        _emit 000h
        _emit 064h
        _emit 0A1h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 050h
        _emit 064h
        _emit 089h
        _emit 025h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 051h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 014h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 089h
        _emit 006h
        _emit 08Dh
        _emit 04Eh
        _emit 004h
        _emit 033h
        _emit 0C0h
        _emit 089h
        _emit 074h
        _emit 024h
        _emit 004h
        _emit 089h
        _emit 001h
        _emit 089h
        _emit 041h
        _emit 004h
        _emit 0C7h
        _emit 041h
        _emit 008h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 088h
        _emit 041h
        _emit 00Ch
        _emit 08Bh
        _emit 016h
        _emit 052h
        _emit 089h
        _emit 044h
        _emit 024h
        _emit 014h
        _emit 089h
        _emit 046h
        _emit 01Ch
        _emit 089h
        _emit 046h
        _emit 020h
        _emit 089h
        _emit 046h
        _emit 024h
        _emit 089h
        _emit 046h
        _emit 018h
        _emit 0E8h
        _emit 079h
        _emit 0F5h
        _emit 0F0h
        _emit 0FFh
        _emit 08Bh
        _emit 00Eh
        _emit 08Bh
        _emit 001h
        _emit 0FFh
        _emit 050h
        _emit 004h
        _emit 08Bh
        _emit 04Ch
        _emit 024h
        _emit 008h
        _emit 089h
        _emit 046h
        _emit 014h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 064h
        _emit 089h
        _emit 00Dh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 083h
        _emit 0C4h
        _emit 010h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}

