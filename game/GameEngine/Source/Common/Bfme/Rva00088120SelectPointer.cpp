// cl: /DNDEBUG /MD /EHsc

struct Rva00088120SelectPointer
{
	unsigned char m_unmodelled_000[0x20];
	unsigned char m_selected[4];
	unsigned char *m_pointer;

	void *select();
};

void *Rva00088120SelectPointer::select()
{
	if (m_pointer == 0)
		goto selected;
	if (*reinterpret_cast<unsigned short *>(m_pointer + 4) != 0)
		goto pointer;
selected:
	return m_selected;
pointer:
	return reinterpret_cast<unsigned char *>(&m_pointer);
}
