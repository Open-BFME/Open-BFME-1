// cl: /DNDEBUG /MD /EHsc /Ireference/shims/languagefilter /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include "Common/UnicodeString.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

struct LANPlayerAddress
{
	UnsignedInt m_IP;
	UnsignedInt m_bfmeLayoutPad;
};

class GameSlot
{
public:
	virtual void reset(void) = 0;
	Bool isHuman(void) const;
	UnicodeString getName(void) const;

protected:
	SlotState m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	UnicodeString m_name;
	UnsignedInt m_bfmeNamePad;
	LANPlayerAddress m_address;
	UnsignedInt m_lastFrameInGame;
	Bool m_disconnected;
	UnsignedInt m_bfmeLayoutPad;
};

class LANPlayer
{
public:
	void setLastHeard(UnsignedInt lastHeard) { m_lastHeard = lastHeard; }
	void setNext(LANPlayer *next) { m_next = next; }

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	LANPlayerAddress m_address;
};

class LANGameSlot : public GameSlot
{
public:
	LANPlayer *getUser(void);
	UnsignedInt getLastHeard(void) const { return m_lastHeard; }

private:
	LANPlayer m_user;
	UnsignedInt m_serial;
	UnsignedInt m_lastHeard;
};

LANPlayer *LANGameSlot::getUser(void)
{
	if (isHuman())
	{
		m_user.m_address = m_address;
		m_user.setLastHeard(getLastHeard());
		m_user.m_name = getName();
		m_user.setNext(NULL);
		return &m_user;
	}
	return NULL;
}
