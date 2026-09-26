// cl: /O2

class Rva007E8810Message;
class Rva007F7980Browser;
void Rva007F79F0Callback(Rva007E8810Message *message, Rva007F7980Browser *browser);

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
class Rva007F7A00Sender
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void send(BfmeC994 *message);
};
class Rva007F7A00Notifier
{
public:
    virtual void v0();
    virtual void v1();
    virtual void send(BfmeC994 *message,
        void (*callback)(Rva007E8810Message *, Rva007F7980Browser *),
        Rva007F7980Browser *owner, int transaction);
};
class Rva007F7A00Browser
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void prepare();
    void requestRegionCount();

    char m_unknown04[0x0C];
    Rva007F7A00Sender *m_sender;
    Rva007F7A00Notifier *m_notifier;
    char m_unknown18[0x2C4];
    char m_messageBuffer[0x400];
    int m_transaction;
};
void Rva007F7A00Browser::requestRegionCount()
{
    prepare();
    BfmeC994 message(m_messageBuffer, 0x400);
    m_sender->send(&message);
    m_notifier->send(&message, Rva007F79F0Callback,
        (Rva007F7980Browser *)this, m_transaction);
    ((Gen_007e86c0 *)&message)->m();
}
