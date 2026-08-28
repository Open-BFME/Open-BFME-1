// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: isolated port of PopupPlayerInfo.cpp's static messageBoxYes() for
// retail 0x004D9010. The shared PopupPlayerInfo.cpp TU already reproduces every
// byte of this function except three immediates, and both come from BFME layout
// drift the vanilla Zero Hour headers do not carry: the frame is 0x2B8 rather
// than 0x208 because BFME's BuddyRequest is that much larger (see
// reference/shims/buddythread), and setLocalProfileID sits at vtable slot 0x6C
// rather than 0x50 because BFME's GameSpyInfoInterface carries seven extra
// virtuals ahead of it (see reference/shims/peerdefs). Rather than change the
// include path of the shared, already-matched PopupPlayerInfo.cpp, this TU
// replicates just the pieces messageBoxYes needs.

// Only the SIZE matters for codegen here: retail allocates the whole record on
// the stack and writes nothing but the type word.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_DELETEACCT = 10,
	};

	int buddyRequestType;
	unsigned char m_rest[0x2B8 - 4];
};

// Stand-ins for the two interfaces: only the slot COUNT ahead of the called
// method matters for codegen, not the real signatures. The class names are the
// real ones so the globals below decorate to the symbols every other reference
// uses, and the build cross-checks their addresses.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void addRequest( const BuddyRequest& req );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfoInterface
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual void _pad07();
	virtual void _pad08();
	virtual void _pad09();
	virtual void _pad10();
	virtual void _pad11();
	virtual void _pad12();
	virtual void _pad13();
	virtual void _pad14();
	virtual void _pad15();
	virtual void _pad16();
	virtual void _pad17();
	virtual void _pad18();
	virtual void _pad19();
	virtual void _pad20();
	virtual void _pad21();
	virtual void _pad22();
	virtual void _pad23();
	virtual void _pad24();
	virtual void _pad25();
	virtual void _pad26();
	virtual void setLocalProfileID( int profileID );
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameSpyInfoInterface *TheGameSpyInfo;

// ?messageBoxYes@@YAXXZ
void messageBoxYes( void )
{
	BuddyRequest breq;
	breq.buddyRequestType = BuddyRequest::BUDDYREQUEST_DELETEACCT;
	TheGameSpyBuddyMessageQueue->addRequest( breq );
	TheGameSpyInfo->setLocalProfileID(0);
}
