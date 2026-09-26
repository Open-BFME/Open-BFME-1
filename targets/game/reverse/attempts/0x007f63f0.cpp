// ?d_007f63f0@@YAXXZ
// partial score=0.88 date=2026-09-26
// cl: /O2 /GS /GX-
// RVA 0x007F63F0 is a single body: branch at +0x44 enters its success path
// at +0x78; +0x75 is the early return when the free-slot assertion fails.
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
class Rva007F63F0Diag
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void fail(const char *expr, const char *file, int line);
};
extern Rva007F63F0Diag *Rva007EB810Get();
class Rva00802680Owner
{
public:
    virtual void v0(); virtual void v1();
    virtual int *v2(void *value);
    void bfmeInit1251(Rva007F51D0Ticket *, void *owner);
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
class Rva007F63F0Listener
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
    Rva00808CB0LanGameEntry()
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
class Rva007F63F0Owner
{
public:
    void handleTicket(Rva007E8810Message *message);
private:
    char m_pad00[0x1c];
    Rva007F63F0Listener *m_listener;
    char m_pad20[4];
    Rva00800920Owner *m_connection;
    char m_pad28[0x2b0];
    Rva00802040Owner *m_lobby;
};
void Rva007F63F0Owner::handleTicket(Rva007E8810Message *message)
{
    if (m_lobby == 0)
        return;
    int *slotResult;
    Rva007F51D0Ticket ticket(message);
    Rva00802680Owner *freeSlot = m_lobby->findFree();
    if (freeSlot == 0)
    {
        Rva007EB810Get()->fail((const char *)0x0112B7D0,
                               (const char *)0x0112B6B0, 0x57d);
        return;
    }
    freeSlot->bfmeInit1251(&ticket, this);
    m_listener->v15(*freeSlot->v2(&slotResult));
    int *value = m_lobby->v9(&slotResult);
    if (*value != -2)
    {
        Rva00808CB0LanGameEntry snapshot;
        ((Rva007E8760Addr *)&snapshot)->parse(ticket.m_ip, ticket.m_port);
        m_connection->rva00800a40(&snapshot, 0, 0);
    }
}
