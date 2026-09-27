// ?d_0089ecd0@@YAXXZ
// partial score=0.34 date=2026-09-27
// cl: /O2 /DNDEBUG /MD

extern "C" unsigned int __cdecl strlen(const char *s);
#pragma intrinsic(strlen)

extern "C" int __cdecl _vsnprintf(char *dst, unsigned int count, const char *format, char *args);

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

extern EAStringData g_emptyStringData;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class EAStringC
{
	typedef EAStringData StringDataC;

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	StringDataC *m_data;

	__declspec(noinline) void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

public:
	void appendFormat0089ECD0(const char *format, ...);
};

void EAStringC::ChangeBuffer(unsigned int reserve, unsigned int offset,
	unsigned int copy, CBPushZero pushZero, unsigned int internalSize)
{
	StringDataC *oldData = m_data;
	EAStringC *self = this;
	if (oldData->m_refCount == 1 && reserve <= oldData->m_maxSize)
	{
		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(StringDataC))[internalSize] = 0;
		return;
	}

	if (reserve != 0)
	{
		unsigned int allocationSize = (reserve + (reserve >> 3) + 0xc) & ~3;
		self->m_data = (StringDataC *)g_bfmeAllocVKJ->allocate(allocationSize);
		self->m_data->m_refCount = 1;
		self->m_data->m_maxSize = (unsigned short)(allocationSize - 9);
		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		for (unsigned int i = 0; i < copy; ++i)
			((char *)self->m_data + sizeof(StringDataC))[i] =
				((char *)oldData + sizeof(StringDataC) + offset)[i];
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(StringDataC))[internalSize] = 0;
	}
	else
	{
		self->m_data = &g_emptyStringData;
		++g_emptyStringData.m_refCount;
	}

	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
}

void EAStringC::appendFormat0089ECD0(const char *format, ...)
{
	unsigned int oldSize = m_data->m_size;
	unsigned int extra = strlen(format) * 4;
	for (;;)
	{
		ChangeBuffer(oldSize + extra, 0, oldSize, CB_NO_PUSH_ZERO, oldSize);
		int written = _vsnprintf(reinterpret_cast<char *>(m_data) + 8 + oldSize,
			m_data->m_maxSize - oldSize, format, reinterpret_cast<char *>(&format + 1));
		if (written >= 0)
		{
			(reinterpret_cast<char *>(m_data) + 8)[oldSize + written] = 0;
			m_data->m_size = (unsigned short)(oldSize + written);
			m_data->m_hash = 0;
			return;
		}
		extra *= 2;
	}
}
