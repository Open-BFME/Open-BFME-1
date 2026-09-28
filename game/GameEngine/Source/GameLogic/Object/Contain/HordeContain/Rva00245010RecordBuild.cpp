// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Open-BFME: HordeContain.cpp body at 0x00245010 (its GameLogicRandomValue
// calls carry HordeContain.cpp lines 0x4fb and 0x4fe). "this" is the object
// that owns Rva00244E60's record vector at +0x12c (0x00244E60 is called on it
// directly) and Rva00244F00Owner's method 0x00244F00 (also called directly on
// it); 0x002459D0 witnesses the 28-byte Rva00244A80Element vector at +0x1d8.
// The real class and method names are unproven, so the body keeps the
// address-qualified FormationBuild00245010::build name its earlier banked
// attempts used (it builds one record per rank formation position).

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

Int GetGameLogicRandomValue( Int lo, Int hi, char *file, Int line );

// landed: game/GameEngine/Source/GameLogic/AI/Rva00244E60.cpp
struct BfmeRva44E60Input
{
	Int m_first;
	Int m_second;
};

// 0x00244E60 copies its input pair into m_first/m_second; here the same
// slots take a jittered position, so they are declared as Real.
struct BfmeRva44E60Record
{
	BfmeRva44E60Record( void );
	BfmeRva44E60Record( const BfmeRva44E60Record &other );

	Int m_value;
	Real m_first;
	Real m_second;
	Real m_third;
};

// landed: game/GameEngine/Source/GameLogic/Object/Contain/Rva002459D0HordeMemberAdd.cpp
class Rva00244A80Element
{
public:
	Rva00244A80Element();
	Rva00244A80Element( const Rva00244A80Element &other );
	Rva00244A80Element &operator=( const Rva00244A80Element &other );

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char m_10;
	int m_14;
	int m_18;
};

struct Rank00245010
{
	Int field000;
	Int field004;
	_STL::vector<Coord3D> m_positions;
};

// Module data reached through this+4; 0x00244F00 reads its vector at +0x2a4.
struct Rva0024SourceHolder
{
	char pad000[ 0x224 ];
	_STL::vector<Rank00245010 *> m_ranks;
	char pad230[ 0x268 - 0x230 ];
	Coord2D m_jitter;
	char pad270[ 0x28c - 0x270 ];
	_STL::vector<Int> m_vector28C;
	BfmeRva44E60Input m_input298;
	char pad2A0[ 0x2a4 - 0x2a0 ];
	char *m_begin;
	char *m_end;
	char *m_capacity;
	_STL::vector<Int> m_vector2B0;
};

class Rva00244E60
{
public:
	void add( BfmeRva44E60Input *input, Int value, Int *output );

	void *m_vtable000;
	Rva0024SourceHolder *m_moduleData;
	char pad008[ 0x38 - 0x08 ];
	_STL::list<Int> m_list038;
	char pad03C[ 0x118 - 0x3c ];
	Int field118;
	char pad11C[ 0x12c - 0x11c ];
	_STL::vector<BfmeRva44E60Record> m_records;
};

// landed: game/GameEngine/Source/GameLogic/Object/Contain/Rva00244F00RecordBuild.cpp
class Rva00244F00Owner : public Rva00244E60
{
public:
	void rva00244f00( Rva0024SourceHolder *src );
};

class FormationBuild00245010 : public Rva00244F00Owner
{
public:
	void build( Int arg );
	void rva0023b9f0();

private:
	_STL::list<Int> m_list138;
	Bool m_flag13C;
	char pad13D[ 0x1b8 - 0x13d ];
	Int field1B8;
	char pad1BC[ 0x1d8 - 0x1bc ];
	_STL::vector<Rva00244A80Element> m_memberStates;
};

// ?build@FormationBuild00245010@@QAEXH@Z
void FormationBuild00245010::build( Int arg )
{
	Rva0024SourceHolder *data = m_moduleData;

	const _STL::vector<Rank00245010 *> &ranks = data->m_ranks;

	Int total = 0;
	UnsignedInt count = ranks.size();
	for ( UnsignedInt i = 0; i < count; ++i )
		total += ranks[ i ]->m_positions.size();

	m_records.reserve( total );
	m_memberStates.reserve( total );

	Coord2D jitter = data->m_jitter;
	for ( UnsignedInt r = 0; r < ranks.size(); ++r )
	{
		Rank00245010 *rank = ranks[ r ];
		Int value = rank->field000;
		const _STL::vector<Coord3D> &positions = rank->m_positions;
		for ( UnsignedInt j = 0; j < positions.size(); ++j )
		{
			const Coord3D &pos = positions[ j ];
			BfmeRva44E60Record record;
			record.m_first = pos.x;
			record.m_second = pos.y;
			record.m_value = value;
			if ( jitter.x > 0.0f )
				record.m_first += GetGameLogicRandomValue( (Int)-jitter.x, (Int)jitter.x,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x4fb );
			if ( jitter.y > 0.0f )
				record.m_second += GetGameLogicRandomValue( (Int)-jitter.y, (Int)jitter.y,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp", 0x4fe );
			record.m_third = positions[ j ].z;
			m_records.push_back( record );

			if ( arg || ( m_list038.empty() && field118 == 0 ) )
			{
				m_list138.push_back( m_records.size() - 1 );
				Rva00244A80Element element;
				m_memberStates.push_back( element );
			}
		}
	}

	if ( !data->m_vector28C.empty() )
		add( &data->m_input298, 0, &field1B8 );
	if ( !data->m_vector2B0.empty() )
		rva00244f00( data );
	rva0023b9f0();
	m_flag13C = true;
}
