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

// Defined after EAStringC, which owns the canonical nested spelling.
static inline EAStringData *rva012D5298Block();
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
	EAStringC() : StringBase<char>()
	{
		m_data = rva012D5298Block();
		++rva012D5298Block()->m_refCount;
	}

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
	// Canonical nested type of the shared empty block at 0x012D5298, defined
	// once in game/GameEngine/Source/Common/Data/Rva012D5298.cpp. Only used to
	// name the global; the bodies read the block through the EAStringData view.
	class StringDataC;

	EAStringC rva0089F0E0(int count) const;
};

// The shared empty EA string block at 0x012D5298, defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp and named here through
// its canonical spelling; the TU-local EAStringData view has the same layout.
extern EAStringC::StringDataC g_rva012D5298Empty;

static inline EAStringData *rva012D5298Block()
{
	return (EAStringData *)&g_rva012D5298Empty;
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
		self->m_data = rva012D5298Block();
		++rva012D5298Block()->m_refCount;
	}

	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
}

// Suffix of `count` characters: offset = length - count. Owner EAStringC from
// the this-call to matched ChangeBuffer 0x0089E570 and the layout shared with
// landed Left 0x0089F010 and Mid 0x0089F1B0; method name kept address-derived
// because no caller, vtable slot, string or Zero Hour twin names it. ChangeBuffer
// is defined noinline in this TU as in EAStringCLeft.cpp/EAStringCMid.cpp: with
// it only declared, VC7.1 swaps the ECX/EDX data-pointer allocation.
EAStringC EAStringC::rva0089F0E0(int count) const
{
	if (count <= 0)
		return EAStringC();

	int remaining = m_data->m_size - count;
	if (remaining <= 0)
		return *this;

	EAStringC result(*this);
	result.ChangeBuffer(count, remaining, count, CB_PUSH_ZERO, count);
	return result;
}
