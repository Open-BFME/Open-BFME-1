// cl: /O2 /Ob0
//
// BFME-only listbox column-width recalculation, retail 0x004B8230 (303
// bytes).  The caller-facing setter owns the percentage buffer at +0x04;
// this helper owns the pixel-width buffer at +0x14 and uses the slider at
// +0x24.  Those offsets are the BFME record view, not the shorter ZH view.

class GameWindow
{
public:
	void *winGetUserData();
	int winGetSize(int *width, int *height);
};

void * __cdecl operator new[](unsigned int bytes);
void __cdecl operator delete[](void *block);

struct Rva004B8230ListboxData
{
	unsigned char m_prefix[2];
	short m_columns;
	int *m_columnWidthPercentage;
	unsigned char m_gap08[0x0c];
	int *m_columnWidth;
	unsigned char m_gap18[0x0c];
	GameWindow *m_slider;
};

struct Rva004B8230Coord
{
	int x;
	int y;
};

extern void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count,
	int *widths);

// ?Rva004B8230UpdateColumnWidths@@YAXPAVGameWindow@@@Z
void Rva004B8230UpdateColumnWidths(GameWindow *listbox)
{
	if (listbox == 0)
		return;

	Rva004B8230ListboxData *data =
		(Rva004B8230ListboxData *)listbox->winGetUserData();
	if (data == 0)
		return;

	int width;
	int height;
	listbox->winGetSize(&width, &height);

	if (data->m_columns == 1)
	{
		data->m_columnWidth = new int[1];
		data->m_columnWidth[0] = width;

		if (data->m_slider == 0)
			return;

		Rva004B8230Coord sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		data->m_columnWidth[0] += -2 - sliderSize.x;
		return;
	}

	if (data->m_columnWidthPercentage == 0)
	{
		GadgetListBoxSetColumnWidths(listbox, data->m_columns, 0);
		return;
	}

	if (data->m_columnWidth != 0)
	{
		delete [] data->m_columnWidth;
		data->m_columnWidth = 0;
	}
	data->m_columnWidth = new int[(int)data->m_columns];

	int totalWidth = width;
	if (data->m_slider != 0)
	{
		Rva004B8230Coord sliderSize;
		data->m_slider->winGetSize(&sliderSize.x, &sliderSize.y);
		totalWidth += -2 - sliderSize.x;
	}

	for (int i = 0; i < data->m_columns; ++i)
		data->m_columnWidth[i] =
			data->m_columnWidthPercentage[i] * totalWidth / 100;
}
