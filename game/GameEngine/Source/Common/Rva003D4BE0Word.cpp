class Rva003D4BE0
{
public:
	short get();

private:
	void *m_data;
};

short Rva003D4BE0::get()
{
	return *(short *)((char *)m_data + 4);
}
