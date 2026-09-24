// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// The BFME-only helper at 0x004BB670 splits a UnicodeString at newlines and
// NULs and appends each resulting line through GadgetListBoxAddEntryText
// (retail call through ILT 0x0003FE86 to the matched body at 0x004BB4B0),
// returning the number of rows added.  No named caller or source twin proves
// the original spelling, so the name keeps the address token and records the
// observed behavior.

#include "string_base.h"

template <typename T> inline StringBase<T>::StringBase() : m_data( 0 ) {}
template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template <typename T> inline int StringBase<T>::getLength() const
{
	return m_data ? m_data->length : 0;
}
template <typename T> inline T StringBase<T>::getCharAt( int index ) const
{
	return m_data ? m_data->data[index] : 0;
}
template <typename T> inline bool StringBase<T>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}
template <typename T> inline void StringBase<T>::concat( T c )
{
	concat( &c, 1 );
}
template <typename T> inline void StringBase<T>::clear()
{
	releaseBuffer();
}

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &source )
		: StringBase<unsigned short>( source ) {}
	~UnicodeString() {}
};

class GameWindow;
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite );

int Rva004BB670GadgetListBoxAddEntryTextLines( GameWindow *listbox,
	UnicodeString text, int color, int row, int column, bool overwrite )
{
	int length = text.getLength();
	UnicodeString line;
	int rowsAdded = 0;

	for ( int i = 0; i <= length; ++i )
	{
		unsigned short character = ( i < length ) ? text.getCharAt( i ) : 0;
		if ( character == 0x000A || character == 0 )
		{
			if ( line.isEmpty() )
				line.concat( (unsigned short)' ' );

			GadgetListBoxAddEntryText( listbox, line, color, row++, column, overwrite );
			++rowsAdded;
			line.clear();
		}
		else
		{
			line.concat( character );
		}
	}

	return rowsAdded;
}
