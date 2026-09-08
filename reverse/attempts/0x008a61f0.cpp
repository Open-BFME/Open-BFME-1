// ??1Rva008A6410HeaderedDeleting@@UAE@XZ
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x008A61F0 (163 B). Same Q4Base00D35D68 destructor
// family as Q4VptrPairDtors.cpp (own vtable 0x11366E0, mid vtable
// 0x1136058, base vtable 0x1135D68; notify(0,0); subobject dtor at +8 is
// the SAME target 0x0089CC70 pinned there as Q4Sub00C9CC70; flag at +0x18
// zeroed) but with two extra ref-counted string releases at +0x20 and +0x24
// (word refcount at the pointee, dec, release through the pool table at
// 0x01337A30 index 1 when it drops to zero -- the same table
// HeaderedDeleteDestructors.cpp's Rva008B01E0Reference already reads).
// This class's own name is address-derived; Rva008A6410HeaderedDeleting
// already names an unrelated, already-pinned class so it is not reused here.

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	void notify( int a, int b );
	~Q4Base00D35D68() { }
};

extern void ( __cdecl **Rva01337A30ReleaseTable )( void * );

struct Rva008A6410RefCount
{
	unsigned short m_count;
};

static void Rva008A6410ReleaseRef( Rva008A6410RefCount *ref )
{
	--ref->m_count;
	unsigned short count = ref->m_count;
	if( count != 0 )
		return;
	if( count == 0 )
		Rva01337A30ReleaseTable[ 1 ]( ref );
}

// address-derived intermediate: own vtable folds to the family's mid table
// 0x1136058; owns the subobject-at-+8 and the flag, and its user body is the
// same notify(0,0)/flag=0 pair every Q4_TABLE_DTOR sibling in
// Q4VptrPairDtors.cpp uses.
class Rva008A6410Middle : public Q4Base00D35D68
{
public:
	virtual void v3();
	virtual void v4();
	virtual void v5();
	__forceinline virtual ~Rva008A6410Middle()
	{
		notify( 0, 0 );
		m_flag = 0;
	}

	char m_gap0[ 8 - 4 ];
	Q4Sub00C9CC70 m_sub;				// +0x08
	char m_gap1[ 0x18 - 9 ];
	int m_flag;					// +0x18
};

class Rva008A6410HeaderedDeleting : public Rva008A6410Middle
{
public:
	virtual ~Rva008A6410HeaderedDeleting();

private:
	char m_gap2[ 0x20 - 0x1C ];
	Rva008A6410RefCount *m_ref20;			// +0x20
	Rva008A6410RefCount *m_ref24;			// +0x24
};

// ??1Rva008A61F0@@UAE@XZ
Rva008A6410HeaderedDeleting::~Rva008A6410HeaderedDeleting()
{
	Rva008A6410ReleaseRef( m_ref24 );
	Rva008A6410ReleaseRef( m_ref20 );
}
