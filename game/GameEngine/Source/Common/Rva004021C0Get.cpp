// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva004021C0
{
	unsigned m_count;
	unsigned m_pad;
	void *m_items[1];

public:
	void *get(unsigned index) const;
};

void *Rva004021C0::get(unsigned index) const
{
	if (index < m_count)
		return m_items[index];
	else
		return 0;
}
