// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
//
// BfmeAptScreenOnlineCustomMatch apply-local-slot, retail 0x005392B0,
// 127 bytes. TheGameSpyGame getLocalSlotNum (+0x14) then getSlot; copy
// color (+0x0C) and playerTemplate (+0x14) into prefs at this+0x174.
// Hosts also setMap(getMap()) by value and tail-call prefs write (+0x0C).

#include "StringInline.h"

class GameSlot
{
public:
	virtual void reset();

	int getColor() const { return m_color; }
	int getPlayerTemplate() const { return m_playerTemplate; }

private:
	int m_state;
	unsigned char m_accepted;
	unsigned char m_hasMap;
	unsigned char m_muted;
	unsigned char m_pad;
	int m_color;
	int m_startPos;
	int m_playerTemplate;
};

class GameSpyStagingRoom
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	GameSlot *getSlot( int index );
	AsciiString getMap() const;
};

extern GameSpyStagingRoom *TheGameSpyGame;

class CustomMatchPreferences
{
public:
	virtual ~CustomMatchPreferences();
	virtual void unused04();
	virtual void unused08();
	virtual bool write();
	void setPreferredColor( int color );
	void setPreferredFaction( int playerTemplate );
	void setPreferredMap( AsciiString mapName );
};

class BfmeAptScreenOnlineCustomMatch
{
public:
	void applyLocalSlotToPreferences();

private:
	unsigned char m_pad[ 0x174 ];
	CustomMatchPreferences m_prefs;
};

void BfmeAptScreenOnlineCustomMatch::applyLocalSlotToPreferences()
{
	BfmeAptScreenOnlineCustomMatch *self = this;
	if( !TheGameSpyGame )
		return;
	int slotNum = TheGameSpyGame->getLocalSlotNum();
	if( slotNum < 0 )
		return;
	GameSlot *slot = TheGameSpyGame->getSlot( slotNum );
	if( !slot )
		return;
	CustomMatchPreferences &prefs = self->m_prefs;
	prefs.setPreferredColor( slot->getColor() );
	prefs.setPreferredFaction( slot->getPlayerTemplate() );
	if( TheGameSpyGame->amIHost() )
		prefs.setPreferredMap( TheGameSpyGame->getMap() );
	prefs.write();
}
