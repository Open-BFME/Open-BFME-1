// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>
#include <vector>

struct Rva00196D90Element;

class Dict
{
public:
	Dict( int numPairsToPreAllocate );
	Dict( const Dict &source )
		: m_data( source.m_data )
	{
		if ( m_data != 0 )
			++*(unsigned short *)m_data;
	}

	void *m_data;

private:
	friend struct Rva00196D90Element;
	void releaseData();
};

struct Rva00196D90Element
{
	short m_word0;
	short m_word2;
	short m_word4;
	short m_word6;
	int m_word8;
	Dict m_dict;

	Rva00196D90Element()
		: m_word0( 0 ), m_word2( 0 ), m_word4( 0 ), m_word6( 0 ),
		  m_word8( 0 ), m_dict( 0 )
	{
	}

	Rva00196D90Element( const Rva00196D90Element &source )
		: m_word0( source.m_word0 ), m_word2( source.m_word2 ),
		  m_word4( source.m_word4 ), m_word6( source.m_word6 ),
		  m_word8( source.m_word8 ), m_dict( source.m_dict )
	{
	}

	~Rva00196D90Element()
	{
		m_dict.releaseData();
	}

	Rva00196D90Element &operator=( const Rva00196D90Element &source );
};

namespace _STL
{
	__forceinline Rva00196D90Element *__uninitialized_fill_n(
		Rva00196D90Element *first, unsigned int count,
		const Rva00196D90Element &value, const __false_type &)
	{
		Rva00196D90Element *current = first;
		for ( ; count > 0; --count, ++current )
			new ( current ) Rva00196D90Element( value );
		return current;
	}
}

template _STL::vector<Rva00196D90Element>::vector( unsigned int );
