// cl: /DNDEBUG /MD /EHsc
// readable body of ?messageCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPRecvBuddyMessageArg@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp
// readable body of ?requestCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPRecvBuddyRequestArg@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp
// readable body of ?statusCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPRecvBuddyStatusArg@@@Z: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp

#include <string.h>
#include <wchar.h>

namespace _STL
{
template <class T> struct char_traits {};
template <class T> class allocator {};

template <bool threads, int instance> class __node_alloc
{
public:
	static void _M_deallocate(void *memory, unsigned int bytes);
};

template <class Character, class Traits, class Allocator> class basic_string
{
public:
	~basic_string()
	{
		if (m_start)
		{
			const unsigned int bytes =
				(unsigned int)(m_storageEnd - m_start) * sizeof(Character);
			if (bytes > 128)
				::operator delete(m_start);
			else
				__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

	const Character *c_str() const { return m_start; }

private:
	Character *m_start;
	Character *m_end;
	Character *m_storageEnd;
};

typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;
}

typedef int GPProfile;
typedef int GPEnum;

class GPConnection;

struct GPRecvBuddyRequestArg
{
	GPProfile profile;
	int date;
	char reason[1];
};

struct GPRecvBuddyMessageArg
{
	GPProfile profile;
	unsigned int date;
	char *message;
};

struct GPRecvBuddyStatusArg
{
	GPProfile profile;
	int reserved;
	int index;
};

struct GPBuddyStatus
{
	GPProfile profile;
	int status;
	char statusString[256];
	char locationString[256];
	char reservedTail[8];
};

struct GPGetInfoResponseArg
{
	GPProfile profile;
	char *nick;
	char *email;
	char *countrycode;
};

typedef void (*GPCallback)(GPConnection *, void *, void *);

void gpGetInfo(GPConnection *connection, GPProfile profile, GPEnum checkCache,
	GPEnum blocking, GPCallback callback, void *param);
void gpGetBuddyStatus(GPConnection *connection, int index, GPBuddyStatus *status);
_STL::wstring MultiByteToWideCharSingleLine(const char *text);

void getInfoResponseForRequest(GPConnection *, GPGetInfoResponseArg *, void *);
void getNickForMessage(GPConnection *, GPGetInfoResponseArg *, void *);
void getInfoResponseForStatus(GPConnection *, GPGetInfoResponseArg *, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
struct BuddyResponse
{
	enum ResponseType
	{
		BUDDYRESPONSE_LOGIN,
		BUDDYRESPONSE_DISCONNECT,
		BUDDYRESPONSE_MESSAGE,
		BUDDYRESPONSE_REQUEST
	};

	ResponseType buddyResponseType;
	GPProfile profile;
	int result;
	union
	{
		struct
		{
			unsigned int date;
			char nick[32];
			wchar_t text[128];
		} message;

		struct
		{
			char identity[0x56];
			wchar_t text[1025];
		} request;

		struct
		{
			char nick[31];
			char email[51];
			char countrycode[3];
			char location[256];
			int status;
			char statusString[256];
		} status;
	} arg;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void addResponse(const BuddyResponse &response) = 0;
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class BuddyThreadClass
{
public:
	void messageCallback(GPConnection *connection, GPRecvBuddyMessageArg *arg);
	void requestCallback(GPConnection *connection, GPRecvBuddyRequestArg *arg);
	void statusCallback(GPConnection *connection, GPRecvBuddyStatusArg *arg);
};

void BuddyThreadClass::statusCallback(GPConnection *connection,
	GPRecvBuddyStatusArg *arg)
{
	BuddyResponse response;
	response.buddyResponseType = (BuddyResponse::ResponseType)4;

	gpGetInfo(connection, arg->profile, 1, 1,
		(GPCallback)getInfoResponseForStatus, &response);

	GPBuddyStatus status;
	gpGetBuddyStatus(connection, arg->index, &status);
	strcpy(response.arg.status.location, status.locationString);
	strcpy(response.arg.status.statusString, status.statusString);
	response.arg.status.status = status.status;

	TheGameSpyBuddyMessageQueue->addResponse(response);
}

void BuddyThreadClass::messageCallback(GPConnection *connection,
	GPRecvBuddyMessageArg *arg)
{
	BuddyResponse response;
	response.buddyResponseType = BuddyResponse::BUDDYRESPONSE_MESSAGE;
	response.profile = arg->profile;

	gpGetInfo(connection, arg->profile, 1, 1,
		(GPCallback)getNickForMessage, &response);

	_STL::wstring text = MultiByteToWideCharSingleLine(arg->message);
	wcsncpy(response.arg.message.text, text.c_str(), 128);
	response.arg.message.text[127] = 0;
	response.arg.message.date = arg->date;

	TheGameSpyBuddyMessageQueue->addResponse(response);
}

void BuddyThreadClass::requestCallback(GPConnection *connection,
	GPRecvBuddyRequestArg *arg)
{
	BuddyResponse response;
	response.buddyResponseType = BuddyResponse::BUDDYRESPONSE_REQUEST;
	response.profile = arg->profile;

	gpGetInfo(connection, arg->profile, 1, 1,
		(GPCallback)getInfoResponseForRequest, &response);

	_STL::wstring text = MultiByteToWideCharSingleLine(arg->reason);
	wcsncpy(response.arg.request.text, text.c_str(), 1025);
	response.arg.request.text[1024] = 0;

	TheGameSpyBuddyMessageQueue->addResponse(response);
}
