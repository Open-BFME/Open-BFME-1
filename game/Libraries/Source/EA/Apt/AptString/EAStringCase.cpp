// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" char *__cdecl _strlwr(char *);
extern "C" char *__cdecl _strupr(char *);

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

	DebugDataC *m_pData;

public:
	EAStringC &MakeLower();
	EAStringC &MakeUpper();
};

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
