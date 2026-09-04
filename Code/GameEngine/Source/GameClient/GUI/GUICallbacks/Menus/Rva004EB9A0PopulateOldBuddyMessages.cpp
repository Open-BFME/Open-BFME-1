// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include <list>

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class AsciiString
{
public:
	~AsciiString();
private:
	void *m_data;
};

class UnicodeString
{
public:
	~UnicodeString();
private:
	void *m_data;
};

class BuddyMessage
{
public:
	BuddyMessage(const BuddyMessage &);
	__forceinline ~BuddyMessage() {}

	unsigned int m_timestamp;
	unsigned int m_senderID;
	AsciiString m_senderNick;
	unsigned int m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};

typedef _STL::list<BuddyMessage> BuddyMessageList;

class BfmeGameSpyInfoView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual BuddyMessageList *getBuddyMessages() = 0;
};

void insertChat(BuddyMessage message);

void PopulateOldBuddyMessages(void)
{
	BuddyMessageList *messages =
		((BfmeGameSpyInfoView *)TheGameSpyInfo)->getBuddyMessages();
	for (BuddyMessageList::iterator mIt = messages->begin();
		mIt != messages->end(); ++mIt)
	{
		BuddyMessage message = *mIt;
		insertChat(message);
	}
}
