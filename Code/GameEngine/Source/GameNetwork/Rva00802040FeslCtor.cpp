// cl: /GX-
// FESL browser owner ctor @ 0x802040 (138B). V2ZeroPair +8; twin Buf +0x10/+0x18;
// Arr2 +0x20 allocate(a->m_08) sibling of matched 0x801BD0; Buf::set from
// owner+0x2AC/+0x2B4. Member ctors supply the early eax-zeros; body zeros
// +28/+30/+55/+2C after the lea trio.

struct V2ZeroPair
{
	__forceinline V2ZeroPair() : m_a( 0 ), m_b( 0 ) {}
	int m_a;
	int m_b;
};

class Rva00802040Buf
{
public:
	__forceinline Rva00802040Buf() : m_p( 0 ), m_n( 0 ) {}
	void set( void *p );

	void *m_p;
	int m_n;
};

class Rva00802040Arr
{
public:
	__forceinline Rva00802040Arr() : m_a( 0 ), m_n( 0 ) {}
	void allocate( int n );

	void *m_a;
	int m_n;
};

class Rva00802040Src
{
public:
	char m_pad[8];
	int m_08;
	char m_pad2[0xb4 - 0x0c];
	void *m_b4;
	void *m_b8;
};

class Rva00802040OwnerSrc
{
public:
	char m_pad[0x2ac];
	void *m_2ac;
	char m_pad2[4];
	void *m_2b4;
};

class Rva00802040Owner
{
public:
	__declspec(noinline) Rva00802040Owner( Rva00802040Src *a, Rva00802040OwnerSrc *b );
	virtual ~Rva00802040Owner() {}

	Rva00802040OwnerSrc *m_04;
	V2ZeroPair m_08;
	Rva00802040Buf m_10;
	Rva00802040Buf m_18;
	Rva00802040Arr m_20;
	int m_28;
	int m_2c;
	char m_30;
	char m_pad31[0x24];
	char m_55;
};

Rva00802040Owner::Rva00802040Owner( Rva00802040Src *a, Rva00802040OwnerSrc *b )
{
	int z = 0;
	m_28 = z;
	m_30 = (char)z;
	m_55 = (char)z;
	m_2c = z;
	m_04 = b;
	m_08.m_a = (int)a->m_b8;
	m_08.m_b = (int)a->m_b4;
	m_20.allocate( a->m_08 );
	m_10.set( m_04->m_2ac );
	m_18.set( m_04->m_2b4 );
}
