class GameWindow;
void __cdecl GadgetComboBoxSetSelectedPos(GameWindow *window, int position, bool selected);
int __cdecl bfmeGo1022L(int window);

class BfmeOwnAK
{
public:
	void bfmeToggleAK(int code);

	unsigned char m_bfmeHeadAK[0x288];
	void *m_bfmeSourceAK;
	unsigned char m_bfmeMidAK[0x80];
	int m_bfmeHandleAK;
};

void BfmeOwnAK::bfmeToggleAK(int code)
{
	if (code == 1)
	{
		int handle = m_bfmeHandleAK;

		if (handle != -1)
			GadgetComboBoxSetSelectedPos((GameWindow *)m_bfmeSourceAK, handle, false);

		return;
	}

	void *source = m_bfmeSourceAK;

	if (source)
		m_bfmeHandleAK = bfmeGo1022L((int)source);
}
