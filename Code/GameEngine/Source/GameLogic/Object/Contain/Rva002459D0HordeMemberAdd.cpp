// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;

class Drawable
{
public:
	void setSelectable( Bool selectable );
};

class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable();

	unsigned char m_pad004[ 0x74 - 4 ];
	Int m_id;
};

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU( void **what );

	unsigned char m_body[ 0x0c ];
};

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

class Rva002459D0Base
{
public:
#define BASE_SLOT( N ) virtual void slot##N();
	BASE_SLOT( 00 ) BASE_SLOT( 01 ) BASE_SLOT( 02 ) BASE_SLOT( 03 )
	BASE_SLOT( 04 ) BASE_SLOT( 05 ) BASE_SLOT( 06 ) BASE_SLOT( 07 )
	BASE_SLOT( 08 ) BASE_SLOT( 09 ) BASE_SLOT( 10 ) BASE_SLOT( 11 )
	BASE_SLOT( 12 ) BASE_SLOT( 13 ) BASE_SLOT( 14 ) BASE_SLOT( 15 )
	BASE_SLOT( 16 ) BASE_SLOT( 17 ) BASE_SLOT( 18 ) BASE_SLOT( 19 )
	BASE_SLOT( 20 ) BASE_SLOT( 21 ) BASE_SLOT( 22 ) BASE_SLOT( 23 )
	BASE_SLOT( 24 ) BASE_SLOT( 25 ) BASE_SLOT( 26 ) BASE_SLOT( 27 )
	BASE_SLOT( 28 ) BASE_SLOT( 29 ) BASE_SLOT( 30 ) BASE_SLOT( 31 )
	BASE_SLOT( 32 ) BASE_SLOT( 33 )
	virtual void onMember( Object *member );
#undef BASE_SLOT
};

class Rva002459D0View
{
public:
#define VIEW_SLOT( N ) virtual void slot##N();
	VIEW_SLOT( 00 ) VIEW_SLOT( 01 ) VIEW_SLOT( 02 ) VIEW_SLOT( 03 )
	VIEW_SLOT( 04 ) VIEW_SLOT( 05 ) VIEW_SLOT( 06 ) VIEW_SLOT( 07 )
	VIEW_SLOT( 08 ) VIEW_SLOT( 09 ) VIEW_SLOT( 10 ) VIEW_SLOT( 11 )
	virtual void updateMember( Object *member );
#undef VIEW_SLOT
};

class Rva002459D0Owner
{
public:
	void rva002459d0( Object *member, Int *memberID, Int index );

private:
	unsigned char m_pad000[ 0x20 ];
	Rva002459D0Base m_base;
	unsigned char m_pad024[ 0xc0 ];
	Rva002459D0View m_view;
	unsigned char m_pad0e8[ 0x38 ];
	BfmeSubDSU m_memberIndices;
	unsigned char m_pad12c[ 0xac ];
	_STL::vector<Rva00244A80Element> m_memberStates;

	void applyMemberFormationState( Object *member );
};

// Each declaration is a real retail thunk.  The source names stay local to
// this address-qualified reconstruction, while the calls retain their retail
// targets and thiscall ABIs.
#pragma comment(linker, "/alternatename:??0Rva00244A80Element@@QAE@XZ=?j_0001aacd@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00244A80Element@@QAE@ABV0@@Z=?j_000128dc@@YAXXZ")
#pragma comment(linker, "/alternatename:?setSelectable@Drawable@@QAEX_N@Z=?j_0001766b@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyMemberFormationState@Rva002459D0Owner@@QAEXPAVObject@@@Z=?j_0000efa2@@YAXXZ")

// ?rva002459d0@Rva002459D0Owner@@QAEXPAVObject@@PAHH@Z
void Rva002459D0Owner::rva002459d0(
	Object *member, Int *memberID, Int index )
{
	Int key = member->m_id;
	*memberID = key;
	Int *storedIndex = (Int *)m_memberIndices.bfmeTwoDSU(
		(void **)&key );
	*storedIndex = index;

	while (m_memberStates.size() <= (unsigned int)index)
	{
		Rva00244A80Element element;
		m_memberStates.push_back( element );
	}

	member->getDrawable()->setSelectable( false );
	m_base.onMember( member );
	member->getDrawable()->setSelectable( true );
	m_view.updateMember( member );
	applyMemberFormationState( member );
}
