// AptSaveLoad::InitGadgets callback, retail 0x0056C0C0 (198 bytes).

extern "C" int strcmp(const char *left, const char *right);

class GameWindow
{
public:
	void *winGetUserData();
};

class WinInstanceData
{
private:
	char m_unmodelled[0x10];

public:
	unsigned short m_controlID;
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text)
		: StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

class BfmeAptScreenSaveLoad
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	char m_unmodelled_00[0x258];
	int m_state;
	char m_unmodelled_25c[8];
	GameWindow *m_gameList;
	GameWindow *m_autoSaveList;
	GameWindow *m_fileNameTextEntry;
};

void BfmeAptScreenSaveLoad::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window)
{
	if (window != 0)
	{
		if (strcmp(name, "GameList") == 0)
		{
			m_gameList = window;
			m_state = 2;
		}
		else if (strcmp(name, "AutoSaveList") == 0)
		{
			m_autoSaveList = window;
			m_state = 2;
		}
		else if (strcmp(name, "FileNameTextEntry") == 0)
		{
			m_fileNameTextEntry = window;
			GadgetTextEntrySetText(window,
				UnicodeString((const unsigned short *)0x01088AF4));
			WinInstanceData *instanceData =
				(WinInstanceData *)window->winGetUserData();
			if (instanceData != 0)
				instanceData->m_controlID = 40;
			if (m_state == 0)
				m_state = 1;
		}
	}
}
