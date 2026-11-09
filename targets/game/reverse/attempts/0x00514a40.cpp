// ?rva00514A40@AptInGameChat@@QAEHHPAX0@Z
// partial score=0.9793 date=2026-11-09
// ?rva00514A40@AptInGameChat@@QAEHHPAX0@Z
// partial score=0.979 date=2026-11-07 (13 non-reloc diffs; prior bank 19)
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x00514A40, 628 bytes: slot 2 of the AptInGameChat vtable
// (0x01105384, through ILT 0x00023BE6), installed by the matched
// constructor at 0x005160E0.  The chat screen's window-message handler:
// after the default handler, mouse-position messages over the friends list
// count hover repeats and, past ten on the status column, show the
// friend-status tooltip; the 0x4030 tail (also reached by the hover case)
// sends on a zero payload from the chat entry or refreshes the buttons,
// which 0x4014 does too.  Declarations follow the matched sibling
// BfmeAptScreenInGameChatRefreshFriendsList.cpp; the member name and the
// +0x298..+0x2A0 hover fields are unrecorded and keep their addresses.
// 2026-11-07: the UnicodeString copy constructor is an inline BODY call of
// the private StringBase<unsigned short> copy constructor (the form of the
// matched sibling BfmeAptScreenInGameChatSelectedFriends.cpp), not a
// mem-initializer forwarder: that gives retail's `mov ecx,esp` before the
// saved-esp store at the setCursorTooltip argument (+0x1F4).

extern const char g_bfmeEmptyUnicode[];

template <typename T> struct StringInlineData { int m_refCount; int m_length; T m_text[1]; };
template <typename T> class StringBase
{
	friend class UnicodeString;
private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	StringInlineData<T> *m_data;
};
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( other ); }
	~UnicodeString() {}
	void __cdecl format( UnicodeString format, ... );
	const unsigned short *str() const { return m_data ? m_data->m_text : (const unsigned short *)g_bfmeEmptyUnicode; }
};
extern "C" void _ReadWriteBarrier( void );
extern "C" void _WriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier, _WriteBarrier )
class GameWindow;

int GadgetListBoxGetEntryBasedOnXY( GameWindow *listbox, int x, int y, int &row, int &column );
void *GadgetListBoxGetItemData( GameWindow *listbox, int row, int column );

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};
extern GameTextInterface *TheGameText;

struct RGBColor;
class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, int delay, const RGBColor *color, float width );
};
struct Rva005A63D0Mouse;
extern Rva005A63D0Mouse *TheMouse;

class BfmeMsgHandler
{
public:
	int defaultHandler( int msg, void *mData1, void *mData2 );
};

class AptInGameChat
{
public:
	int rva00514A40( int msg, void *mData1, void *mData2 );
	void Rva00006F4BUpdateButtons();
	int rva00512890( int profileID, UnicodeString &result );
	void _bfme_send( const char *text );

private:
	unsigned char m_unmodelled000[0x260];
	GameWindow *m_chatEntry;
	GameWindow *m_friendsList;
	unsigned char m_unmodelled268[0x30];
	int m_rva298;
	int m_rva29C;
	int m_rva2A0;
};

// ?rva00514A40@AptInGameChat@@QAEHHPAX0@Z
int AptInGameChat::rva00514A40( int msg, void *mData1, void *mData2 )
{
	if( ((BfmeMsgHandler *)this)->defaultHandler( msg, mData1, mData2 ) == 1 )
		return 1;

	switch( msg )
	{
		case 0x18:
			if( (GameWindow *)mData1 == m_friendsList )
			{
				int x = (unsigned int)mData2 & 0xffff;
				int y = (unsigned int)mData2 >> 16;
				if( x == m_rva298 && y == m_rva29C )
					++m_rva2A0;
				else
					m_rva2A0 = 0;
				int row, column;
				GadgetListBoxGetEntryBasedOnXY( (GameWindow *)mData1, x, y, row, column );
				if( m_rva2A0 >= 10 && column == 2 )
				{
					int profileID = (int)GadgetListBoxGetItemData( (GameWindow *)mData1, row, 0 );
					UnicodeString name;
					int status = rva00512890( profileID, name );
					UnicodeString tooltip;
					if( status == 2 )
					{
						tooltip.format( TheGameText->fetch( "APT:BuddyIsOfflineToolTip" ), name.str() );
						_WriteBarrier();
					}
					else if( status == 1 )
					{
						tooltip.format( TheGameText->fetch( "APT:BuddyIsOnlineToolTip" ), name.str() );
						_ReadWriteBarrier();
					}
					else if( status == 4 )
					{
						tooltip.format( TheGameText->fetch( "APT:BuddyRequestToolTip" ), name.str() );
						_ReadWriteBarrier();
					}
					else
					{
						tooltip.format( TheGameText->fetch( "APT:Null" ) );
						_ReadWriteBarrier();
					}
					((Mouse *)TheMouse)->setCursorTooltip( tooltip, -1, 0, 1.0f );
				}
				m_rva29C = y;
				m_rva298 = x;
			}
			// fall through
		case 0x4030:
			if( mData2 == 0 )
			{
				if( (GameWindow *)mData1 == m_chatEntry )
					_bfme_send( 0 );
			}
			else
				Rva00006F4BUpdateButtons();
			return 1;

		case 0x4014:
			Rva00006F4BUpdateButtons();
			return 1;
	}
	return 0;
}
