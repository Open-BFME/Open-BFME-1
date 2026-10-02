// cl: /O2 /DNDEBUG /MD /EHsc

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

#pragma intrinsic(memcpy)

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

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
	EAStringC();

	EAStringC(const EAStringC &other) : StringBase<char>(other) {}

	EAStringC(EAStringData *data) : StringBase<char>()
	{
		++data->m_refCount;
		m_data = data;
	}

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	__declspec(noinline) void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

public:
	// The shared empty EA string block at 0x012D5298 is one global, EA's
	// EAStringC::StringDataC g_rva012D5298Empty (defined in
	// game/GameEngine/Source/Common/Data/Rva012D5298.cpp).  MSVC mangles a
	// global's type into its name, so the extern below must carry that exact
	// spelling.  Only declared here: every use of the global in this TU goes
	// through the local EAStringData view, which shares its layout.  The
	// default constructor is defined after the extern, which is why it is not
	// inline in the class body.
	class StringDataC;

	EAStringC Mid(int start) const;
	EAStringC Mid(int start, int count) const;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

EAStringC::EAStringC() : StringBase<char>()
{
	m_data = (EAStringData *)&g_rva012D5298Empty;
	++((EAStringData *)&g_rva012D5298Empty)->m_refCount;
}

void EAStringC::ChangeBuffer(unsigned int reserve, unsigned int offset,
	unsigned int copy, CBPushZero pushZero, unsigned int internalSize)
{
	EAStringData *oldData = m_data;
	EAStringC *self = this;
	if (oldData->m_refCount == 1 && reserve <= oldData->m_maxSize)
	{
		if (offset != 0)
			memmove((char *)oldData + sizeof(EAStringData),
				(char *)oldData + sizeof(EAStringData) + offset, copy);

		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(EAStringData))[internalSize] = 0;
		return;
	}

	if (reserve != 0)
	{
		unsigned int allocationSize = (reserve + (reserve >> 3) + 0xc) & ~3;
		self->m_data = (EAStringData *)g_bfmeAllocVKJ->allocate(allocationSize);
		self->m_data->m_refCount = 1;
		self->m_data->m_maxSize = (unsigned short)(allocationSize - 9);
		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		memcpy((char *)self->m_data + sizeof(EAStringData),
			(char *)oldData + sizeof(EAStringData) + offset, copy);
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(EAStringData))[internalSize] = 0;
	}
	else
	{
		self->m_data = (EAStringData *)&g_rva012D5298Empty;
		++((EAStringData *)&g_rva012D5298Empty)->m_refCount;
	}

	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
}

EAStringC EAStringC::Mid(int start) const
{
	if (start <= 0)
		return *this;

	int size = m_data->m_size - start;
	if (size <= 0)
		return EAStringC();

	EAStringC result(m_data);
	result.ChangeBuffer(size, start, size, CB_PUSH_ZERO, size);
	return result;
}

EAStringC EAStringC::Mid(int start, int count) const
{
	int effectiveStart = start;
	int adjustedCount = count;
	if (start < 0)
	{
		adjustedCount += start;
		effectiveStart = 0;
	}
	if (adjustedCount <= 0)
		return EAStringC();

	int size = m_data->m_size - effectiveStart;
	if (size <= 0)
		return EAStringC();
	if (adjustedCount < size)
		size = adjustedCount;

	EAStringC result(m_data);
	result.ChangeBuffer(size, start, size, CB_PUSH_ZERO, size);
	return result;
}
