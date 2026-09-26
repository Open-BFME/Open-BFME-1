// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BfmeAptScreenOnlineCustomMatch StartingSupplies combo apply, retail
// 0x00537B90, 78 bytes. Prefs at +0x174 call the StartingSupplies getter
// (Gen000AC870Owner::Rva000AC870); values outside [0, 5) become 2, then
// GadgetComboBoxSetSelectedPos writes the gadget at +0x1AC.

class GameWindow;

void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, int selectedIndex, bool dontHide );

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow() {}

private:
	unsigned char m_unmodelled[ 0x38 ];
};

class BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSecondary() {}
};

class Gen000AC870Owner
{
public:
	int Rva000AC870();

private:
	unsigned char m_data[ 0x38 ];
};

class BfmeAptScreenOnlineCustomMatch : public BfmeAptGameWindow, public BfmeAptScreenSecondary
{
public:
	void applyStartingSuppliesCombo();

private:
	unsigned char m_setup[ 0x134 ];
	Gen000AC870Owner m_prefs;
	GameWindow *m_combo;
};

void BfmeAptScreenOnlineCustomMatch::applyStartingSuppliesCombo()
{
	if( !m_combo )
		return;

	int index;
	if( m_prefs.Rva000AC870() >= 0 )
	{
		if( m_prefs.Rva000AC870() >= 5 )
			index = 2;
		else
			index = m_prefs.Rva000AC870();
	}
	else
		index = 2;
	GadgetComboBoxSetSelectedPos( m_combo, index, false );
}
