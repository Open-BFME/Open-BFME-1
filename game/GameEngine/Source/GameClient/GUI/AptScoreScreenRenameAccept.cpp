// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenScoreScreen::_bfme_renameAccept, retail 0x005710A0, 230 bytes.
// The score screen constructor pushes the selector string
// "AptScoreScreen::RenameAccept" at 0x00578465 and loads this body's ILT thunk
// a few bytes later, which is what names it.
//
// The callback takes the text the player typed into the rename box, writes it
// into the record at this+0x318, puts it back in the list box row this+0x31C,
// and clears both fields.

#include <wchar.h>
#include "Common/UnicodeString.h"

class GameWindow
{
public:
	int winEnable( bool enable );
};

// The record the rename box edits. Retail only touches its UnicodeString at
// +0x78, so the rest stays unmodelled and the name stays address-derived.
struct Rva005710A0Record
{
	unsigned char m_head[ 0x78 ];
	UnicodeString m_name;
};

extern int g_color12B7FC8;

// upstream declarations: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Gadget.h
UnicodeString GadgetTextEntryGetText( GameWindow *textEntry );
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text, int color,
	int row, int column, bool overwrite );

class BfmeAptScreenScoreScreen
{
public:
	void _bfme_renameAccept( const char *name );

private:
	unsigned char m_head[ 0x310 ];
	GameWindow *m_listBox;
	GameWindow *m_textEntry;
	Rva005710A0Record *m_record;
	int m_row;
};

void BfmeAptScreenScoreScreen::_bfme_renameAccept( const char *name )
{
	(void)name;
	if ( m_record == 0 )
		return;

	UnicodeString text = GadgetTextEntryGetText( m_textEntry );
	// The record pointer has to land in its own local and the field in its own
	// reference. Retail materialises the pointer, then computes the field
	// address into ecx before it pushes the argument.
	Rva005710A0Record *record = m_record;
	UnicodeString &field = record->m_name;
	field.set( text );

	if ( m_listBox != 0 )
	{
		m_listBox->winEnable( true );
		if ( m_row >= 0 )
			GadgetListBoxAddEntryText( m_listBox, text, g_color12B7FC8, m_row, 1, true );
	}

	m_record = 0;
	m_row = -1;
	if ( m_listBox != 0 )
		m_listBox->winEnable( true );
}
