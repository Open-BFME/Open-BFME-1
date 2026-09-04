// cl: /O2 /Ob0
// BFME's column-width setter is an additive listbox helper.  The retail
// layout keeps the column count at +2 and the width buffer at +4.

class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva004B83B0ListboxData
{
	unsigned char m_prefix[2];
	unsigned short m_columns;
	int *m_columnWidth;
};

void f_00881ef0(void *memory);
extern void *__cdecl operator new[](unsigned int size);

void j_000272fa(void);

void GadgetListBoxSetColumnWidths(GameWindow *listbox, int count, int *widths)
{
	if (count <= 0)
		return;
	if (listbox == 0)
		return;

	Rva004B83B0ListboxData *data =
		(Rva004B83B0ListboxData *)listbox->winGetUserData();
	if (data == 0)
		return;

	data->m_columns = (unsigned short)count;
	f_00881ef0(data->m_columnWidth);
	data->m_columnWidth = new int[count];

	if (widths != 0)
	{
		for (int i = 0; i < count; ++i)
			data->m_columnWidth[i] = widths[i];
	}
	else
	{
		int each = 100 / count;
		int extra = 100 % count;
		for (int i = 0; i < count; ++i)
		{
			if (extra != 0)
			{
				--extra;
				data->m_columnWidth[i] = each + 1;
			}
			else
			{
				data->m_columnWidth[i] = each;
			}
		}
	}

	((void (__cdecl *)(GameWindow *))j_000272fa)(listbox);
}
