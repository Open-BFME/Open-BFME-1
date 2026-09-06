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

extern char g_bfmeSideNameA1294[];
extern char g_bfmeSideNameB1294[];
extern char g_bfmeSideNameC1294[];
extern char g_bfmeSideNameD1294[];

class Rva0046FBB0SideIndex
{
public:
	static int get(StringBase<char> side);
};

int Rva0046FBB0SideIndex::get(StringBase<char> side)
{
	if (side.compareNoCase(g_bfmeSideNameB1294) == 0)
		return 0;
	if (side.compareNoCase(g_bfmeSideNameA1294) == 0)
		return 1;
	if (side.compareNoCase(g_bfmeSideNameC1294) == 0)
		return 2;
	if (side.compareNoCase(g_bfmeSideNameD1294) == 0)
		return 3;
	return 4;
}
