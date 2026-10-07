// Open-BFME5 conversions.

struct BfmeBlockVKV
{
	int m_bfmeArr[10];
};

// The leading member is copy-constructed in place: retail calls the private
// StringBase<char> copy constructor (0x00887B60, callees.py) on it. Only that
// member is declared on this minimal view.
class BfmeThingVKV;

template <class T> class StringBase
{
	friend class BfmeThingVKV;
	StringBase(const StringBase<T> &src);
	void *m_data;
};

struct BfmeRefVKV
{
	int m_bfme00;
	int m_bfme04;
};

extern "C" __declspec(dllimport) void __stdcall InterlockedIncrement(void *p);

class BfmeThingVKV
{
public:
	BfmeThingVKV *bfmeInitVKV(const BfmeThingVKV &o);
	StringBase<char> m_bfme00;
	BfmeRefVKV *m_bfme04;
	int m_bfme08;
	BfmeBlockVKV m_bfme0c;
	BfmeBlockVKV m_bfme34;
	char m_bfme5c;
};

BfmeThingVKV *BfmeThingVKV::bfmeInitVKV(const BfmeThingVKV &o)
{
	m_bfme00.StringBase<char>::StringBase(o.m_bfme00);
	m_bfme04 = o.m_bfme04;
	if (m_bfme04)
		InterlockedIncrement(&m_bfme04->m_bfme04);
	m_bfme08 = o.m_bfme08;
	m_bfme0c = o.m_bfme0c;
	m_bfme34 = o.m_bfme34;
	m_bfme5c = o.m_bfme5c;
	return this;
}
