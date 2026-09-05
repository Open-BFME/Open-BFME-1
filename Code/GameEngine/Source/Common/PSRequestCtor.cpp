// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// PSRequest default constructor. Layout matches the landed copy ctor at
// 0x006588B0 and the 0x210 deque stride: requestType, PSPlayerStats at +4,
// four strings, two bools, lastHouse, one extra Int, results string.

#include <string>

class PSPlayerStats
{
public:
	PSPlayerStats();
	~PSPlayerStats();
	void reset();

private:
	char m_data[0x1C4];
};

class PSRequest
{
public:
	PSRequest();

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

// ??0PSRequest@@QAE@XZ
PSRequest::PSRequest()
{
	m_player.reset();
	m_requestType = 0;
	m_addDiscon = m_addDesync = false;
	m_lastHouse = -1;
}
