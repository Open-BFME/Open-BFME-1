// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0052DB10, 136 bytes. Read column 2 of one listbox row into the
// caller's UnicodeString and answer whether the row existed. The two callees
// name the shape outright: GadgetListBoxGetNumEntries, matched at 0x004B77C0,
// bounds the row, and GadgetListBoxGetText, matched at 0x004BBC70, returns the
// text by value. The result reaches the out parameter through the matched
// StringBase<unsigned short> set at 0x00888530 and the temporary is released
// through 0x008881D0.
//
// No caller names the body, so the name keeps the address.

typedef int Int;
typedef bool Bool;

class GameWindow;

// upstream layout: game/Libraries/Source/WWVegas/WWLib/string_base.h
template <class T> class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	~StringBase() { releaseBuffer(); }

	void set( const StringBase &other );

	void *m_data;

private:
	void releaseBuffer();
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	~UnicodeString() {}
};

Int GadgetListBoxGetNumEntries( GameWindow *window );
UnicodeString GadgetListBoxGetText( GameWindow *window, Int row, Int column );

// ?Rva0052DB10ListboxColumnText@@YA_NPAVGameWindow@@HPAVUnicodeString@@@Z
Bool Rva0052DB10ListboxColumnText( GameWindow *listbox, Int row, UnicodeString *text )
{
	Bool found = false;
	Int entries = GadgetListBoxGetNumEntries( listbox );

	if( row >= 0 && row < entries )
	{
		text->set( GadgetListBoxGetText( listbox, row, 2 ) );
		found = true;
	}

	return found;
}
