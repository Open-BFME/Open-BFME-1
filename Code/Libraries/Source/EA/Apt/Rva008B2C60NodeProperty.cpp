// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B2C60, 332 bytes. Three stack args, ret12, AL return.
// docs/analysis/0x008985c0.md B/C/E proves the value/handle/block layouts.
// Retail NodeName/NodeValue literals select receiver+20 vslots 38/44.
// Proprietary owner identity is unproved; all owner names retain addresses.
struct BfmeStringData3AF0
{
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0
{
    void *m_unknown00;
    void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern int bfmeCompareVSC(const char *, const char *);

class Rva8CD130String
{
public:
    Rva8CD130String()
    {
        m_data = &g_bfmeDefaultString1284;
        ++m_data->m_refCount;
    }
    ~Rva8CD130String()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }
    const char *text() const { return (const char *)m_data + 8; }
    BfmeStringData3AF0 *m_data;
};
class NodeProperty008B2C60Receiver
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38(const char *);
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44(const char *);
};
class Rva8CD130Value
{
public:
    void getName(Rva8CD130String *output);
    bool isUndefined() const { return ((m_flags >> 15) & 1) == 0; }
    bool isString() const
    {
        unsigned type = m_flags & 0x3f;
        return (type == 1 || type == 42) && !isUndefined();
    }
    void *m_unknown00;
    unsigned m_flags;
    unsigned char m_unknown08[0x18];
    NodeProperty008B2C60Receiver *m_receiver20;
};

bool __stdcall rva008B2C60NodeProperty(Rva8CD130Value *self,
    Rva8CD130String *key, Rva8CD130Value *value)
{
    if ((self->m_flags & 0x3f) == 32)
    {
        if (bfmeCompareVSC(key->text(), "NodeName") == 0)
        {
            if (value->isString())
            {
                Rva8CD130String text;
                value->getName(&text);
                if (self->m_receiver20)
                    self->m_receiver20->slot38(text.text());
            }
        }
        else if (bfmeCompareVSC(key->text(), "NodeValue") == 0)
        {
            if (value->isString())
            {
                Rva8CD130String text;
                value->getName(&text);
                if (self->m_receiver20)
                    self->m_receiver20->slot44(text.text());
            }
        }
    }
    return true;
}
