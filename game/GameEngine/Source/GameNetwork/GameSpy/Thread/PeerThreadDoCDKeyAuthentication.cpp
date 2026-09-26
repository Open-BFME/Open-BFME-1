// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/nat /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"

#include "Common/Registry.h"
#include "Common/StackDump.h"
#include "Common/UserPreferences.h"
#include "Common/Version.h"
#include "GameNetwork/IPEnumeration.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/ThreadUtils.h"

#include "strtok_r.h"
#include "mutex.h"
#include "thread.h"

#include "Common/MiniLog.h"

class PSRequest
{
public:
	PSRequest();
	~PSRequest();

	enum
	{
		PSREQUEST_READPLAYERSTATS,
		PSREQUEST_UPDATEPLAYERSTATS,
		PSREQUEST_UPDATEPLAYERLOCALE,
		PSREQUEST_READCDKEYSTATS,
		PSREQUEST_SENDGAMERESTOGAMESPY,
		PSREQUEST_MAX
	};

	int requestType;
	char player[0x1c4];
	std::string cdkey;
	std::string nick;
	std::string password;
	std::string email;
	Bool addDiscon;
	Bool addDesync;
	Int lastHouse;
	Int extra;
	std::string results;
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual void addRequest( const PSRequest& req ) = 0;
};

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

static bool hasText(const AsciiString &s)
{
	const char *data = *(const char *const *)&s;
	return data != 0 && *(const unsigned short *)(data + 4) != 0;
}

static void AuthenticateCDKeyCallback(
	PEER peer,
	int result,
	const char *message,
	void *param
)
{
	DEBUG_LOG(("CD Key Result: %s (%d) %X\n", message, result, param));
	SerialAuthResult *val = (SerialAuthResult *)param;
	if (val)
	{
		if (result >= 1)
			*val = SERIAL_OK;
		else
			*val = SERIAL_AUTHFAILED;
	}
}

static SerialAuthResult doCDKeyAuthentication( PEER peer )
{
	SerialAuthResult retval = SERIAL_NONEXISTENT;
	if (!peer)
		return retval;

	AsciiString s = "";
	if (GetStringFromRegistry("\\ergc", "", s) && hasText(s))
	{
		peerAuthenticateCDKey(peer, s.str(), AuthenticateCDKeyCallback, &retval, PEERTrue);
	}

	if (retval == SERIAL_OK)
	{
		PSRequest req;
		req.requestType = PSRequest::PSREQUEST_READCDKEYSTATS;
		req.cdkey = s.str();
		TheGameSpyPSMessageQueue->addRequest(req);
	}

	return retval;
}

extern "C" void PeerThreadDoCDKeyAuthenticationAnchor( PEER peer )
{
	doCDKeyAuthentication(peer);
}
