// ?UTF8_Initialize@EAStringC@@QAEAAV1@H@Z
// partial score=0.18 date=2026-09-11
// ?UTF8_Initialize@EAStringC@@QAEAAV1@H@Z
// cl: /O2 /DNDEBUG /MD

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(BfmeStringData3AF0 *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class EAStringC
{
public:
	typedef BfmeStringData3AF0 StringDataC;

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);
	EAStringC &UTF8_Initialize(int value);

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	StringDataC *m_pData;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

EAStringC &EAStringC::UTF8_Initialize(int value)
{
	StringDataC *oldData = m_pData;
	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);

	m_pData = &g_bfmeDefaultString1284;
	++g_bfmeDefaultString1284.m_refCount;

	int count;
	if (value < 0x80)
		count = 1;
	else if (value < 0x800)
		count = 2;
	else
		count = 3 + (value >= 0x10000);

	unsigned int size = m_pData->m_length;
	if (size > (unsigned int)count)
		size = count;
	ChangeBuffer(count, 0, size, CB_PUSH_ZERO, size);

	char *buffer = GetInternalBuffer();
	if (value < 0x80)
	{
		buffer[0] = (char)value;
		buffer[1] = 0;
		m_pData->m_length = 1;
		m_pData->m_flags = 0;
		return *this;
	}
	if (value < 0x800)
	{
		buffer[0] = (char)((value >> 6) | 0xc0);
		buffer[2] = 0;
		buffer[1] = (char)((value & 0x3f) | 0x80);
		m_pData->m_length = 2;
		m_pData->m_flags = 0;
		return *this;
	}
	if (value < 0x10000)
	{
		buffer[0] = (char)((value >> 12) | 0xe0);
		buffer[1] = (char)((value >> 6) | 0x80);
		buffer[3] = 0;
		buffer[2] = (char)((value & 0x3f) | 0x80);
		m_pData->m_length = 3;
		m_pData->m_flags = 0;
		return *this;
	}
	buffer[0] = (char)((value >> 18) | 0xf0);
	buffer[4] = 0;
	buffer[1] = (char)((value >> 12) | 0x80);
	buffer[2] = (char)((value >> 6) | 0x80);
	buffer[3] = (char)((value & 0x3f) | 0x80);
	m_pData->m_length = 4;
	m_pData->m_flags = 0;
	return *this;
}
