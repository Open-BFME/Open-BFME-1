// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB
// stlport

#include <string.h>
#include <vector>

template <typename T> class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

struct Rva00369860Pair
{
	int m_first;
	int m_second;
};

class Rva00368C10Mask
{
public:
	Rva00368C10Mask() : m_bits( 0 ) {}

private:
	unsigned int m_bits;
};

class Rva00369860Values10
{
public:
	Rva00369860Values10() { memset( m_values, 0, sizeof( m_values ) ); }

private:
	int m_values[ 10 ];
};

class Rva00369860State
{
public:
	Rva00369860State();
	void reset( int mode );

private:
	std::vector<Rva00369860Pair> m_pairs;
	Rva00368C10Mask m_mask;
	StringBase<char> m_name;
	int m_mode;
	int m_field18;
	Rva00369860Values10 m_firstValues;
	Rva00369860Values10 m_secondValues;
	int m_primaryValues[ 3 ];
	int m_secondaryValues[ 3 ];
	int m_unreconstructed84;
	int m_unreconstructed88;
	bool m_flag8C;
};

Rva00369860State::Rva00369860State() :
	m_unreconstructed84( 0 ),
	m_unreconstructed88( 0 )
{
	reset( 0 );
}
