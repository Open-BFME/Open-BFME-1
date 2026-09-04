// cl: /O2 /Ob0

class GameWindow
{
public:
	void *winGetUserData(void);
	bool winIsHidden(void);
	int winHide(bool hide);
};

struct Rva004B7A10ListboxData
{
	char m_prefix[0x1c];
	GameWindow *m_upButton;
	GameWindow *m_downButton;
	GameWindow *m_slider;
};

// ?Rva004B7A10SetScrollButtonsHidden@@YAXPAVGameWindow@@_N@Z
void Rva004B7A10SetScrollButtonsHidden(GameWindow *window, bool hide)
{
	if (window != 0)
	{
		Rva004B7A10ListboxData *data =
			(Rva004B7A10ListboxData *)window->winGetUserData();
		GameWindow *child = data != 0 ? data->m_slider : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);

		data = (Rva004B7A10ListboxData *)window->winGetUserData();
		child = data != 0 ? data->m_upButton : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);

		data = (Rva004B7A10ListboxData *)window->winGetUserData();
		child = data != 0 ? data->m_downButton : 0;
		if (child != 0 && child->winIsHidden() != hide)
			child->winHide(hide);
	}
}
