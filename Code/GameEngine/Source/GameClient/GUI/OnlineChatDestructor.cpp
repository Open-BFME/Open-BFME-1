// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineChat destructor, retail 0x0052D7C0, 232 bytes.
// Named by AptOnlineChat::InitGadgets string xref and vtable 0x01106F58
// (installed by ctor 0x00536DC0 / S4Guarded0055BB20).

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x54 ];
};

class InGameChatSlot
{
public:
	~InGameChatSlot();

private:
	unsigned char m_data[ 0x10 ];
};

void _bfme_closeAptScreen( const AsciiString &name );

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
};

extern GameSpyInfo *TheGameSpyInfo;
extern class BfmeAptScreenOnlineChat *TheBfmeOnlineChat;

class BfmeAptScreenOnlineChat : public BfmeAptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineChat();

private:
	InGameChatSlot m_slot0;
	InGameChatSlot m_slot1;
	InGameChatSlot m_slot2;
	InGameChatSlot m_slot3;
	unsigned char m_mid[ 0x20 ];
	AsciiString m_unusedName;
};

BfmeAptScreenOnlineChat::~BfmeAptScreenOnlineChat()
{
	if( this == TheBfmeOnlineChat )
	{
		{
			AsciiString callback( "AptOnlineChat::InitGadgets" );
			_bfme_closeAptScreen( callback );
		}
		TheBfmeOnlineChat = 0;
		if( TheGameSpyInfo )
			TheGameSpyInfo->s07();
	}
}
