// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Gen_t_00776240_p128pod copy constructor at retail 0x00772E10.

#include <new>

template <typename T>
class StringBase
{
public:
	StringBase( const StringBase<T> &other );
	~StringBase();

private:
	void *m_data;
};

class AsciiStringVX
{
public:
	AsciiStringVX( const AsciiStringVX &other )
		: m_base(
			*( const StringBase<char> * )( &other ) )
	{
	}
	~AsciiStringVX()
	{
	}

private:
	StringBase<char> m_base;
};

struct Raw10
{
	unsigned int words[ 10 ];
};

struct Rva00776240Vector2C
{
	Rva00776240Vector2C( const Rva00776240Vector2C &other );
	~Rva00776240Vector2C();
	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240Vector2C@@QAE@ABU0@@Z=?j_0003edfb@@YAXXZ")

struct Rva00776240List50
{
	Rva00776240List50( const Rva00776240List50 &other );
	~Rva00776240List50();
	char m_body[ 0x04 ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240List50@@QAE@ABU0@@Z=?j_000296e5@@YAXXZ")

struct Rva00776240Vector54
{
	Rva00776240Vector54( const Rva00776240Vector54 &other );
	~Rva00776240Vector54();
	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240Vector54@@QAE@ABU0@@Z=?j_00046141@@YAXXZ")

struct Rva00776240Vector60
{
	Rva00776240Vector60( const Rva00776240Vector60 &other );
	~Rva00776240Vector60();
	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240Vector60@@QAE@ABU0@@Z=?j_000027f2@@YAXXZ")

struct Rva00776240Vector70
{
	Rva00776240Vector70( const Rva00776240Vector70 &other );
	~Rva00776240Vector70();
	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240Vector70@@QAE@ABU0@@Z=?j_00014547@@YAXXZ")

struct Rva00776240Vector70Holder : public Rva00776240Vector70
{
	Rva00776240Vector70Holder(
		const Rva00776240Vector70Holder &other )
		: Rva00776240Vector70( other )
	{
	}
	~Rva00776240Vector70Holder()
	{
	}
};

struct Rva00776240Field7C
{
	Rva00776240Field7C();
	~Rva00776240Field7C();
	Rva00776240Field7C &operator=( const Rva00776240Field7C &other );
	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00776240Field7C@@QAE@XZ=?j_00018647@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00776240Field7C@@QAE@XZ=?j_000455e8@@YAXXZ")
#pragma comment(linker, "/alternatename:??4Rva00776240Field7C@@QAEAAU0@ABU0@@Z=?j_0001c288@@YAXXZ")

struct Rva00776240ByteAC
{
	Rva00776240ByteAC( const Rva00776240ByteAC &other )
		: m_value( other.m_value )
	{
	}

	unsigned char m_value;
};

struct Rva00776240FieldB0
{
	Rva00776240FieldB0()
	{
		m_words[ 0 ] = 0;
		m_words[ 1 ] = 0;
		m_words[ 2 ] = 0;
	}
	~Rva00776240FieldB0();

	unsigned int m_words[ 3 ];
};

struct Gen_t_00776240_p128pod : public StringBase<char>
{
	Gen_t_00776240_p128pod( const Gen_t_00776240_p128pod &other );

	Raw10 m_raw;
	Rva00776240Vector2C m_vector2C;
	unsigned int m_dword38;
	unsigned int m_dword3C;
	unsigned char m_byte40;
	unsigned int m_dword44;
	AsciiStringVX m_string48;
	unsigned int m_dword4C;
	Rva00776240List50 m_list50;
	Rva00776240Vector54 m_vector54;
	Rva00776240Vector60 m_vector60;
	unsigned char m_byte6C;
	char m_padding6D[ 3 ];
	Rva00776240Vector70Holder m_vector70;
	Rva00776240Field7C m_vector7C[ 4 ];
	Rva00776240ByteAC m_byteAC;
	Rva00776240FieldB0 m_fieldB0;
};

Gen_t_00776240_p128pod::Gen_t_00776240_p128pod(
	const Gen_t_00776240_p128pod &other )
	: StringBase<char>( other ),
	  m_raw( other.m_raw ),
	  m_vector2C( other.m_vector2C ),
	  m_dword38( other.m_dword38 ),
	  m_dword3C( other.m_dword3C ),
	  m_byte40( other.m_byte40 ),
	  m_dword44( other.m_dword44 ),
	  m_string48( other.m_string48 ),
	  m_dword4C( other.m_dword4C ),
	  m_list50( other.m_list50 ),
	  m_vector54( other.m_vector54 ),
	  m_vector60( other.m_vector60 ),
	  m_byte6C( other.m_byte6C ),
	  m_vector70( other.m_vector70 ),
	  m_byteAC( other.m_byteAC ),
	  m_fieldB0()
{
	for ( int i = 0; i < 4; ++i )
	{
		m_vector7C[ i ] = other.m_vector7C[ i ];
	}
}

Gen_t_00776240_p128pod *copy_gen_00776240(
	Gen_t_00776240_p128pod *result,
	const Gen_t_00776240_p128pod &other )
{
	return new ( result ) Gen_t_00776240_p128pod( other );
}
