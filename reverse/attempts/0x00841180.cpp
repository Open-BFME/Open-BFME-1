// ?Rva00841180Dispatch@@YAXPAD@Z
// partial score=0.6316 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// RVA 0x00841180: adjust an object pointer by a stored offset and call slot zero.
struct Rva00841180Adjustment
{
    void *m_unknown;
    int m_offset;
};

class Rva00841180Target
{
public:
    virtual void invoke(int value) = 0;
};

void __cdecl Rva00841180Dispatch(char *object)
{
    Rva00841180Adjustment *adjustment =
        *reinterpret_cast<Rva00841180Adjustment **>(object);
    int offset = adjustment->m_offset;
    Rva00841180Target *target =
        reinterpret_cast<Rva00841180Target *>(object + offset);
    target->invoke(0);
}
