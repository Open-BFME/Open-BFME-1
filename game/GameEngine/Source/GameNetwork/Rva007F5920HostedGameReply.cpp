// cl: /O2 /GS /GX-
// FESL game-browser hosted-game reply at 0x007F5920. The adjacent ticket
// handler shares listener +0x1c, connection +0x24 and lobby +0x2d8.
class Rva007F5920Diag
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void fail(const char *expr, const char *file, int line);
};
struct Rva007EB810Diag;
extern Rva007EB810Diag *Rva007EB810Get();
class Rva007E8810Message
{
public:
    bool hasError();
    int getError();
};
class Rva007F5080Game
{
public:
    Rva007F5080Game(Rva007E8810Message *msg);
    int m_lid;
    int m_gid;
    int m_maxPlayers;
    char m_ugid[0x25];
    char m_secret[0x80];
    int m_lobbyId;
    int m_gameId;
};
class Gen007F0130
{
public:
    static void *operator new(unsigned int size);
};
class Rva00802040Src;
class Rva00802040OwnerSrc;
class Rva00802040Owner : public Gen007F0130
{
public:
    Rva00802040Owner(Rva00802040Src *game, Rva00802040OwnerSrc *owner);
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual int *v9(void *out);
    virtual int *v10(void *out);
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(void *value);
    virtual void v15(void *secret);
private:
    char m_storage[0xd4];
};
class Rva007F5920Listener
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(int status);
};
class Rva008006C0Owner
{
public:
    int connect(const char *ugid, const char *secret, int flag);
};
class Rva007F5920Owner
{
public:
    void handleHostedGameReply(Rva007E8810Message *msg);
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void v22(int lhs, int rhs);
private:
    char m_pad004[0x18];
    Rva007F5920Listener *m_listener;
    char m_pad020[4];
    Rva008006C0Owner *m_connection;
    char m_pad028[0xe];
    unsigned char m_flag36;
    char m_pad037[0x2a1];
    Rva00802040Owner *m_lobby;
};
void Rva007F5920Owner::handleHostedGameReply(Rva007E8810Message *msg)
{
    if (msg->hasError()) {
        int status = msg->getError();
        m_listener->v13(status);
        return;
    }
    Rva007F5080Game game(msg);
    if (m_lobby)
        ((Rva007F5920Diag *)Rva007EB810Get())->fail(
            "!mHostedGame",
            "\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
            0x32c);
    m_lobby = new Rva00802040Owner((Rva00802040Src *)&game,
                                    (Rva00802040OwnerSrc *)this);
    m_lobby->v14(game.m_ugid);
    m_lobby->v15(game.m_secret);
    m_listener->v13(0);
    int *secondOutput;
    if (m_flag36) {
        int *firstOutput;
        int *left = m_lobby->v10(&firstOutput);
        int *right = m_lobby->v9(&secondOutput);
        v22(*right, *left);
    }
    if (*m_lobby->v9(&secondOutput) != -2)
        m_connection->connect(game.m_ugid, game.m_secret, 0);
}
