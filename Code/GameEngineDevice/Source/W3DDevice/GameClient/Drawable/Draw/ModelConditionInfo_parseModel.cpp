// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: clean reconstruction of the Model field parser at retail 0x00773170.

extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *left, const char *right );

class AsciiString
{
	public:
	AsciiString( const char *text );
	~AsciiString() { releaseBuffer(); }

	private:
	void releaseBuffer( void );
	void *m_data;
};

class INI
{
public:
	const char *getNextTokenOrNull( const char *separators );
	static bool scanBool( const char *token );

	char m_unreconstructed[ 0x41c ];
	const char *m_separators;
};

namespace _STL
{
template <typename T>
class allocator;

template <typename T, typename Allocator = allocator<T> >
class vector
{
public:
	void push_back( const T &value );
	T *erase( T *first, T *last );
	void clear( void ) { erase( m_start, m_finish ); }

	public:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

class ModelConditionInfo
{
public:
	char m_unreconstructed[ 0x28 ];
	_STL::vector<AsciiString> m_modelNames;
};

// ?parseModel@@YAXPAVINI@@PAX1PBX@Z
static __declspec(noinline) void parseModel( INI *ini, void *instance, void *, const void * )
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	if( !self )
		return;
	const char *model = ini->getNextTokenOrNull( ini->m_separators );
	if( !model )
		return;
	bool keep = false;
	const char *separators = ini->m_separators;
	if( const char *mesh = ini->getNextTokenOrNull( separators ) )
	{
		if( _stricmp( mesh, "ExtraMesh" ) == 0 )
		{
			const char *flag = ini->getNextTokenOrNull( 0 );
			if( flag && INI::scanBool( flag ) )
				keep = true;
		}
	}
	if( !keep )
	{
		AsciiString *finish = self->m_modelNames.m_finish;
		self->m_modelNames.erase( self->m_modelNames.m_start, finish );
	}
	AsciiString name( model );
	self->m_modelNames.push_back( name );
}

void (*volatile parseModelAnchor)( INI *, void *, void *, const void * ) = parseModel;
