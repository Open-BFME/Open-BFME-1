class Rva00923770
{
public:
	void *get(int index);

private:
	char m_pad[0x130];
	void *m_items[32];
	int m_count;
};

void *Rva00923770::get(int index)
{
	if (index < 0 || (unsigned)index >= (unsigned)m_count)
		return 0;
	return m_items[index];
}
