// cl: /O2 /DNDEBUG /MD /EHsc
// The retail body at 0x0089F420 scans an EAStringC buffer with strchr and
// returns the suffix through the exact Mid(int) helper at 0x0089F1B0.

extern "C" char *__cdecl strchr( const char *, int );

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

struct BfmeAllocVKJ
{
	void *(__cdecl *allocate)( unsigned int );
	void (__cdecl *free)( void * );
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

extern EAStringData g_emptyStringData;

class EAStringC
{
public:
	EAStringC();
	EAStringC( const EAStringC &other ) : m_pData( other.m_pData )
	{
		++m_pData->m_refCount;
	}
	~EAStringC()
	{
		EAStringData *data = m_pData;
		if (--data->m_refCount == 0)
			g_bfmeAllocVKJ->free( data );
	}
	EAStringC &operator=( const EAStringC &other )
	{
		++other.m_pData->m_refCount;
		EAStringData *oldData = m_pData;
		if (--oldData->m_refCount == 0)
			g_bfmeAllocVKJ->free( oldData );
		m_pData = other.m_pData;
		return *this;
	}

	EAStringC Mid( int count ) const;
	EAStringC &rva0089F420( const char *characters );

private:
	EAStringData *m_pData;

	const char *GetInternalBuffer() const
	{
		return reinterpret_cast<const char *>(m_pData) + sizeof(EAStringData);
	}
};

EAStringC::EAStringC()
	: m_pData( &g_emptyStringData )
{
	++m_pData->m_refCount;
}

EAStringC &EAStringC::rva0089F420( const char *characters )
{
	unsigned int size = m_pData->m_size;
	const char *character = GetInternalBuffer();
	unsigned int count = 0;
	while (count < size)
	{
		char value = *character;
		++character;
		if (strchr( characters, value ) == 0)
			break;
		++count;
	}
	EAStringC result;
	result = Mid( count );
	*this = result;
	return *this;
}
