// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0052DC00 adds one BuddyInfo name and profile to the OnlineChat
// friends list. The caller at 0x00533EA0 proves the four-argument ABI.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void translate( const AsciiString &source );
};

class GameWindow;

int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite );
void bfmeCall926A( void *listbox, void *row, void *data, int unused );

// Address-derived identity for the retail 0x0052DC00 row-adder body.
int Rva0052DC00AddFriend( GameWindow *listbox, int profileID,
	const AsciiString *name, int color )
{
	UnicodeString displayName;
	displayName.translate( *name );
	int row = GadgetListBoxAddEntryText( listbox, displayName, color, -1, 2,
		true );
	bfmeCall926A( listbox, (void *)profileID, (void *)row, 0 );
	return row;
}
