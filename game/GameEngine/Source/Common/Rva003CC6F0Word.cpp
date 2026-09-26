class Rva003CC6F0
{
public:
	short get();

private:
	int m_pad;
	void *m_data;
};

short Rva003CC6F0::get()
{
	return *(short *)((char *)m_data + 0x1C);
}
