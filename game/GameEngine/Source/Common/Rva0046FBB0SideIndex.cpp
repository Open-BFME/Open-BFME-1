// ?get@Rva0046FBB0SideIndex@@SAHV?$StringBase@D@@@Z
// Retail 0x0046FBB0. Maps a by-value BFME faction string to its side index.
// cl: /DNDEBUG /MD /EHsc

template <typename T>
class StringBase
{
public:
	int compareNoCase(const T *text) const throw();

	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};


class Rva0046FBB0SideIndex
{
public:
	static int get(StringBase<char> side);
};

int Rva0046FBB0SideIndex::get(StringBase<char> side)
{
	if (side.compareNoCase("Rohan") == 0)
		return 0;
	if (side.compareNoCase("Gondor") == 0)
		return 1;
	if (side.compareNoCase("Mordor") == 0)
		return 2;
	if (side.compareNoCase("Isengard") == 0)
		return 3;
	return 4;
}
