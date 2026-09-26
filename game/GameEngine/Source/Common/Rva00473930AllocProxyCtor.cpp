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

class Rva00473930
{
public:
	Rva00473930( int flags );

private:
	void initialize( Bool *out, int mode );
	void *m_bfmePtr;
};

#pragma comment(linker, "/alternatename:?initialize@Rva00473930@@AAEXPA_NH@Z=?j_0000e7cd@@YAXXZ")

Rva00473930::Rva00473930( int flags )
{
	Bool ok;

	initialize( &ok, 0 );

	m_bfmePtr = _STL::__new_alloc::allocate( 0x18 );
}
