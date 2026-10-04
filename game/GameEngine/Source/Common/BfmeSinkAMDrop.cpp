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

__forceinline const char *bfmeNameText(const BFMERetailAsciiString &name)
{
	const char *text = name.str();
	if (text != 0)
		text += 8;
	else
		text = "";
	return text;
}

// Retail routes these two BfmeItemAM calls through ILT thunks
// (0x0000510F -> 0x0060AA10, 0x00009EDA -> 0x0061E3E0); call the real
// bodies directly through a thiscall member-pointer alias.
extern void dup_0060aa10();
extern void d_0061e3e0();
void __cdecl operator delete(void *);

class BfmeItemAM
{
public:
};

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
	typedef BFMERetailAsciiString(BfmeItemAM::*GetName)();
	union
	{
		void (*fn)();
		GetName call;
	} u_getName = { dup_0060aa10 };
	typedef void(BfmeItemAM::*Dtor)();
	union
	{
		void (*fn)();
		Dtor call;
	} u_dtor = { d_0061e3e0 };
	reinterpret_cast<BfmeHostCA *>(this)->bfmeRemoveCA(
		bfmeNameText((item->*u_getName.call)()));
	if (item != 0)
	{
		(item->*u_dtor.call)();
		::operator delete(item);
	}
	m_items.erase(found);
}
