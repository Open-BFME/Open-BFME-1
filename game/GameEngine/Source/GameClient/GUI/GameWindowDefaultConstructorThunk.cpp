// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

// Byte-exact BFME reconstruction of ??0GameWindow@@QAE@XZ.  The BFME layout
// is kept TU-local because the ordinary GameWindow reference header has the
// Zero Hour offsets; these fields are corroborated by the BFME accessors and
// neighboring constructors.
class WinInstanceData
{
public:
	WinInstanceData();

private:
	char m_data[ 0x1A8 ];
};

class GameWindow
{
public:
	GameWindow();
	virtual void winDrawBorder( void ) = 0;

private:
	void *m_bfmeAnchor;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	int m_regionLoX;
	int m_regionLoY;
	int m_regionHiX;
	int m_regionHiY;
	int m_cursorX;
	int m_cursorY;
	void *m_userData;
	WinInstanceData m_instData;
	void *m_inputData;
	void *m_bfmeInputExtra;
	void *m_input;
	void *m_system;
	void *m_draw;
	void *m_tooltip;
	void *m_bfmeCallbackExtra;
	int m_bfmeCallbackExtra2;
	void *m_next;
	void *m_prev;
	void *m_parent;
	void *m_child;
	void *m_nextLayout;
	void *m_prevLayout;
	void *m_layout;
	void *m_editData;
};

GameWindow::GameWindow( void )
{
	m_bfmeAnchor = 0;
	m_status = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_regionLoX = 0;
	m_regionLoY = 0;
	m_regionHiX = 0;
	m_regionHiY = 0;
	m_cursorX = 0;
	m_cursorY = 0;
	m_userData = 0;
	m_inputData = 0;
	m_bfmeInputExtra = 0;
	m_input = 0;
	m_system = 0;
	m_draw = 0;
	m_tooltip = 0;
	m_bfmeCallbackExtra = 0;
	m_next = 0;
	m_prev = 0;
	m_parent = 0;
	m_child = 0;
	m_nextLayout = 0;
	m_prevLayout = 0;
	m_layout = 0;
	m_editData = 0;
	m_bfmeCallbackExtra2 = 1;
}
