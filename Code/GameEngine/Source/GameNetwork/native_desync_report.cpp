// cl: /DNDEBUG /MD /GX

typedef bool Bool;
typedef int Int;

typedef unsigned int UnsignedInt;

struct GameLogicBFMERetailLayout
{
    unsigned char m_padding[0x3C];
    UnsignedInt m_frame;
    unsigned char m_padding40[0xCC];
    Int m_gameMode;
};

class GameLogicBFMEShim
{
public:
    UnsignedInt getCRC(Int mode);
    UnsignedInt getFrame() const
    {
        return reinterpret_cast<const GameLogicBFMERetailLayout *>(this)->m_frame;
    }
};

extern GameLogicBFMEShim *TheGameLogic;
// Retail enable byte at VA 0x012ED4E4.
extern unsigned char BfmeClientCRCCheckEnabled;

// The string accessors and lifetimes follow the retail StringBase layout.
template <typename T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    struct Header
    {
        int references;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    const char *str() const { return m_data ? m_data->text : ""; }
    int getLength() const { return m_data ? m_data->length : 0; }
    void __cdecl format(AsciiString fmt, ...);
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class IPEnumeration
{
public:
    IPEnumeration();
    ~IPEnumeration();
    AsciiString getMachineName();
private:
    void *m_ipList;
    Bool m_isWinsockInitialized;
};

class DesyncInGameUI
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void message(UnicodeString text, ...);
};
extern DesyncInGameUI *TheInGameUI;

struct DesyncSystemTime
{
    unsigned short year, month, dayOfWeek, day, hour, minute, second, milliseconds;
};
struct DesyncFile;
extern "C" {
    __declspec(dllimport) DesyncFile *__cdecl fopen(const char *, const char *);
    __declspec(dllimport) unsigned int __cdecl fwrite(const void *, unsigned int, unsigned int, DesyncFile *);
    __declspec(dllimport) int __cdecl fclose(DesyncFile *);
    __declspec(dllimport) void __stdcall GetLocalTime(DesyncSystemTime *);
}

// A local simulation-integrity guard around client subsystem updates. The
// matched caller at RVA 0x0006B910 constructs this record before the radar,
// client and message updates, and destroys it after network liteupdate.
// The class name is descriptive; retail's original spelling is unknown.
class BFMEDesyncCheck
{
public:
    BFMEDesyncCheck();
    void writeReportIfMismatched();
private:
    UnsignedInt m_crcBeforeClientUpdate;
};

// ??0BFMEDesyncCheck@@QAE@XZ
BFMEDesyncCheck::BFMEDesyncCheck()
{
	if (BfmeClientCRCCheckEnabled != 0)
	{
		GameLogicBFMERetailLayout *logic = reinterpret_cast<GameLogicBFMERetailLayout *>( TheGameLogic );
		if (logic->m_gameMode != 8 && logic->m_gameMode != 4)
		{
			m_crcBeforeClientUpdate = TheGameLogic->getCRC( 0 );
			return;
		}
	}
	m_crcBeforeClientUpdate = 0;
}

// Both CRCs come from this machine. A difference means client work changed
// simulation state outside GameLogic::update; this is not a peer CRC exchange.
void BFMEDesyncCheck::writeReportIfMismatched()
{
    if (BfmeClientCRCCheckEnabled == 0)
        return;
    if (reinterpret_cast<GameLogicBFMERetailLayout *>(TheGameLogic)->m_gameMode == 8 ||
        reinterpret_cast<GameLogicBFMERetailLayout *>(TheGameLogic)->m_gameMode == 4)
        return;
    UnsignedInt crc = TheGameLogic->getCRC(0);
    if ((reinterpret_cast<GameLogicBFMERetailLayout *>(TheGameLogic)->m_gameMode == 1 ||
         reinterpret_cast<GameLogicBFMERetailLayout *>(TheGameLogic)->m_gameMode == 5) &&
        m_crcBeforeClientUpdate != crc)
    {
        if (TheInGameUI)
            TheInGameUI->message(L"GameLogic changed outside of GameLogic::update()!");
        AsciiString filename;
        AsciiString report;
        IPEnumeration enumeration;
        filename.format("CLIENT_DESYNC_%s.txt", enumeration.getMachineName().str());
        DesyncFile *file = fopen(filename.str(), "a");
        DesyncSystemTime time;
        GetLocalTime(&time);
        report.format("Desync detected on frame %d on %u-%u-%u %u:%u:%u\n\n",
            TheGameLogic->getFrame(),
            time.month, time.day, time.year, time.hour, time.minute, time.second);
        fwrite(report.str(), 1, report.getLength(), file);
        fclose(file);
    }
}
