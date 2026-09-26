// ?aptSetRectField008B7210@@YAPAVAptValue@@PAURva008B6D70Obj@@H@Z
// partial score=0.91 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B7210: set the second rect field and refresh with a negative context.
class AptValue
{
public:
    int toInteger() const;
};

struct Rva008B6D70Obj
{
    char m_padding00[0x20];
    char m_rect[0x20];
    char m_extra[0x20];
    int m_context;
    void refreshNeg(void *field, void *rect, int negativeContext);
};

extern AptValue *g_bfmeFallbackDB;
extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
AptValue *Rva008B6D70MakeValue(int value);

AptValue *aptSetRectField008B7210(Rva008B6D70Obj *self, int argc)
{
    if (argc < 1)
        return g_bfmeFallbackDB;
    int *field = (int *)self->m_extra;
    int value = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
    self->refreshNeg(&(*field = value), self->m_rect, -self->m_context);
    return Rva008B6D70MakeValue(0);
}
