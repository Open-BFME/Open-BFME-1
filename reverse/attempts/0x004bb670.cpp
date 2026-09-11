// ?d_004bb670@@YAXXZ
// partial score=0.96 date=2026-09-11
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The BFME-only helper at 0x004BB670 splits a UnicodeString at newlines and
// appends each resulting line through GadgetListBoxAddEntryText.  The original
// source spelling is not recovered; the descriptive name records the observed
// behavior and the thunk's real callee is kept as the identity anchor.

template <typename T>
struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }

	public:
	void releaseBuffer();
	void concat( const T *text, int length );
	int getLength() const { return m_data ? m_data->length : 0; }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }

	StringHeader<T> *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	StringHeader<unsigned short> *data() const { return m_data; }
};

class GameWindow;
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite );

// ?GadgetListBoxAddEntryTextLines@@YAHPAVGameWindow@@VUnicodeString@@HHH_N@Z
int Rva004BB670GadgetListBoxAddEntryTextLines( GameWindow *listbox,
	UnicodeString text, int color, int row, int column, bool overwrite )
{
	int length = text.getLength();
	UnicodeString line;
	int rowsAdded = 0;

	for ( int offset = 8, i = 0; i <= length; ++i, offset += 2 )
	{
		unsigned short character = text.data() ?
			*(unsigned short *)((unsigned char *)text.data() + offset) : 0;
		if ( character != 0x000A && character != 0 )
		{
			line.concat( &character, 1 );
		}
		else
		{
			if ( line.isEmpty() )
				line.concat( (const unsigned short *)L" ", 1 );

			GadgetListBoxAddEntryText( listbox, line, color, row++, column, overwrite );
			++rowsAdded;
			line.releaseBuffer();
		}
	}

	return rowsAdded;
}
