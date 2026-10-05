// Open-BFME7: normalize an Apt hierarchy path, using the root separator when
// the recursive mode-zero path builder produces an empty string.

extern const char g_Rva0107301CEmptyString[];

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

// The Apt allocator-hook pair pointer at VA 0x01337A30, defined once by
// game/Libraries/Source/Apt/Apt.cpp.  Slot +4 is the deallocator this TU calls;
// the view below is the TU-local spelling of that second slot.
struct BfmeStringPool3AF0;
extern struct BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			((BfmeStringPoolVKI *)g_rva01337A30AllocPair)->free(data);
	}

	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		other.m_data->m_refCount++;

		BfmeHdrVKI *old = m_data;
		if (--old->m_refCount == 0)
			((BfmeStringPoolVKI *)g_rva01337A30AllocPair)->free(old);

		m_data = other.m_data;
		return *this;
	}

	BfmeHdrVKI *m_data;
};

void bfmeApplyEVF(void *node, BfmeStrVKI *text, int mode);

void bfmeNormalizeEVF(void *node, BfmeStrVKI *text)
{
	*text = g_Rva0107301CEmptyString;
	bfmeApplyEVF(node, text, 0);
	if (text->m_data->m_length == 0)
		*text = "/";
}
