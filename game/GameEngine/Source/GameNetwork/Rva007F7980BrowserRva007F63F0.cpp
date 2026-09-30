// cl: /O2 /GS /GX-
// The matched callback wrapper, Rva007F7000, calls body 0x007F63F0 as a member of Rva007F7980Browser.
// Retail passes the address of Rva00808CB0LanGameEntry::m_sequence to both output calls before it constructs the object.

#include <new>

extern const char g_0112B7D0[];
extern const char g_0112B6B0[];

class Rva007E8810Message;
class Rva007F51D0Ticket
{
public:
    Rva007F51D0Ticket(Rva007E8810Message *message);
    int m_pid;
    __int64 m_uid;
    int m_port;
    char m_name[0x80];
    char m_ip[0x20];
    char m_ticket[0x80];
};
class Rva007E8760Addr
{
public:
    void parse(const char *text, int port);
private:
    char m_pad00[8];
    unsigned int m_address;
    int m_port;
};
struct Rva007EB810Diag
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void fail(const char *expr, const char *file, int line);
};
extern Rva007EB810Diag *Rva007EB810Get();
class BfmeB1251;
class BfmeS1251;
class BfmeA1251
{
public:
    void bfmeInit1251(BfmeB1251 *, BfmeS1251 *);
};
class Rva00802680Owner
{
public:
    virtual void v0(); virtual void v1();
    virtual int *v2(void *value);
};
class Rva00802040Owner
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual int *v9(void *result);
    Rva00802680Owner *findFree();
};
class Rva007F7980Listener
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(int value);
};
class Rva00800920Owner
{
public:
    int rva00800a40(void *record, unsigned char flag, int extra);
};
class Rva007E86B0Base
{
public:
    Rva007E86B0Base();
    virtual ~Rva007E86B0Base();
    int m_field04;
};
class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
    __forceinline Rva00808CB0LanGameEntry()
    {
        m_field08 = 0;
        m_field0c = 0;
        m_field04 = 0;
    }
    virtual ~Rva00808CB0LanGameEntry();
    int m_field08;
    int m_field0c;
    int m_sequence;
};
class Rva007F7980Browser
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void *findGame(int);
    void rva007f63f0(void *message);
private:
    char m_head[0x18];
    Rva007F7980Listener *m_listener;
    char m_pad20[4];
    Rva00800920Owner *field24;
    char m_pad28[0x2b0];
    Rva00802040Owner *field2d8;
};
void Rva007F7980Browser::rva007f63f0(void *message)
{
    if (field2d8 == 0)
        return;
    int storage[5];
    Rva007F51D0Ticket ticket((Rva007E8810Message *)message);
    Rva00802680Owner *freeSlot = field2d8->findFree();
    if (freeSlot == 0)
    {
        Rva007EB810Get()->fail(g_0112B7D0,
                               g_0112B6B0, 0x57d);
        return;
    }
    ((BfmeA1251 *)freeSlot)->bfmeInit1251((BfmeB1251 *)&ticket, (BfmeS1251 *)this);
    int slot = *freeSlot->v2(reinterpret_cast<int **>(&storage[4]));
    m_listener->v15(slot);
    int *value = field2d8->v9(reinterpret_cast<int **>(&storage[4]));
    if (*value != -2)
    {
        ::new ((void *)storage) Rva00808CB0LanGameEntry();
        ((Rva007E8760Addr *)storage)->parse(ticket.m_ip, ticket.m_port);
        field24->rva00800a40(reinterpret_cast<Rva00808CB0LanGameEntry *>(storage), 0, 0);
        reinterpret_cast<Rva00808CB0LanGameEntry *>(storage)->Rva00808CB0LanGameEntry::~Rva00808CB0LanGameEntry();
    }
}
