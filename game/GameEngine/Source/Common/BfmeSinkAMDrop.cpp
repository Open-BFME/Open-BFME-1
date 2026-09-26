// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

template <typename T> class BfmeStringBase
{
protected:
	BfmeStringBase() : m_data(0) {}
	BfmeStringBase(const BfmeStringBase &other) : m_data(other.m_data) {}
	__forceinline ~BfmeStringBase() {}

	char *m_data;
};

class BFMERetailAsciiString : private BfmeStringBase<char>
{
public:
	BFMERetailAsciiString() : BfmeStringBase<char>() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: BfmeStringBase<char>(other) {}
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer();

	const char *str() const
	{
		return m_data;
	}
};

extern const char Rva006A16B0Empty[];

__forceinline const char *bfmeNameText(const BFMERetailAsciiString &name)
{
	const char *text = name.str();
	if (text != 0)
		text += 8;
	else
		text = Rva006A16B0Empty;
	return text;
}

class BfmeItemAM
{
public:
	BFMERetailAsciiString getName();
	~BfmeItemAM();
};

#pragma comment(linker, "/alternatename:?getName@BfmeItemAM@@QAE?AVBFMERetailAsciiString@@XZ=?dup_0060aa10@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeItemAM@@QAE@XZ=?d_0061e3e0@@YAXXZ")

class BfmeHostCA
{
public:
	void bfmeRemoveCA(const char *name);
};

typedef _STL::hash_map<int, BfmeItemAM *> BfmeItemMapAM;

class BfmeSinkAM
{
public:
	void bfmeDrop(int handle);

private:
	char m_bfmePad[0x210];
	BfmeItemMapAM m_items;
};

void BfmeSinkAM::bfmeDrop(int handle)
{
	BfmeItemMapAM::iterator found = m_items.find(handle);
	if (found == m_items.end())
		return;

	BfmeItemAM *item = found->second;
	reinterpret_cast<BfmeHostCA *>(this)->bfmeRemoveCA(
		bfmeNameText(item->getName()));
	if (item != 0)
		delete item;
	m_items.erase(found);
}
