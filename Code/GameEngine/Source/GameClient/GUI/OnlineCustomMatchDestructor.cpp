// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch destructor, retail 0x00538CE0, 251 bytes.
// Named by PrimarySort/SecondarySort string xrefs, ctor 0x00545310 /
// S4Guarded0055BCA0, and vtable 0x01107484.

#include "../../../../../reference/shims/stringinline/StringInline.h"

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x38 ];
};

class BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSecondary() {}
};

class BfmeCustomMatchMember40
{
public:
	~BfmeCustomMatchMember40();

private:
	unsigned char m_data[ 0x134 ];
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void unused04();
	virtual void unused08();
	virtual bool write();
	void setInt( AsciiString key, int value );

private:
	unsigned char m_data[ 0x6C ];
};

class CustomMatchPreferences : public UserPreferences
{
public:
	virtual ~CustomMatchPreferences();
};

class GameSpyInfo
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
};

extern GameSpyInfo *TheGameSpyInfo;
extern class BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

class BfmeAptScreenOnlineCustomMatch : public BfmeAptGameWindow, public BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenOnlineCustomMatch();

private:
	BfmeCustomMatchMember40 m_mid;
	CustomMatchPreferences m_prefs;
	AsciiString m_unusedName;
	int m_primarySort;
	int m_secondarySort;
};

BfmeAptScreenOnlineCustomMatch::~BfmeAptScreenOnlineCustomMatch()
{
	if( this == TheBfmeOnlineCustomMatch )
	{
		m_prefs.setInt( AsciiString( "PrimarySort" ), m_primarySort );
		m_prefs.setInt( AsciiString( "SecondarySort" ), m_secondarySort );
		m_prefs.write();
		GameSpyInfo *info = TheGameSpyInfo;
		TheBfmeOnlineCustomMatch = 0;
		if( info )
			info->s08();
	}
}
