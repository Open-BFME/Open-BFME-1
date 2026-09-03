// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

#pragma intrinsic(memcpy)

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

class EAStringC
{
	public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	private:
	StringDataC *m_pData;

	private:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

	public:
	EAStringC &MakeLower();
	EAStringC &MakeUpper();
};

extern EAStringC::StringDataC g_emptyStringData;

void EAStringC::ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
	unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize)
{
	StringDataC *oldData = m_pData;
	EAStringC *self = this;
	if (oldData->m_uRefCount == 1 && uSizeToReserve <= oldData->m_uMaxSize)
	{
		if (uOffsetCopy != 0)
			memmove((char *)oldData + sizeof(StringDataC),
				(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);

			self->m_pData->m_uSize = (unsigned short)uInternalSize;
			self->m_pData->m_uHash = 0;
		if (ePushZero != CB_NO_PUSH_ZERO)
			GetInternalBuffer()[uInternalSize] = 0;
		return;
	}

	if (uSizeToReserve != 0)
	{
		unsigned int allocationSize = (uSizeToReserve + (uSizeToReserve >> 3) + 0xc) & ~3;
		self->m_pData = (StringDataC *)g_bfmeAllocVKJ->allocate(allocationSize);
		self->m_pData->m_uRefCount = 1;
		self->m_pData->m_uMaxSize = (unsigned short)(allocationSize - 9);
		self->m_pData->m_uSize = (unsigned short)uInternalSize;
		self->m_pData->m_uHash = 0;
		memcpy((char *)self->m_pData + sizeof(StringDataC),
			(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_pData + sizeof(StringDataC))[uInternalSize] = 0;
	}
	else
	{
		self->m_pData = &g_emptyStringData;
		++g_emptyStringData.m_uRefCount;
	}

	if (--oldData->m_uRefCount == 0)
		g_bfmeAllocVKJ->free(oldData);
}
