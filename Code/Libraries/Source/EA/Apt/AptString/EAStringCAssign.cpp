// cl: /O2 /DNDEBUG /MD

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

class EAStringC
{
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	EAStringC &Assign(const EAStringC &other);
};

EAStringC &EAStringC::Assign(const EAStringC &other)
{
	unsigned otherSize = other.m_pData->m_uSize;
	unsigned n = m_pData->m_uSize;
	if (n > otherSize)
		n = otherSize;
	ChangeBuffer(otherSize, 0, n, CB_PUSH_ZERO, n);
	char *dst = GetInternalBuffer();
	memcpy(dst, other.GetInternalBuffer(), otherSize);
	dst[otherSize] = 0;
	m_pData->m_uSize = (unsigned short)otherSize;
	m_pData->m_uHash = other.m_pData->m_uHash;
	return *this;
}
