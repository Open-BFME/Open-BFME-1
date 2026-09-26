// ?Right@EAStringC@@QBE?AV1@H@Z
// partial score=0.9 date=2026-09-07
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern EAStringData g_emptyStringData;


template <typename T> class StringBase

{
	protected:
	EAStringData *m_data;
	StringBase() {}

	private:
	StringBase(const StringBase &other) : m_data(other.m_data)
	{
		++m_data->m_refCount;
	}

	StringBase(EAStringData *data) : m_data(data)
	{
		++m_data->m_refCount;
	}

	protected:
	void releaseBuffer()
	{
		EAStringData *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	~StringBase() { releaseBuffer(); }

	friend class EAStringC;
};

class EAStringC : private StringBase<char>
{
	typedef EAStringData StringDataC;

	EAStringC() : StringBase<char>()
	{
		m_data = &g_emptyStringData;
		++g_emptyStringData.m_refCount;
	}

	EAStringC(const EAStringC &other) : StringBase<char>(other) {}

	EAStringC(EAStringData *data) : StringBase<char>()
	{
		++data->m_refCount;
		m_data = data;
	}

	~EAStringC() {}

	private:
		enum CBPushZero
		{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero push_zero, unsigned int size);

	public:
	EAStringC Right(int count) const;
};

EAStringC EAStringC::Right(int count) const
{
	if (count <= 0)
		return EAStringC();

	int remaining = m_data->m_size - count;
	if (remaining <= 0)
		return EAStringC(*this);

	EAStringC result(m_data);
	result.ChangeBuffer(count, (unsigned int)remaining, count, CB_PUSH_ZERO,
		count);
	return result;
}
