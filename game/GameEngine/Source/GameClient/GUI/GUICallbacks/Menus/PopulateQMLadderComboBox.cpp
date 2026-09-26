// cl: /DNDEBUG /MD /EHsc

// PopulateQMLadderComboBox, retail 0x005091D0. Sixteen bytes: the panel at
// 0x012F4820 is asked to fill itself, and a null panel is simply not asked.
// The call is a tail jump, so this function adds nothing of its own.

class BfmeQuickMatchLadderPanel
{
public:
	void populateLadderList( void );
};

extern BfmeQuickMatchLadderPanel *TheQuickMatchLadderPanel;		// 0x012F4820

// ?PopulateQMLadderComboBox@@YAXXZ
void PopulateQMLadderComboBox( void )
{
	if( TheQuickMatchLadderPanel )
		TheQuickMatchLadderPanel->populateLadderList();
}
