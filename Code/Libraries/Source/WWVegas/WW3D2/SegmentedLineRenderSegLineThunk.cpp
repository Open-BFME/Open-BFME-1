// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rinfo.h
class RenderInfoClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/segline.h
class SegmentedLineClass
{
protected:
    void Render_Seg_Line(RenderInfoClass &);
};

__declspec(naked) void SegmentedLineClass::Render_Seg_Line(RenderInfoClass &)
{
    __asm {
        _emit 083h
        _emit 0ECh
        _emit 010h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 083h
        _emit 0BEh
        _emit 0DCh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 002h
        _emit 07Ch
        _emit 038h
        _emit 08Bh
        _emit 006h
        _emit 08Dh
        _emit 04Ch
        _emit 024h
        _emit 004h
        _emit 051h
        _emit 08Bh
        _emit 0CEh
        _emit 0FFh
        _emit 090h
        _emit 008h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 086h
        _emit 0D4h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 08Bh
        _emit 08Eh
        _emit 0DCh
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 06Ah
        _emit 000h
        _emit 08Dh
        _emit 054h
        _emit 024h
        _emit 008h
        _emit 052h
        _emit 050h
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 024h
        _emit 051h
        _emit 08Dh
        _emit 056h
        _emit 018h
        _emit 052h
        _emit 050h
        _emit 08Dh
        _emit 08Eh
        _emit 0E0h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0E8h
        _emit 089h
        _emit 000h
        _emit 001h
        _emit 000h
        _emit 05Eh
        _emit 083h
        _emit 0C4h
        _emit 010h
        _emit 0C2h
        _emit 004h
        _emit 000h
    }
}
