// cl: /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: identity from the landed sibling call at 0x00244E60
// (Rva00244E60.cpp), whose add(BfmeRva44E60Input*, Int, Int*) is called
// here directly on "this" (this object is-a Rva00244E60, same address, no
// offset), plus the global registry lookup TheRegistry->bfmeFind975D and
// the pinned STLport vector<POD4> overflow-insert helper already used
// elsewhere in this tree under the shared Gen_t_0023db70_m4pod proxy type.
// The source vector's element type and this object's real class beyond
// Rva00244E60's own declared 0x138 bytes are unproven, so both stay
// address-qualified.

#define _STLP_USE_STATIC_LIB 1
#include <vector>

typedef int Int;

// landed: Code/GameEngine/Source/GameLogic/Object/Contain/Rva00244E60.cpp
struct BfmeRva44E60Input
{
	Int m_first;
	Int m_second;
};

struct BfmeRva44E60Record
{
	BfmeRva44E60Record( void );
	BfmeRva44E60Record( const BfmeRva44E60Record &other );

	Int m_value;
	Int m_first;
	Int m_second;
	Int m_unused;
};

class Rva00244E60
{
public:
	void add( BfmeRva44E60Input *input, Int value, Int *output );

	char m_head[ 0x12c ];
	_STL::vector<BfmeRva44E60Record> m_records;
};

// generic 4-byte POD proxy already used to reach the shared STLport
// vector<POD4> instantiation (Code/gen_small/fam_017.cpp)
struct Gen_t_0023db70_m4pod { Int a[ 1 ]; };
bool operator==( const Gen_t_0023db70_m4pod &, const Gen_t_0023db70_m4pod & );
bool operator<( const Gen_t_0023db70_m4pod &, const Gen_t_0023db70_m4pod & );

// pinned reverse/symbols.csv: ?bfmeFind975D@BfmeFind975D@@QAEPAXH@Z @ 0x00028560
class BfmeFind975D
{
public:
	void *bfmeFind975D( Int arg );
};
extern BfmeFind975D *Rva0020AA00TheRegistry;

struct Rva0024SourceHolder
{
	char m_pad0[ 0x2a4 ];
	char *m_begin;
	char *m_end;
};

struct Rva00244F00Node
{
	Int a;
	Int b;
};

class Rva00244F00Owner : public Rva00244E60
{
public:
	void rva00244f00( Rva0024SourceHolder *src );

private:
	char m_gap138[ 0x1c0 - 0x138 ];
	_STL::vector<Gen_t_0023db70_m4pod> m_nodes;
};

// ?rva00244f00@Rva00244F00Owner@@QAEXPAURva0024SourceHolder@@@Z
void Rva00244F00Owner::rva00244f00( Rva0024SourceHolder *src )
{
	unsigned int i = 0;
	if ( (unsigned int)( (Int)( src->m_end - src->m_begin ) >> 2 ) <= 0 )
		return;

	do
	{
		void *raw = ::operator new( 8 );
		Rva00244F00Node *node;
		if ( raw )
		{
			( (Rva00244F00Node *)raw )->a = 0;
			( (Rva00244F00Node *)raw )->b = -1;
			node = (Rva00244F00Node *)raw;
		}
		else
		{
			node = 0;
		}

		add( (BfmeRva44E60Input *)( *(char **)( src->m_begin + i * 4 ) + 4 ), 0, &node->b );

		Int idx = (Int) * (char **)( src->m_begin + i * 4 );
		node->a = (Int)Rva0020AA00TheRegistry->bfmeFind975D( idx );

		m_nodes.push_back( *(Gen_t_0023db70_m4pod *)&node );

		++i;
	} while ( i < (unsigned int)( (Int)( src->m_end - src->m_begin ) >> 2 ) );
}
