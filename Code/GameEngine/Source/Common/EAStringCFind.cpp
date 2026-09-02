// cl: /O2 /DNDEBUG /MD

extern "C" char *__cdecl strstr(const char *, const char *);
extern "C" char *__cdecl strchr(const char *, int);

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

	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

public:
	int Find(const char *s, int start);
	int Find(char c, int start);
};

int EAStringC::Find(const char *s, int start)
{
	if (start >= (int)m_pData->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strstr(GetInternalBuffer() + start, s);
	if (found)
		return found - GetInternalBuffer();
	return -1;
}

int EAStringC::Find(char c, int start)
{
	if (start >= (int)m_pData->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strchr(GetInternalBuffer() + start, c);
	if (found)
		return found - GetInternalBuffer();
	return -1;
}
