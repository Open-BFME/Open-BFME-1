// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <string>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	~PSPlayerStats();

private:
	char m_data[0x1C4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSRequest
{
public:
	~PSRequest();

private:
	int m_requestType;
	PSPlayerStats m_player;
	std::string m_cdkey;
	std::string m_nick;
	std::string m_password;
	std::string m_email;
	int m_addDiscon;
	int m_addDesync;
	int m_lastHouse;
	std::string m_results;
};

PSRequest::~PSRequest()
{
}
