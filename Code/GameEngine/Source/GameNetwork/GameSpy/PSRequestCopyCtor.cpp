// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// PSRequest copy constructor. Layout matches the 0x210 deque stride and
// the sibling destructor at 0x000A5490: requestType, PSPlayerStats at +4,
// four strings, two bools, lastHouse, one extra Int, results string.

#include <string>

class PSPlayerStats
{
public:
	PSPlayerStats(const PSPlayerStats &other);
	~PSPlayerStats();

private:
	char m_data[0x1C4];
};

class PSRequest
{
public:
	PSRequest(const PSRequest &other);

private:
	int m_requestType;
	PSPlayerStats m_player;
	_STL::string m_cdkey;
	_STL::string m_nick;
	_STL::string m_password;
	_STL::string m_email;
	bool m_addDiscon;
	bool m_addDesync;
	int m_lastHouse;
	int m_extra;
	_STL::string m_results;
};

typedef char PSRequestSizeCheck[sizeof(PSRequest) == 0x210 ? 1 : -1];

// ??0PSRequest@@QAE@ABV0@@Z
PSRequest::PSRequest(const PSRequest &other)
	: m_requestType(other.m_requestType)
	, m_player(other.m_player)
	, m_cdkey(other.m_cdkey)
	, m_nick(other.m_nick)
	, m_password(other.m_password)
	, m_email(other.m_email)
	, m_addDiscon(other.m_addDiscon)
	, m_addDesync(other.m_addDesync)
	, m_lastHouse(other.m_lastHouse)
	, m_extra(other.m_extra)
	, m_results(other.m_results)
{
}
