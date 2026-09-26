// cl: /DNDEBUG /MD
//
// Retail 0x0055E070: map 0..5 onto combo indices 4,3,2,1,0,5, then
// GadgetComboBoxSetSelectedPos + bfmeGo1022L.  The combo pointer at +0x288
// is cleared around the call and restored, matching retail's reentrancy store.

class GameWindow;

void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, int selectedIndex, bool dontHide );
int bfmeGo1022L( int h );

class BfmeAptScreenSetComboFromIndex
{
public:
	void setComboFromIndex( int index );

private:
	unsigned char m_unmodelled_000[ 0x288 ];
	GameWindow *m_combo;
	unsigned char m_unmodelled_28c[ 0x30c - 0x28c ];
	int m_selected;
};

// ?setComboFromIndex@BfmeAptScreenSetComboFromIndex@@QAEXH@Z
void BfmeAptScreenSetComboFromIndex::setComboFromIndex( int index )
{
	GameWindow *combo = m_combo;
	if( !combo )
		return;

	m_combo = 0;
	switch( index )
	{
	case 0:
		GadgetComboBoxSetSelectedPos( combo, 4, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	case 1:
		GadgetComboBoxSetSelectedPos( combo, 3, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	case 2:
		GadgetComboBoxSetSelectedPos( combo, 2, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	case 3:
		GadgetComboBoxSetSelectedPos( combo, 1, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	case 4:
		GadgetComboBoxSetSelectedPos( combo, 0, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	case 5:
		GadgetComboBoxSetSelectedPos( combo, 5, false );
		m_selected = bfmeGo1022L( (int)combo );
		break;
	}
	m_combo = combo;
}
