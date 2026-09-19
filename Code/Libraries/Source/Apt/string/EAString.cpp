// cl: /O2 /DNDEBUG /MD /EHsc

// Retail 0x0089F730 compares a suffix with an EAStringC buffer and replaces
// the object with Left(size - suffixSize) when the suffix matches. The address
// derived method name keeps the original Apt string identity unresolved.

typedef bool Bool;

extern "C" unsigned int strlen(const char *);
extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(strlen,memcmp)

struct EAStringData
{
	unsigned short refCount;
	unsigned short size;
	unsigned short maxSize;
	unsigned short hash;
};

struct BfmeStringPool3AF0
{
	void *unused;
	void (__cdecl *free)(void *);
};

extern EAStringData g_emptyStringData;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

template <typename T>
class StringBase
{
protected:
	EAStringData *data;

	StringBase() {}
	StringBase(const StringBase &other) : data(other.data) { ++data->refCount; }
	StringBase(EAStringData *value) : data(value) { ++data->refCount; }
	~StringBase()
	{
		EAStringData *old = data;
		if (--old->refCount == 0)
			g_bfmeStringPool1284->free(old);
	}

	friend class EAStringC;
};

class EAStringC : private StringBase<char>
{
	EAStringC() : StringBase<char>()
	{
		data = &g_emptyStringData;
		++data->refCount;
	}

	EAStringC(const EAStringC &other) : StringBase<char>(other) {}

public:
	EAStringC &operator=(const EAStringC &other)
	{
		++other.data->refCount;
		EAStringData *old = data;
		if (--old->refCount == 0)
			g_bfmeStringPool1284->free(old);
		data = other.data;
		return *this;
	}

	EAStringC Left(int count) const;
	char *buffer() const { return reinterpret_cast<char *>(data) + 8; }
	Bool rva0089F730(const char *suffix);
};

Bool EAStringC::rva0089F730(const char *suffix)
{
	unsigned int size = data->size;
	unsigned int suffixSize = strlen(suffix);
	if (size < suffixSize)
		return false;
	if (memcmp(buffer() + size - suffixSize, suffix, suffixSize) == 0)
	{
		*this = Left(size - suffixSize);
		return true;
	}
	return false;
}
