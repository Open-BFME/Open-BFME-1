// ?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z
// partial score=0.95 date=2026-09-01
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" char *__cdecl _strlwr(char *);
extern "C" char *__cdecl _strupr(char *);
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

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

	class DebugDataC : public StringDataC
	{
		char m_strText[256];
	};

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

	StringDataC *m_pData;

public:
	EAStringC &MakeLower();
	EAStringC &MakeUpper();
};

void EAStringC::ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
	unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize)
{
	unsigned int allocationSize;
	StringDataC *const oldData = m_pData;
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
		allocationSize = (uSizeToReserve + (uSizeToReserve >> 3) + 0xc) & ~3;
		self->m_pData = (StringDataC *)g_bfmeAllocVKJ->allocate(allocationSize);
		self->m_pData->m_uRefCount = 1;
		self->m_pData->m_uMaxSize = (unsigned short)(allocationSize - 9);
		self->m_pData->m_uSize = (unsigned short)uInternalSize;
		self->m_pData->m_uHash = 0;
		memmove((char *)self->m_pData + sizeof(StringDataC),
			(char *)oldData + sizeof(StringDataC) + uOffsetCopy, uSizeCopy);
		if (ePushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_pData + sizeof(StringDataC))[uInternalSize] = 0;
	}
	else
	{
			self->m_pData = (StringDataC *)0x012D5298;
			++self->m_pData->m_uRefCount;
	}

	if (--oldData->m_uRefCount == 0)
		g_bfmeAllocVKJ->free(oldData);
}

EAStringC &EAStringC::MakeLower()
{
	const unsigned int size = m_pData->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);
	_strlwr(GetInternalBuffer());
	return *this;
}

EAStringC &EAStringC::MakeUpper()
{
	const unsigned int size = m_pData->m_uSize;
	ChangeBuffer(size, 0, size, CB_PUSH_ZERO, size);
	_strupr(GetInternalBuffer());
	return *this;
}
