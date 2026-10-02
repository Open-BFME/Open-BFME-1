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

struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class EAStringC
{
public:
	// 0x012D5298: the shared empty EA string block, defined once in
	// game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  This TU keeps its
	// own EAStringData view of it and casts at the use.
	class StringDataC;

	inline EAStringC();
	EAStringC( const EAStringC &other ) : m_pData( other.m_pData )
	{
		++m_pData->m_refCount;
	}
	~EAStringC()
	{
		EAStringData *data = m_pData;
		if (--data->m_refCount == 0)
			reinterpret_cast<BfmeAllocVKJ *>(g_rva01337A30AllocPair)->free( data );
	}
	EAStringC &operator=( const EAStringC &other )
	{
		++other.m_pData->m_refCount;
		EAStringData *oldData = m_pData;
		if (--oldData->m_refCount == 0)
			reinterpret_cast<BfmeAllocVKJ *>(g_rva01337A30AllocPair)->free( oldData );
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

extern EAStringC::StringDataC g_rva012D5298Empty;

inline EAStringC::EAStringC()
	: m_pData( (EAStringData *)&g_rva012D5298Empty )
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
