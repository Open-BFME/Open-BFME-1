// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: selected-item-data getter at retail 0x0056AB50, 104 bytes.
// Two GameWindow listboxes at this+0x264 / this+0x268.  Owning class is not
// recovered; Rva0056AB50Owner is an address-derived stand-in.  Same dump
// range as BfmeAptScreenQuitMenu but that object is only 0x260 bytes.

class GameWindow;

void GadgetListBoxGetSelected(GameWindow *listbox, int *selectList);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

class Rva0056AB50Owner
{
public:
	void *getSelectedItemData();

private:
	char m_head[0x264];
	GameWindow *m_list1;
	GameWindow *m_list2;
};

void *Rva0056AB50Owner::getSelectedItemData()
{
	if (m_list1 == 0)
		return 0;

	int selected;
	GadgetListBoxGetSelected(m_list1, &selected);
	void *data = GadgetListBoxGetItemData(m_list1, selected, 0);
	if (selected < 0)
	{
		if (m_list2 != 0)
		{
			GadgetListBoxGetSelected(m_list2, &selected);
			data = GadgetListBoxGetItemData(m_list2, selected, 0);
		}
	}
	return data;
}
