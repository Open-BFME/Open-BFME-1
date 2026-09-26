class Rva003D4BD0
{
public:
	short get();

private:
	void *m_data;
};

short Rva003D4BD0::get()
{
	return *(short *)m_data;
}
