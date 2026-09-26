// cl: /DNDEBUG /MD /EHsc
// stlport
// STLport payload copy constructor at retail 0x006071C0.

#include <map>
#include <new>

struct Gen_t_00607280_k4
{
	int a[ 1 ];
};

struct Gen_t_00607280_p12cd
{
	int a[ 3 ];
};

struct Rva006071C0Pod
{
	char m_bytes[ 0x28 ];
};

struct Rva00606A80Member
{
	Rva00606A80Member( const Rva00606A80Member &other );
	~Rva00606A80Member();

	char m_body[ 0x1B4 ];
};

#pragma comment(linker, "/alternatename:??0Rva00606A80Member@@QAE@ABU0@@Z=?j_0001ff64@@YAXXZ")

struct Rva00606E60Member
{
	Rva00606E60Member( const Rva00606E60Member &other );
	~Rva00606E60Member();

	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00606E60Member@@QAE@ABU0@@Z=?j_00032515@@YAXXZ")

namespace _STL
{
	template<> struct pair<const Gen_t_00607280_k4, Gen_t_00607280_p12cd>
	{
		Rva006071C0Pod m_pod;
		Rva00606A80Member m_member28;
		Rva00606E60Member m_member1DC;
		int m_field1E8;
		unsigned char m_field1EC;
		char m_padding1ED[ 3 ];

		pair( const pair &other )
			: m_pod( other.m_pod ),
			  m_member28( other.m_member28 ),
			  m_member1DC( other.m_member1DC )
		{
			m_field1E8 = other.m_field1E8;
			m_field1EC = other.m_field1EC;
		}
	};
}

typedef _STL::pair<const Gen_t_00607280_k4, Gen_t_00607280_p12cd>
	Gen00607280Pair;

Gen00607280Pair *copy_gen_00607280_pair( Gen00607280Pair *result,
	const Gen00607280Pair &other )
{
	return new ( result ) Gen00607280Pair( other );
}
