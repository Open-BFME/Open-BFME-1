// ?Rva0064DA00PeerServerKeyCallback@@YAXPAXH00@Z
// partial score=0.65 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DDEBUG_LOGGING /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Full real-C++ attempt for the registered PeerCallbacks.qrServerKey body.
//
// Retail boundary: [0x0064DA00, 0x0064E031), 1585 bytes, ret 4.  The old
// PeerThreadClass::Thread_Function stores this callback at PeerCallbacks
// offset 0x50 (retail 0x0064FCC0), so the address-derived name below claims
// the callback body and not the unrelated callerless 0x006359C0 body.
// The retail dispatch table and registration at that caller prove the old
// key ABI: keys 0x33..0x3a are exeCRC, iniCRC, cmdCRC, obs, pw, ladIP,
// ladPort and pings; the direct fields and existing accessor callees below
// are kept at their retail offsets rather than borrowing the newer source
// layout in PeerThread.cpp.

#include "PreRTS.h"

typedef void *PEER;
typedef void *qr2_buffer_t;

void qr2_buffer_add(qr2_buffer_t buffer, const char *value);
void qr2_buffer_add_int(qr2_buffer_t buffer, int value);

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
	OBS_KEY = 54,
	PW_KEY = 55,
	LADIP_KEY = 56,
	LADPORT_KEY = 57,
	PINGSTR_KEY = 58,
	NUMPLAYER_KEY = 59,
	MAXPLAYER_KEY = 60,
	NUMOBS_KEY = 61
};

#define ADD(x) { qr2_buffer_add(buffer, x); val = x; }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); val.format("%d", x); }

// ?Rva0064DA00PeerServerKeyCallback@@YAXPAXH00@Z
static void Rva0064DA00PeerServerKeyCallback
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
	case GAMENAME_KEY:
		{
			std::string name = thread->getPlayerName(0);
			name.append(" ");
			name.append(WideCharStringToMultiByte(
				((Rva00647780Host *)thread)->copyStringAt218().c_str()));
			ADD(name.c_str());
		}
		break;
	case GAMEVER_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x138));
		break;
	case MAPNAME_KEY:
		ADD(((Rva00647720Host *)thread)->copyStringAtB0().c_str());
		break;
	case GAMEMODE_KEY:
		ADD(((Rva00647750Host *)thread)->copyStringAtC0().c_str());
		break;
	case TEAMPLAY_KEY:
		// Key 12 is proven by the retail dispatch table; its field has no
		// recovered semantic name, so retain the honest +0xBC ABI only.
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0xbc));
		break;
	case EXECRC_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x12c));
		break;
	case INICRC_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x130));
		break;
	case CMDCRC_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x134));
		break;
	case OBS_KEY:
		ADDINT(*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(thread) + 0xad));
		break;
	case PW_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x13c));
		break;
	case LADIP_KEY:
		ADD(((Rva006477B0Host *)thread)->copyStringAt14C().c_str());
		break;
	case LADPORT_KEY:
		ADDINT(*reinterpret_cast<const unsigned short *>(reinterpret_cast<const char *>(thread) + 0x158));
		break;
	case PINGSTR_KEY:
		ADD(((Rva006477E0Host *)thread)->copyStringAt140().c_str());
		break;
	case NUMPLAYER_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x1fc));
		break;
	case MAXPLAYER_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x200));
		break;
	case NUMOBS_KEY:
		ADDINT(*reinterpret_cast<const int *>(reinterpret_cast<const char *>(thread) + 0x204));
		break;
	default:
		ADD("");
		break;
	}
}

#undef ADD
#undef ADDINT

// Keep the registered static callback in this focused TU; the pointer is
// only an object-file anchor and is not a second claimed retail body.
typedef void (*Rva0064DA00PeerServerKeyCallbackType)(PEER, int, qr2_buffer_t, void *);
Rva0064DA00PeerServerKeyCallbackType forceRva0064DA00PeerServerKeyCallback =
	Rva0064DA00PeerServerKeyCallback;
