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

#pragma comment(linker, "/alternatename:?initialize@Rva00473900@@AAEXPA_NH@Z=?j_0000cdb0@@YAXXZ")

Rva00473900::Rva00473900( int flags )
{
	Bool ok;

	initialize( &ok, 0 );

	m_bfmePtr = _STL::__new_alloc::allocate( 0x18 );
}
