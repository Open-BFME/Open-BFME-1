// Five 78-byte __cdecl functions with the shape of STLport's
// `__final_insertion_sort`: over a threshold, sort the first sixteen elements
// and hand the remainder to an unguarded pass; under it, sort the whole range.
//
//     ecx = last - first ; ecx &= ~(SIZE-1) ; if ( ecx <= 16*SIZE ) goto small
//     mid = first + 16*SIZE
//     sort( first, mid, comp )
//     tail( mid, last, 0, comp )      <- FOUR arguments; the third is a zero
//     return
//   small: sort( first, last, comp )
//
// WHAT THE `and` MEANS, because it is the whole puzzle.  Masking a pointer
// DIFFERENCE with ~(SIZE-1) looks like source-level rounding and is not: MSVC
// rewrites `(last - first) > 16` on a T* of size SIZE into
// `((last-first) & ~(SIZE-1)) > 16*SIZE`, trading the arithmetic shift the
// signed division would need for a mask.  Read that way the two constants stop
// being independent -- 0xFFFFFFF0 with 0x100 and 0xFFFFFFF8 with 0x80 are the
// SAME source constant 16 at two element sizes, and `jle` being signed is the
// signed ptrdiff_t comparison, not an unsigned one.  Probing the plain
// `last - first > 16` spelling reproduces the mask, the limit and the `lea`.
//
// The fourth argument of the tail call is a hard zero pushed between `last` and
// the comparator.  A dead pointer argument in that position is STLport's
// value-type dummy -- `__unguarded_insertion_sort(first, last, __VALUE_TYPE, comp)`
// -- and the position is the only evidence for it, so it is declared as an
// unnamed pointer of the element type and passed as 0.
//
// TWO AXES: the element size (16 bytes in two rows, 8 in three) and the callee
// pair.  Five distinct pairs; within each row the SMALL branch calls the same
// address as the big branch's first call, which is what makes the two branches
// one function rather than two.
//
// IDENTITY IS NOT RECOVERED.  The real thing is a template instantiation whose
// mangled name encodes the element type and comparator; nothing in these bytes
// names either, so the callees are declared as ordinary functions with
// address-derived names and the comparator is typed only by its WIDTH (one
// dword, passed by value).

class Rva00476880Elem { public: char m_pad[ 16 ]; };
extern void Gen00020D65( Rva00476880Elem *first, Rva00476880Elem *last, void *comp );
extern void Gen00041ABA( Rva00476880Elem *first, Rva00476880Elem *last, Rva00476880Elem *, void *comp );

void Rva00476880( Rva00476880Elem *first, Rva00476880Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Gen00020D65( first, first + 16, comp );
		Gen00041ABA( first + 16, last, 0, comp );
	}
	else
		Gen00020D65( first, last, comp );
}

class Rva00574E70Elem { public: char m_pad[ 16 ]; };
extern void Gen0002591E( Rva00574E70Elem *first, Rva00574E70Elem *last, void *comp );
extern void Gen000235C4( Rva00574E70Elem *first, Rva00574E70Elem *last, Rva00574E70Elem *, void *comp );

void Rva00574E70( Rva00574E70Elem *first, Rva00574E70Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Gen0002591E( first, first + 16, comp );
		Gen000235C4( first + 16, last, 0, comp );
	}
	else
		Gen0002591E( first, last, comp );
}

class Rva00576FF0Elem { public: char m_pad[ 8 ]; };
extern void Gen0001EE39( Rva00576FF0Elem *first, Rva00576FF0Elem *last, void *comp );
extern void Gen000046FB( Rva00576FF0Elem *first, Rva00576FF0Elem *last, Rva00576FF0Elem *, void *comp );

void Rva00576FF0( Rva00576FF0Elem *first, Rva00576FF0Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Gen0001EE39( first, first + 16, comp );
		Gen000046FB( first + 16, last, 0, comp );
	}
	else
		Gen0001EE39( first, last, comp );
}

class Rva009F3CE0Elem { public: char m_pad[ 8 ]; };
extern void Gen009F3A80( Rva009F3CE0Elem *first, Rva009F3CE0Elem *last, void *comp );
extern void Gen009F3050( Rva009F3CE0Elem *first, Rva009F3CE0Elem *last, Rva009F3CE0Elem *, void *comp );

void Rva009F3CE0( Rva009F3CE0Elem *first, Rva009F3CE0Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Gen009F3A80( first, first + 16, comp );
		Gen009F3050( first + 16, last, 0, comp );
	}
	else
		Gen009F3A80( first, last, comp );
}

class Rva009F3D30Elem { public: char m_pad[ 8 ]; };
extern void Gen009F3AC0( Rva009F3D30Elem *first, Rva009F3D30Elem *last, void *comp );
extern void Gen009F30B0( Rva009F3D30Elem *first, Rva009F3D30Elem *last, Rva009F3D30Elem *, void *comp );

void Rva009F3D30( Rva009F3D30Elem *first, Rva009F3D30Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Gen009F3AC0( first, first + 16, comp );
		Gen009F30B0( first + 16, last, 0, comp );
	}
	else
		Gen009F3AC0( first, last, comp );
}

