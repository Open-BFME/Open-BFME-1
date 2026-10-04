// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;
typedef bool Bool;

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( UnsignedInt bytes );
};
}

class Rva00473900
{
public:
	Rva00473900( int flags );

private:
	void initialize( Bool *out, int mode );
	void *m_bfmePtr;
};

extern void j_0000cdb0();

Rva00473900::Rva00473900( int flags )
{
	Bool ok;

	typedef void (Rva00473900::*Init)( Bool *, int );
	union { void (*fn)(); Init call; } init = { j_0000cdb0 };
	( this->*init.call )( &ok, 0 );

	m_bfmePtr = _STL::__new_alloc::allocate( 0x18 );
}
