// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// GameSpyPSMessageQueue::setEmail / setNick / setPassword.
// ZH GeneralsMD PersistentStorageThread.cpp inlines these as
// m_email = email (by-value STLport string). Retail adds 0x6C / 0x78 / 0x84
// then inlines operator=; setPassword is 3 bytes longer because 0x84 is imm32.

#include <string>

class GameSpyPSMessageQueue
{
public:
	void setEmail(_STL::string email);
	void setNick(_STL::string nick);
	void setPassword(_STL::string password);

private:
	unsigned char m_prefix[0x6C];
	_STL::string m_email;
	_STL::string m_nick;
	_STL::string m_password;
};

void GameSpyPSMessageQueue::setEmail(_STL::string email)
{
	m_email = email;
}

void GameSpyPSMessageQueue::setNick(_STL::string nick)
{
	m_nick = nick;
}
