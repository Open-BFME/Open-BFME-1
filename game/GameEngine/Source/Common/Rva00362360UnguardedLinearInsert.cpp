// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

// Retail 0x00362360 is the STLport __unguarded_linear_insert for the 0xB4-byte
// heap element. Both of its element operations go out of line, and both targets
// are already matched elsewhere, so this file declares them instead of inventing
// the element's own ??4/??1 spellings that nothing defines:
//   * the two `push src; mov ecx,dst; call` sites reach the five-byte ILT thunk
//     0x000470F0, whose jump target 0x00361B30 is
//     ?copyFrom@LivingWorldArmy@@QAEXABV1@@Z (LivingWorldArmyAssign.cpp);
//   * the scope-exit `lea ecx,&value; call` site reaches the five-byte ILT thunk
//     0x000257ED, whose jump target 0x00360F90 is ??1BfmeOwnVUM@@QAE@XZ
//     (BfmeConv1645.cpp).
// LivingWorldArmy and BfmeOwnVUM agree field for field on this 0xB4 record
// (pointer at +4, +0x4C, +0x78, +0xAC and +0xB0 alike), which is what ties the
// two call targets to the same element the ledger row names
// Rva00364980HeapElement: BfmeOwnVUM supplies the element's only non-trivial
// member, so declaring it first gives the parameter the destructor that produces
// the SEH scope frame retail opens with.
class LivingWorldArmy
{
public:
	void copyFrom( const LivingWorldArmy &other );
};

// Retail calls copyFrom through the five-byte ILT thunk 0x000470F0.
extern void j_000470f0();
typedef void ( LivingWorldArmy::*CopyFromThunk )( const LivingWorldArmy &other );

class BfmeOwnVUM
{
public:
	~BfmeOwnVUM();

private:
	void *m_vptr;
	char m_bfme04[ 4 ];
	char m_bfme08[ 0x44 ];
	char m_bfme4c[ 4 ];
	char m_bfme50[ 0x28 ];
	char m_bfme78[ 4 ];
	char m_bfme7c[ 0x30 ];
	char m_bfmeac[ 4 ];
	char m_bfmeb0[ 4 ];
};

struct Rva00364980HeapElement
{
	float priority() const
	{
		return *(const float *)( (const char *)this + 8 );
	}

	BfmeOwnVUM m_bfmeOwner;
};

struct Rva00364980HeapCompare
{
	bool operator()( const Rva00364980HeapElement &left,
		const Rva00364980HeapElement &right ) const
	{
		return left.priority() > right.priority();
	}

	void *m_state;
};

void rva00362360UnguardedLinearInsert( Rva00364980HeapElement *last,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare )
{
	union { void ( *fn )(); CopyFromThunk call; } copyFrom = { j_000470f0 };
	Rva00364980HeapElement *next = last;
	--next;
	while( compare( value, *next ) )
	{
		( ((LivingWorldArmy *)last)->*copyFrom.call )( *(const LivingWorldArmy *)next );
		last = next;
		--next;
	}
	( ((LivingWorldArmy *)last)->*copyFrom.call )( *(const LivingWorldArmy *)&value );
}