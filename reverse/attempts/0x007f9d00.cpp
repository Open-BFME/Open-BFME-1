// ?d_007f9d00@@YAXXZ
// partial score=0.3 date=2026-09-22
// ABI experiment: raw message storage and one declared request parameter.
// cl: /O2 /GX-

struct Rva007F9D00Request
{
    int m_00, m_04, m_08, m_0C, m_10, m_14, m_18, m_1C, m_20;
};

class Rva007E8810Message
{
public:
    Rva007E8810Message();
    ~Rva007E8810Message();
    int getError();
    void setError(int code);
    int m_00, m_04, m_08, m_0C;
    char *m_10;
    int m_14, m_18, m_1C, m_20, m_24, m_28, m_2C;
    unsigned char m_30;
    unsigned char m_pad31[3];
};

struct Rva007FA170Slot
{
    void *m_00;
    int m_04;
    Rva007E8810Message *m_08;
    void (__cdecl *m_0C)(Rva007E8810Message *message, void *context);
    void *m_10;
    int m_14;
    int m_18;
};

class Rva007F9D00Hub
{
public:
    virtual void v0();
    virtual int v1(Rva007E8810Message *message);
    virtual int v2(Rva007E8810Message *message);
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual bool v6(Rva007E8810Message *message);
    virtual bool v7(Rva007E8810Message *message);
};

class Rva007FA2C0
{
public:
    bool onTxn(Rva007E8810Message *message);
    void d_007f97b0(Rva007E8810Message *message, Rva007FA170Slot *slot);
    void clearSlot(void *slot);
    char m_pad00[0x14];
    int m_14;
    char m_pad18[8];
    void *m_20;
    Rva007F9D00Hub *m_24;
};

class Rva007EB810Diag
{
public:
    virtual void v0();
    virtual void v1();
    virtual void log(int level, const char *format, ...);
};

Rva007EB810Diag *Rva007EB810Get();
void __cdecl Rva007F91D0(void *header, const char *direction);

class Rva007F9D00Owner
{
public:
    virtual void process(Rva007F9D00Request *request);
private:
    char m_pad00[0x1c];
    Rva007F9D00Hub *m_hub;
    Rva007FA170Slot m_slots[0x20];
};

#define MESSAGE ((Rva007E8810Message *)messageStorage)

void Rva007F9D00Owner::process(Rva007F9D00Request *request)
{
    char messageStorage[0x34];
    MESSAGE->Rva007E8810Message::Rva007E8810Message();
    MESSAGE->m_10 = (char *)request->m_08;
    MESSAGE->m_14 = request->m_0C;
    MESSAGE->m_1C = request->m_00;
    MESSAGE->m_20 = request->m_04;
    MESSAGE->m_04 = request->m_18;
    MESSAGE->m_0C = request->m_20;
    MESSAGE->m_08 = request->m_1C;
    MESSAGE->setError(m_hub->v2(MESSAGE));
    int result = m_hub->v1(MESSAGE);
    bool accepted = m_hub->v7(MESSAGE);
    if (result != 0 && !m_hub->v6(MESSAGE))
    {
        Rva007FA170Slot *slot = m_slots;
        int index = 0;
        while (slot->m_00 != (void *)result && index < 0x20)
        {
            ++index;
            ++slot;
        }
        if (slot->m_00 == (void *)result)
        {
            if (m_hub->v7(MESSAGE))
            {
                ((Rva007FA2C0 *)((char *)this - 4))->d_007f97b0(
                    MESSAGE, slot);
                MESSAGE->Rva007E8810Message::~Rva007E8810Message();
                return;
            }
            if (slot->m_08)
            {
                Rva007E8810Message *record = slot->m_08;
                Rva007F91D0(request, "block");
                record->m_20 = result;
                record->m_1C = MESSAGE->m_24;
                record->setError(MESSAGE->getError());
                if (record->m_14 < request->m_0C)
                    record->setError(-100);
                else
                    record->m_18 = request->m_0C;
                slot->m_04 = 2;
                MESSAGE->Rva007E8810Message::~Rva007E8810Message();
                return;
            }
            if (slot->m_0C)
            {
                Rva007F91D0(request, "nonblock");
                ++((Rva007FA2C0 *)((char *)this - 4))->m_14;
                slot->m_0C(MESSAGE, slot->m_10);
                --((Rva007FA2C0 *)((char *)this - 4))->m_14;
                ((Rva007FA2C0 *)((char *)this - 4))->clearSlot(slot);
                MESSAGE->Rva007E8810Message::~Rva007E8810Message();
                return;
            }
            Rva007F91D0(request, "ignored");
            Rva007EB810Get()->log(0, "ignored", result);
            MESSAGE->Rva007E8810Message::~Rva007E8810Message();
            return;
        }
    }
    if (*((unsigned char *)&request + 4))
    {
        Rva007F91D0(request, "report");
        MESSAGE->Rva007E8810Message::~Rva007E8810Message();
        return;
    }
    Rva007F91D0(request, "owner");
    if (!((Rva007FA2C0 *)((char *)this - 4))->onTxn(MESSAGE))
        Rva007EB810Get()->log(0, "failure", result);
    MESSAGE->Rva007E8810Message::~Rva007E8810Message();
}

#undef MESSAGE
