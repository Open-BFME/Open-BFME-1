// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006A57D0: prepare one indexed grid lane, drain cells down to a
// requested level, and notify the lane when its boundary changes.

class BfmeCellAF0
{
public:
	void bfmeFill(void);

	int m_first;
	char m_middle[0x0c];
	int m_last;
	char m_tail[0x14];
};

class Gen_006A6AF0
{
public:
	void bfmePrep(int first, int third);
};

class Rva006A57D0Owner
{
public:
	void process(int index, int threshold, int level, int extra);

private:
	char m_pad[0x9d4];
	BfmeCellAF0 m_cells[6];
	int m_counts[1];
};

extern void b_006a56a0();
typedef void (Rva006A57D0Owner::*Rva006A57D0Notify)(int, int, int);

void Rva006A57D0Owner::process(int index, int threshold, int level, int extra)
{
	((Gen_006A6AF0 *)this)->bfmePrep(index, level);

	int count = m_counts[index];
	while (threshold < count)
	{
		m_cells[count + index * 2].bfmeFill();
		m_counts[index] -= 1;
		count = m_counts[index];
	}

	BfmeCellAF0 *cell = &m_cells[threshold + index * 2];
	if (cell->m_last != cell->m_first)
	{
		union
		{
			void *asVoid;
			Rva006A57D0Notify asMember;
		} notifyCast;
		notifyCast.asVoid = (void *)&b_006a56a0;
		(this->*notifyCast.asMember)(index, threshold, extra);
	}
}
