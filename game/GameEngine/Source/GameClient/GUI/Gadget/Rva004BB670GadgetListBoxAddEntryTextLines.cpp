// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The BFME-only helper at 0x004BB670 splits a UnicodeString at newlines and
// NULs and appends each resulting line through GadgetListBoxAddEntryText
// (retail call through ILT 0x0003FE86 to the matched body at 0x004BB4B0),
// returning the number of rows added.  No named caller or source twin proves
// the original spelling, so the name keeps the address token and records the
// observed behavior.

#include "string_base.h"

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

#include "../../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class GameWindow;
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite );

int Rva004BB670GadgetListBoxAddEntryTextLines( GameWindow *listbox,
	UnicodeString text, int color, int row, int column, bool overwrite )
{
	int length = ((StringBase<unsigned short>*)(&(text)))->getLength();
	UnicodeString line;
	int rowsAdded = 0;

	for ( int i = 0; i <= length; ++i )
	{
		unsigned short character = ( i < length ) ? ((StringBase<unsigned short>*)(&(text)))->getCharAt( i ) : 0;
		if ( character == 0x000A || character == 0 )
		{
			if ( ((StringBase<unsigned short>*)(&(line)))->isEmpty() )
				((StringBase<unsigned short>*)(&(line)))->concat( (unsigned short)' ' );

			GadgetListBoxAddEntryText( listbox, line, color, row++, column, overwrite );
			++rowsAdded;
			((StringBase<unsigned short>*)(&(line)))->clear();
		}
		else
		{
			((StringBase<unsigned short>*)(&(line)))->concat( character );
		}
	}

	return rowsAdded;
}
