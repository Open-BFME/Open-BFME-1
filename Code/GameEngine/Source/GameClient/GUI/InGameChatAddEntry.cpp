// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00512170: InGameChat list-box append.  Requires the three cached
// windows at +0x260/+0x264/+0x268; adds the by-value line through
// GadgetListBoxAddEntryText then the follow-up at ILT 0x00049F30.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
};

class GameWindow;

int GadgetListBoxAddEntryText( GameWindow *listBox, UnicodeString text, int color,
	int row, int column, bool overwrite );
void bfmeCall926A( void *listBox, void *row, void *data, int unused );

class BfmeAptScreenInGameChat
{
public:
	bool addEntry( UnicodeString text, int color );

private:
	char m_head[ 0x260 ];
	GameWindow *m_window0;
	GameWindow *m_window1;
	GameWindow *m_listBox;
};

// ?addEntry@BfmeAptScreenInGameChat@@QAE_NVUnicodeString@@H@Z
bool BfmeAptScreenInGameChat::addEntry( UnicodeString text, int color )
{
	if( m_window0 && m_window1 && m_listBox )
	{
		int row = GadgetListBoxAddEntryText(
			m_listBox, text, color, -1, -1, true );
		bfmeCall926A( m_listBox, (void *)-1, (void *)row, 0 );
		return true;
	}
	return false;
}
