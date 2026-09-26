// Retail at 0x002206F0 is a five-byte tail virtual dispatch:
//     mov eax, [ecx]
//     jmp dword ptr [eax+0x64]
// The owning class is not recovered; the address-derived shim preserves the
// proven zero-based slot 25 and thiscall shape without inventing a semantic
// name.

struct Rva002206F0VirtualSlot25DispatchThunk
{
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void invoke() = 0;

    void dispatch();
};

void Rva002206F0VirtualSlot25DispatchThunk::dispatch()
{
    invoke();
}
