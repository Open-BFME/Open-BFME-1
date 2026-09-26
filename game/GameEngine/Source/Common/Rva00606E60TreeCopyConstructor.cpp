// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport red-black-tree copy constructor at retail 0x00606E60.

#include <map>

class AsciiString
{
public:
	AsciiString();
	AsciiString( const AsciiString &other );
	~AsciiString();
	AsciiString &operator=( const AsciiString &other );
	int compare( const AsciiString &other ) const;
private:
	void *m_data;
};

inline bool operator<( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) < 0;
}

class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS( const AudioEventRTS &other );
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=( const AudioEventRTS &other );
private:
	unsigned char m_data[ 0x6C ];
};

typedef _STL::pair<const AsciiString, AudioEventRTS> Rva00606E60Pair;
typedef _STL::_Rb_tree<AsciiString, Rva00606E60Pair,
	_STL::_Select1st<Rva00606E60Pair>, _STL::less<AsciiString>,
	_STL::allocator<Rva00606E60Pair> > Rva00606E60Tree;

template class _STL::_Rb_tree<AsciiString, Rva00606E60Pair,
	_STL::_Select1st<Rva00606E60Pair>, _STL::less<AsciiString>,
	_STL::allocator<Rva00606E60Pair> >;
