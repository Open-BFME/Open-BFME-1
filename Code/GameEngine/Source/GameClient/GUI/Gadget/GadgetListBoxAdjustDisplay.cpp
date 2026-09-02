// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryRowBFME
{
	int listHeight;
	short rowTop;
	short unused6;
	void *cell;
};

struct ListboxDataBFME
{
	char unused00[0x18];
	ListEntryRowBFME *listData;
	char unused1c[0x10];
	short endPos;
	char unused2e[0x0e];
	short displayHeight;
	char unused3e[6];
	short displayPos;
};

void adjustDisplay(GameWindow *window, bool updateSlider);

static int getListboxTopEntry(ListboxDataBFME *list)
{
	int entry;
	for (entry = 0; ; ++entry)
	{
		if (list->listData[entry].listHeight > list->displayPos)
			return entry;
		if (entry >= list->endPos)
			return 0;
	}
}

void adjustDisplay(GameWindow *window, int adjustment, bool updateSlider)
{
	ListboxDataBFME *list = (ListboxDataBFME *)window->winGetUserData();

	if (updateSlider)
	{
		int entry = getListboxTopEntry(list) + adjustment;
		if (entry < 0)
			entry = 0;
		else if (entry >= list->endPos)
			entry = list->endPos - 1;

		list->displayPos = list->listData[entry].listHeight - list->listData[entry].rowTop;
	}

	adjustDisplay(window, updateSlider);
}
