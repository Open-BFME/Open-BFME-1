// cl: /DNDEBUG /MD /EHsc
//
// Two constructors that take two refcounted handles BY VALUE, 0x004C5C30 and
// 0x004C5D20.  The pair is byte-identical outside its EH table, so one
// reconstruction serves both.
//
// The shape is the whole finding.  Each argument is one pointer: it is stored,
// then `inc [p+4]` takes a reference -- that is the MEMBER's copy
// construction.  Afterwards each is released again with `dec / jg / call
// [vptr]` -- that is the by-value ARGUMENT being destroyed, which is also
// where the SEH frame and its two unwind states come from.  The releases run
// in the same order as the copies, not reversed.
//
// `dec edx / mov eax,edx / test eax,eax / jg` is `--refs <= 0`, not `== 0`:
// the sign test is what a `<=` on a signed counter compiles to.

class Open2Counted
{
public:
	virtual void release( int deleting );

	int m_refs;
};

class Open2Handle
{
public:
	Open2Handle( const Open2Handle &other ) : m_held( other.m_held )
	{
		if( m_held != 0 )
			++m_held->m_refs;
	}

	~Open2Handle()
	{
		if( m_held != 0 && --m_held->m_refs <= 0 )
			m_held->release( 1 );
	}

	Open2Counted *m_held;
};

class Rva004C5C30
{
public:
	Rva004C5C30( Open2Handle first, Open2Handle second );

	Open2Handle m_first;
	Open2Handle m_second;
};

// @??0Rva004C5C30@@QAE@VOpen2Handle@@0@Z 0x004C5C30
Rva004C5C30::Rva004C5C30( Open2Handle first, Open2Handle second )
	: m_first( first ), m_second( second )
{
}

class Rva004C5D20
{
public:
	Rva004C5D20( Open2Handle first, Open2Handle second );

	Open2Handle m_first;
	Open2Handle m_second;
};

// @??0Rva004C5D20@@QAE@VOpen2Handle@@0@Z 0x004C5D20
Rva004C5D20::Rva004C5D20( Open2Handle first, Open2Handle second )
	: m_first( first ), m_second( second )
{
}
