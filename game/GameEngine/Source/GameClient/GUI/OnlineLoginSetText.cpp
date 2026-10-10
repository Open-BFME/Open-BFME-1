// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s); }
template<> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

class GameWindow;

void GadgetCheckBoxSetChecked( GameWindow *window, bool enabled );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenOnlineLogin
{
public:
	bool bfmeSetTextAt7C( const UnicodeString &text, bool updateEnabled );

private:
	unsigned char m_unmodelled[ 0x7C ];
	GameWindow *m_textEntry;
	GameWindow *m_dependentControl;
};

bool BfmeAptScreenOnlineLogin::bfmeSetTextAt7C(
	const UnicodeString &text, bool updateEnabled )
{
	bool textWasSet = false;
	if( m_textEntry )
	{
		if( m_dependentControl && updateEnabled )
			GadgetCheckBoxSetChecked( m_dependentControl, !((const StringBase<unsigned short> *)&text)->isEmpty() );

		GadgetTextEntrySetText( m_textEntry, text );
		textWasSet = true;
	}
	return textWasSet;
}
