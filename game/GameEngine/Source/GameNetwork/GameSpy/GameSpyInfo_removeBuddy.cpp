// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/buddythread /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// The retail slot at 0x00637BD0 removes a buddy or denies a buddy request.

#include <map>

typedef int Int;
typedef bool Bool;

class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_DELBUDDY = 6,
		BUDDYREQUEST_DENYADD = 8
	};

	int buddyRequestType;
	union
	{
		struct
		{
			Int id;
		} profile;
		char body[0x2B4];
	} arg;
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual Bool isThreadRunning() = 0;
	virtual Bool isConnected() = 0;
	virtual Bool isConnecting() = 0;
	virtual void addRequest(const BuddyRequest &request) = 0;
};

struct Gen_t_004ee060_p12cd
{
	int data[3];
};

typedef std::map<Int, Gen_t_004ee060_p12cd> BuddyInfoMap;

class BfmeGameSpyInfoView
{
public:
	virtual ~BfmeGameSpyInfoView() {}
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual BuddyInfoMap *getBuddyRequestMap() = 0;
	virtual void slot14() = 0;
	virtual Bool isBuddy(Int profileID) = 0;
};

extern BfmeGameSpyInfoView *TheGameSpyInfo;
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class GameSpyInfo
{
public:
	void removeBuddy(Int profileID);
};

// ?removeBuddy@GameSpyInfo@@QAEXH@Z
void GameSpyInfo::removeBuddy(Int profileID)
{
	BuddyRequest request;
	if (profileID <= 0)
		return;

	Bool isBuddy = TheGameSpyInfo->isBuddy(profileID);
	if (isBuddy)
	{
		request.arg.profile.id = profileID;
		request.buddyRequestType = BuddyRequest::BUDDYREQUEST_DELBUDDY;
		TheGameSpyBuddyMessageQueue->addRequest(request);
	}
	else
	{
		request.arg.profile.id = profileID;
		request.buddyRequestType = BuddyRequest::BUDDYREQUEST_DENYADD;
		TheGameSpyBuddyMessageQueue->addRequest(request);
		BuddyInfoMap *requests = TheGameSpyInfo->getBuddyRequestMap();
		requests->erase(profileID);
	}

	BuddyInfoMap *buddies = isBuddy ? TheGameSpyInfo->getBuddyMap() : TheGameSpyInfo->getBuddyRequestMap();
	buddies->erase(profileID);
}
