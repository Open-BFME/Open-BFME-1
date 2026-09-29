// cl: /O2
// FESL game-browser hosted-game request at retail 0x007F61E0 (vtable slot
// 0x00D2B88C) and its reply adapter at 0x007F5A70, which hands the reply to
// Rva007F5920Owner::handleHostedGameReply. Same request shape as the region
// count request at 0x007F7A00: message over the +0x2dc buffer, sender, then
// notifier with the transaction id at +0x6dc.

class Rva007E8810Message;

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
class Rva007F61E0Sender
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void send(BfmeC994 *message, int first, int second, int id);
};
class Rva007F5920Owner;
class Rva007F61E0Notifier
{
public:
    virtual void v0();
    virtual void v1();
    virtual void send(BfmeC994 *message,
        void (*callback)(Rva007E8810Message *, Rva007F5920Owner *),
        Rva007F5920Owner *owner, int transaction);
};
class Rva007F5920Owner
{
public:
    void handleHostedGameReply(Rva007E8810Message *msg);
    void requestHostedGame(int first, int second);

    char m_pad00[0x10];
    Rva007F61E0Sender *m_sender;
    Rva007F61E0Notifier *m_notifier;
    char m_pad18[0x10];
    int m_defaultId;
    int m_overrideId;
    char m_pad30[0x2ac];
    char m_messageBuffer[0x400];
    int m_transaction;
};

void Rva007F5A70Callback(Rva007E8810Message *message, Rva007F5920Owner *owner)
{
    owner->handleHostedGameReply(message);
}

void Rva007F5920Owner::requestHostedGame(int first, int second)
{
    BfmeC994 message(m_messageBuffer, 0x400);
    m_sender->send(&message, first, second,
        m_overrideId ? m_overrideId : m_defaultId);
    m_notifier->send(&message, Rva007F5A70Callback, this, m_transaction);
    ((Gen_007e86c0 *)&message)->m();
}
