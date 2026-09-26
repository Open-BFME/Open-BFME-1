// cl: /O2

class Rva007E8810Message;
class Rva007F6260GameBrowser;
void Rva007F62E0Callback(Rva007E8810Message *, Rva007F6260GameBrowser *);
void a_007ea650();

int Rva007EB810Get();
class Rva007EB810Diag
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void fail(const char *, const char *, int);
};
class BfmeC994
{
public:
    BfmeC994(char *buffer, int size);
    char m_unknown[0x34];
};
class Gen_007e86c0
{
public:
    void m();
};
class Rva007EA6A0FieldAddress
{
public:
    char *get();
};
class Rva007EA6B0Accessor
{
public:
    void *getAt80();
};
class Rva007F62F0Owner
{
public:
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void send(BfmeC994 *message, void *a, void *b, const char *key, void *c);
};
class Rva007F62F0Notifier
{
public:
    virtual void v0();
    virtual void v1();
    virtual void send(BfmeC994 *message,
        void (*callback)(Rva007E8810Message *, Rva007F6260GameBrowser *),
        Rva007F6260GameBrowser *owner, int transaction);
};
class Rva007F62F0Failure
{
public:
    virtual void v0();
    virtual void report(int code);
};
class Rva007F62F0ConnectRequest
{
    void *m_vptr;
    void *m_field04;
    void *m_field08;
    Rva007F62F0Owner *m_sender;
    Rva007F62F0Notifier *m_notifier;
    char m_unknown14[4];
    Rva007F62F0Failure *m_failure;
    char m_unknown1c[0x10];
    int m_state;
    char m_unknown30[0x2A8];
    char m_buffer[0x400];
    int m_transaction;
public:
    void request(int action, void *unused, int *status);
};
void Rva007F62F0ConnectRequest::request(int action, void *, int *status)
{
    if (action == 3)
    {
        if (m_state != 1)
            ((Rva007EB810Diag *)Rva007EB810Get())->fail(
                "mState == GameBrowserStateConnectingNetwork",
                "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp", 0x529);
        m_state = 2;
        BfmeC994 message(m_buffer, 0x400);
        m_sender->send(&message,
            ((void *(__fastcall *)(void *))a_007ea650)(m_field08),
            ((Rva007EA6B0Accessor *)m_field08)->getAt80(), "PC",
            ((Rva007EA6A0FieldAddress *)m_field08)->get());
        m_notifier->send(&message, Rva007F62E0Callback,
            (Rva007F6260GameBrowser *)((char *)this - 4), m_transaction);
        ((Gen_007e86c0 *)&message)->m();
        return;
    }
    if (action == 0)
    {
        int code = -1;
        if (status)
            code = *status;
        m_state = 0;
        m_failure->report(code);
    }
}
