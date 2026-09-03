// cl: /O2 /Ob1

struct BfmeCellAF0
{
	void bfmeFill(void);
	int m_bfmeFirst;
	char m_bfmeMiddle[0x0c];
	int m_bfmeLast;
	char m_bfmeTail[0x14];
};

class Gen_006A6AF0
{
public:
	void bfmeGo(int a, int b, int c);
	void bfmePrep(int a, int c);
	void bfmeFinish(int group, int value, void *arg0, void *arg1);

private:
	void bfmeFinishCell(int group, int cell, void *arg0, void *arg1);

	char m_bfmePad[0x9D4];
	BfmeCellAF0 m_bfmeCells[6];
	int m_bfmeMap[1];
};

void Gen_006A6AF0::bfmeGo(int a, int b, int c)
{
	if (m_bfmeMap[a] == b)
		bfmePrep(a, c);

	m_bfmeCells[b + 2 * a].bfmeFill();
}

void Gen_006A6AF0::bfmeFinish(int group, int value, void *arg0, void *arg1)
{
	if (m_bfmeMap[group] == value && value)
	{
		int cell = value - 1;
		BfmeCellAF0 *entry;
		if (cell > 0)
		{
			entry = &m_bfmeCells[cell + 2 * group];
			do
			{
				if (entry->m_bfmeLast != entry->m_bfmeFirst)
					break;
				--cell;
				--entry;
			} while (cell > 0);
		}
		bfmeFinishCell(group, cell, arg0, arg1);
		return;
	}
	if (m_bfmeMap[group] == value)
		bfmePrep(group, (int)arg0);

	m_bfmeCells[value + 2 * group].bfmeFill();
}
