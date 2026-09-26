// ?d_0089e0c0@@YAXXZ
// partial score=0.8 date=2026-09-11
// cl: /O2 /DNDEBUG /MD /EHsc

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct EAStringData
{
	unsigned short m_uRefCount;
	unsigned short m_uSize;
	unsigned short m_uMaxSize;
	unsigned short m_uHash;
};

template <typename T> class StringBase
{
protected:
	EAStringData *m_data;
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other) : m_data(other.m_data)
	{
		++m_data->m_uRefCount;
	}

private:
	void releaseBuffer()
	{
		EAStringData *data = m_data;
		if (--data->m_uRefCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	~StringBase()
	{
		releaseBuffer();
	}
	friend class EAStringC;
};

class EAStringC : private StringBase<char>
{
public:
	typedef EAStringData StringDataC;
	EAStringC(unsigned int nSize);
	EAStringC(const EAStringC &other) : StringBase<char>(other) {}
	~EAStringC() {}
	EAStringC operator+(const EAStringC &other) const;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_data) + sizeof(StringDataC);
	}
};

// ??HEAStringC@@QBE?AV0@ABV0@@Z
EAStringC EAStringC::operator+(const EAStringC &other) const
{
	unsigned int thisSize = m_data->m_uSize;
	if (thisSize == 0)
		return other;

	unsigned int otherSize = other.m_data->m_uSize;
	if (otherSize == 0)
		return *this;

	EAStringC result(thisSize + otherSize);
	EAStringC::StringDataC *resultData = result.m_data;
	memcpy(reinterpret_cast<char *>(resultData) + sizeof(EAStringC::StringDataC),
		GetInternalBuffer(), thisSize);
	memcpy(reinterpret_cast<char *>(resultData) + sizeof(EAStringC::StringDataC) + thisSize,
		other.GetInternalBuffer(), otherSize);
	reinterpret_cast<char *>(resultData)[sizeof(EAStringC::StringDataC) + thisSize + otherSize] = 0;
	resultData->m_uSize = thisSize + otherSize;
	resultData->m_uHash = 0;
	return result;
}
