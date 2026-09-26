// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME QRServerKeyCallback at RVA 0x0064DA00. Thread_Function at 0x64FB90
// stores this callback at PeerCallbacks.qrServerKey (+0x50) at 0x64FCC0.
// It is a four-argument cdecl callback; the executable ends with plain ret.
// The complete COFF symbol is 1721 bytes: 1585 executable + 3-byte alignment,
// 18 jump destinations and 61 dispatch-index bytes. Both table pointers are
// used only by this callback and every destination is inside its code.
//
// PeerThread.cpp supplies the switch and debug-value reporting algorithm.
// BFME's by-value AsciiString::format and eight-byte StringBase header are
// required here; the ZH const-char format overload changes argument lifetime.
// The real C qr2 APIs do not throw under EHsc. Getter return types preserve
// password/observer bytes, ushort port and full CRC/count widths. Field +0xBC
// has no independently recovered member spelling, so its accessor is named
// by offset. Existing by-value string accessors are kept under proven names.
// Registration literals prove PW=54 and OBS=55. The field order and hosting
// setters independently identify password at+0xAD and observers at+0x13C;
// the old bank had both semantic labels swapped despite preserving the bytes.

#include <string>
#include <string.h>
typedef bool Bool;
template<class T> struct StringData { int ref_count; unsigned short length, capacity; T text[1]; };
template<class T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringData<T> *data;
    StringBase():data(0) {}
    StringBase(const T*);
    StringBase(const StringBase&);
    ~StringBase();
    void set(const StringBase&);
    void set(const T *, int);
};
class AsciiString : private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char *p):StringBase<char>(p) {}
    AsciiString(const AsciiString &p):StringBase<char>(p) {}
    ~AsciiString() {}
    const char *str() const { return data ? data->text : ""; }
    void __cdecl format(AsciiString, ...);
    AsciiString &operator=(const char *s) { set(s, s ? strlen(s) : 0); return *this; }
    AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const unsigned short *p):StringBase<unsigned short>(p) {}
    UnicodeString(const UnicodeString &p):StringBase<unsigned short>(p) {}
    ~UnicodeString() {}
    const unsigned short *str() const { return data ? data->text : (const unsigned short *)L""; }
    void __cdecl format(UnicodeString, ...);
    void translate(const AsciiString&);
    UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
};
typedef void *PEER;
typedef void *qr2_buffer_t;

extern "C" void qr2_buffer_addA(qr2_buffer_t buffer, const char *value);
#define qr2_buffer_add qr2_buffer_addA
extern "C" void qr2_buffer_add_int(qr2_buffer_t buffer, int value);

typedef unsigned short WideChar;
std::string WideCharStringToMultiByte(const WideChar *orig);

class Rva00647720Host
{
public:
	std::string copyStringAtB0(void);
};

class Rva00647750Host
{
public:
	std::string copyStringAtC0(void);
};

class Rva00647780Host
{
public:
	std::wstring copyStringAt218(void);
};

class Rva006477B0Host
{
public:
	std::string copyStringAt14C(void);
};

class Rva006477E0Host
{
public:
	std::string copyStringAt140(void);
};

class PeerThreadClass
{
public:
	Bool isHosting(void)
	{
		return *reinterpret_cast<const Bool *>(reinterpret_cast<const char *>(this) + 0xac);
	}

	unsigned int gameVersion() { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x138); }
unsigned int exeCRC() { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x12c); }
unsigned int iniCRC() { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x130); }
unsigned int cmdCRC() { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x134); }
bool hasPassword() { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this) + 0xad); }
bool allowObservers() { return *reinterpret_cast<const bool *>(reinterpret_cast<const char *>(this) + 0x13c); }
unsigned short ladderPort() { return *reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(this) + 0x158); }
int getNumPlayers() { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x1fc); }
int getMaxPlayers() { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x200); }
int getNumObservers() { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x204); }
int valueAtBC() { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0xbc); }
	void stopHostingAlready(PEER peer);
	std::string getPlayerName(int index);
};

enum
{
	HOSTNAME_KEY = 1,
	GAMENAME_KEY = 2,
	GAMEVER_KEY = 3,
	MAPNAME_KEY = 5,
	GAMEMODE_KEY = 11,
	TEAMPLAY_KEY = 12,
	EXECRC_KEY = 51,
	INICRC_KEY = 52,
	CMDCRC_KEY = 53,
	PW_KEY = 54,
	OBS_KEY = 55,
	LADIP_KEY = 56,
	LADPORT_KEY = 57,
	PINGSTR_KEY = 58,
	NUMPLAYER_KEY = 59,
	MAXPLAYER_KEY = 60,
	NUMOBS_KEY = 61
};

#define ADD(x) { qr2_buffer_add(buffer, x); val = x; }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); val.format("%d", x); }


static void QRServerKeyCallback
(
	PEER peer,
	int key,
	qr2_buffer_t buffer,
	void *param
)
{
	PeerThreadClass *thread = (PeerThreadClass *)param;
	if (!thread)
		return;

	if (!thread->isHosting())
		thread->stopHostingAlready(peer);

	AsciiString val = "";

	switch (key)
	{
	case HOSTNAME_KEY:
		ADD(thread->getPlayerName(0).c_str());
		break;
	case GAMEVER_KEY:
		ADDINT(thread->gameVersion());
		break;
	case EXECRC_KEY:
		ADDINT(thread->exeCRC());
		break;
	case INICRC_KEY:
		ADDINT(thread->iniCRC());
		break;
	case CMDCRC_KEY:
		ADDINT(thread->cmdCRC());
		break;
	case GAMENAME_KEY:
		{
			std::string name = thread->getPlayerName(0);
			name.append(" ");
			name.append(WideCharStringToMultiByte(
				((Rva00647780Host *)thread)->copyStringAt218().c_str()));
			ADD(name.c_str());
		}
		break;
	case MAPNAME_KEY:
		ADD(((Rva00647720Host *)thread)->copyStringAtB0().c_str());
		break;
	case PW_KEY:
		ADDINT(thread->hasPassword());
		break;
	case OBS_KEY:
		ADDINT(thread->allowObservers());
		break;
	case LADIP_KEY:
		ADD(((Rva006477B0Host *)thread)->copyStringAt14C().c_str());
		break;
	case LADPORT_KEY:
		ADDINT(thread->ladderPort());
		break;
	case PINGSTR_KEY:
		ADD(((Rva006477E0Host *)thread)->copyStringAt140().c_str());
		break;
	case NUMPLAYER_KEY:
		ADDINT(thread->getNumPlayers());
		break;
	case MAXPLAYER_KEY:
		ADDINT(thread->getMaxPlayers());
		break;
	case NUMOBS_KEY:
		ADDINT(thread->getNumObservers());
		break;
	case TEAMPLAY_KEY:
		// Key 12 is proven by the retail dispatch table; its field has no
		// recovered semantic name, so retain the honest +0xBC ABI only.
		ADDINT(thread->valueAtBC());
		break;
	case GAMEMODE_KEY:
		ADD(((Rva00647750Host *)thread)->copyStringAtC0().c_str());
		break;
	default:
		ADD("");
		break;
	}
}

#undef ADD
#undef ADDINT

// Retain the registered static callback in this focused TU; this pointer
// is an object-file anchor, not a separate retail claim.
typedef void (*QRServerKeyCallbackType)(PEER, int, qr2_buffer_t, void *);
QRServerKeyCallbackType forceQRServerKeyCallback =
	QRServerKeyCallback;
