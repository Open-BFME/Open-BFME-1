// ?UTF8_Initialize008A0320@EAStringC@@QAEAAV1@H@Z
// cl: /O2 /DNDEBUG /MD

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		unsigned short m_flags;
	};

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

private:
	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

public:
	// ?GetInternalBuffer@EAStringC@@QBEPADXZ absent-from-retail
	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	EAStringC &UTF8_Initialize008A0320(int value);

	StringDataC *m_pData;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

EAStringC &EAStringC::UTF8_Initialize008A0320(int value)
{
	StringDataC *oldData = m_pData;
	--oldData->m_refCount;
	if (oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);

	m_pData = &g_rva012D5298Empty;
	++g_rva012D5298Empty.m_refCount;

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
	ChangeBuffer(count, 0, size, EAStringC::CB_PUSH_ZERO, size);

	char *buffer = reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	if (value < 0x80)
	{
		buffer[0] = (char)value;
		buffer[1] = 0;
		m_pData->m_length = 1;
	}
	else if (value < 0x800)
	{
		buffer[0] = (char)((value >> 6) | 0xc0);
		buffer[2] = 0;
		buffer[1] = (char)((value & 0x3f) | 0x80);
		m_pData->m_length = 2;
	}
	else if (value < 0x10000)
	{
		buffer[0] = (char)((value >> 12) | 0xe0);
		buffer[1] = (char)(((value >> 6) & 0x3f) | 0x80);
		buffer[3] = 0;
		buffer[2] = (char)((value & 0x3f) | 0x80);
		m_pData->m_length = 3;
	}
	else
	{
		buffer[0] = (char)((value >> 18) | 0xf0);
		buffer[1] = (char)(((value >> 12) & 0x3f) | 0x80);
		buffer[2] = (char)(((value >> 6) & 0x3f) | 0x80);
		buffer[4] = 0;
		buffer[3] = (char)((value & 0x3f) | 0x80);
		m_pData->m_length = 4;
	}
	m_pData->m_flags = 0;
	return *this;
}
