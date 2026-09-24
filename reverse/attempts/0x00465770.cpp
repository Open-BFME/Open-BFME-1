// ?Rva00465770MovieProperties@@YAXPAXPBDPAVGameWindow@@@Z
// partial score=0.938 date=2026-09-24
// Probe only: retail 0x00465770, 487 bytes. The owner is unknown.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" unsigned strlen(const char *);
#pragma intrinsic(strlen)

class BFMERetailAsciiString
{
public:
    BFMERetailAsciiString() : m_data(0) {}
    ~BFMERetailAsciiString() { releaseBuffer(); }
    void set(const char *text, int length);
    void set(const BFMERetailAsciiString &other);
    const char *str() const { return m_data ? m_data + 8 : ""; }
    unsigned getLength() const { return m_data ? *(const unsigned short *)(m_data + 4) : 0; }
private:
    void releaseBuffer();
    const char *m_data;
};

class BfmeStrVMZ;
char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);
void j_00030477();

class GameWindow;
struct Rva00465770MovieMessage;
class GameWindowManager
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32();
    virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38();
    virtual void slot39(); virtual void slot40(); virtual void slot41();
    virtual void slot42(); virtual void slot43(); virtual void slot44();
    virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50();
    virtual void slot51(); virtual void slot52();
    virtual int winSendSystemMsg(GameWindow *, unsigned, unsigned,
                                Rva00465770MovieMessage *);
};

extern GameWindowManager * volatile TheWindowManager;

struct Rva00465770MovieMessage
{
    Rva00465770MovieMessage() : flags(0), callback(0), window(0) {}
    BFMERetailAsciiString movieName;
    unsigned flags;
    void (* volatile callback)();
    GameWindow *window;
};

static inline BfmeStrVMZ *asParam(BFMERetailAsciiString *s)
{
    return reinterpret_cast<BfmeStrVMZ *>(s);
}

static inline bool containsTrue(const BFMERetailAsciiString &s)
{
    const char *p = s.str();
    const char *end = p + s.getLength();
    for (; p != end; ++p)
        if (*p == 't')
            return true;
    return false;
}

// The first parameter is unused in retail; only the query and window are read.
void Rva00465770MovieProperties(void *, const char *query, GameWindow *window)
{
    if (!window)
        return;

    BFMERetailAsciiString param;
    Rva00465770MovieMessage msg;
    if (bfmeGetParamVMZ(query, "_MovieName", asParam(&param)))
    {
        const char *movie = param.str();
        unsigned length = movie ? strlen(movie) : 0;
        msg.movieName.set(movie, length);
        bfmeGetParamVMZ(query, "_Loop", asParam(&param));
        if (containsTrue(param))
            msg.flags |= 4;
        bfmeGetParamVMZ(query, "_UseAlpha", asParam(&param));
        if (containsTrue(param))
            msg.flags |= 0x40;
        bfmeGetParamVMZ(query, "_HoldLastFrame", asParam(&param));
        if (containsTrue(param))
            msg.flags |= 0x80;
        if (bfmeGetParamVMZ(query, "_CallOnLastFrame", asParam(&param)))
            reinterpret_cast<BFMERetailAsciiString *>((char *)window + 0x268)->set(param);
        msg.callback = j_00030477;
        msg.window = window;
        GameWindowManager *manager = TheWindowManager;
        manager->winSendSystemMsg(window, 0x1D, 1000, &msg);
    }
}
