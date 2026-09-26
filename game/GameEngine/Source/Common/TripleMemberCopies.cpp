// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x00138BA0 and 0x00146B10 (93 bytes each) are the copy loops of
// Open2Copies.cpp over a 36-byte record made of three 12-byte members, each assigned
// through its own out-of-line operator= (three distinct callees per body, autopinned).
// Address-tagged records.

class Rva00138BA0A { public: Rva00138BA0A &operator=( const Rva00138BA0A &o ); int m_v[3]; };
class Rva00138BA0B { public: Rva00138BA0B &operator=( const Rva00138BA0B &o ); int m_v[3]; };
class Rva00138BA0C { public: Rva00138BA0C &operator=( const Rva00138BA0C &o ); int m_v[3]; };

class Rva00138BA0Elem
{
public:
	Rva00138BA0A m_at00;
	Rva00138BA0B m_at0c;
	Rva00138BA0C m_at18;
};

Rva00138BA0Elem *Rva00138BA0Copy( Rva00138BA0Elem *first, Rva00138BA0Elem *last, Rva00138BA0Elem *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

class Rva00146B10A { public: Rva00146B10A &operator=( const Rva00146B10A &o ); int m_v[3]; };
class Rva00146B10B { public: Rva00146B10B &operator=( const Rva00146B10B &o ); int m_v[3]; };
class Rva00146B10C { public: Rva00146B10C &operator=( const Rva00146B10C &o ); int m_v[3]; };

class Rva00146B10Elem
{
public:
	Rva00146B10A m_at00;
	Rva00146B10B m_at0c;
	Rva00146B10C m_at18;
};

Rva00146B10Elem *Rva00146B10Copy( Rva00146B10Elem *first, Rva00146B10Elem *last, Rva00146B10Elem *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}
