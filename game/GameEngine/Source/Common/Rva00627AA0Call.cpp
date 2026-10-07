// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BuddyRequest
{
	int m_value;
	char m_pad[0x2B4];
};

struct Rva00627AA0Obj
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(BuddyRequest *arg);
};

class GameSpyBuddyMessageQueueInterface;
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

void buddyTryReconnect()
{
	BuddyRequest req;
	req.m_value = 1;
	reinterpret_cast<Rva00627AA0Obj *>(TheGameSpyBuddyMessageQueue)->slot6(&req);
}
