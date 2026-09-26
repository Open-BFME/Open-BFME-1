// cl: /DNDEBUG /MD /GX- /D_STLP_USE_STATIC_LIB
// stlport

// Twelve frameless destructors whose whole body is one inlined
// `_STL::vector<T>` teardown.  Two mnemonic families land here: the
// shift-divide group anchored at 0x0006A3C0 (element sizes that are powers of
// two) and the magic-multiply group anchored at 0x001361F0 (element sizes that
// are not).  Same source shape; the difference is entirely the divide the
// compiler picks for `end_of_storage - start`.
//
// WHAT THE BYTES SHOW.
//
//   mov edx,[ecx+OFF]        ; _M_start
//   test edx,edx / je out    ; STLport's own "was anything allocated" guard
//   mov eax,[ecx+OFF+8]      ; _M_end_of_storage -- the THIRD word, so the
//   sub eax,edx              ;   member between them (_M_finish) is skipped,
//   <divide by sizeof(T)>    ;   which is what fixes the layout as a vector
//   <multiply by sizeof(T)>  ;   rather than any two-pointer pair
//   cmp eax,0x80 / jbe small
//   push edx / call <free> / add esp,4 / ret
// small:
//   push eax / push edx / call <pool free> / add esp,8 / ret
//
// The `sar`/`shl` (or `imul` magic / `imul sizeof`) round-trip is the compiler
// turning a pointer difference back into a byte count; NOTHING in the source
// spells it, and the constant it multiplies by IS sizeof(T).  That constant --
// 16, 4, 236, 136, 220, 528 -- is the only thing these bodies say about the
// element type.  It does not say what the elements are, only how wide.
//
// The 0x80 threshold and the two-callee split are STLport's node allocator
// (`_MAX_BYTES`), not application code: they come from the vendored header, so
// they are reproduced by including it rather than by hand.  An earlier attempt
// at this shape with a hand-rolled replica of the container is exactly the
// mistake this file avoids.
//
// NO STACK FRAME AND NO EH STATE.  That is why the first line asks for /GX-:
// with exceptions on, MSVC wraps the deallocation in unwind bookkeeping and
// the body stops being 46 (or 65) bytes.  `-D_STLP_NO_EXCEPTIONS` does not
// reach this shape.
//
// IDENTITY IS NOT RECOVERED.  Each owner class is named for the RVA of its
// destructor and holds filler up to the vector's offset; the filler is not a
// claim that anything in particular lives there, only that the vector starts
// where the loads say.  Element structs are named for their SIZE because size
// is all the bytes give.  Where two owners have the same offset and the same
// element size their destructors are byte-identical (0x00587180 / 0x005871C0,
// 0x000D1980 / 0x00370D60, and the three 236-byte owners); they are kept as
// separate classes because nothing in the bytes merges them.

#include <vector>

struct GenElem4   { int m_words[1]; };
struct GenElem16  { int m_words[4]; };
struct GenElem136 { int m_words[34]; };
struct GenElem220 { int m_words[55]; };
struct GenElem236 { int m_words[59]; };
struct GenElem528 { int m_words[132]; };

#define BFME_VECTOR_OWNER( NAME, LEAD, ELEM )                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		char m_lead[ LEAD ];                                              \
		_STL::vector< ELEM > m_vector;                                    \
	};                                                                    \
	NAME::~NAME() {}

#define BFME_VECTOR_OWNER_HEAD( NAME, ELEM )                              \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		~NAME();                                                          \
		_STL::vector< ELEM > m_vector;                                    \
	};                                                                    \
	NAME::~NAME() {}

// ------------------------------------------------ family anchored at 0x0006A3C0

BFME_VECTOR_OWNER( Rva0006A3C0, 0x08, GenElem16 )
BFME_VECTOR_OWNER( Rva000D1980, 0x04, GenElem4 )
BFME_VECTOR_OWNER( Rva00370D60, 0x04, GenElem4 )
BFME_VECTOR_OWNER( Rva00587140, 0x10, GenElem4 )
BFME_VECTOR_OWNER( Rva00587180, 0x14, GenElem4 )
BFME_VECTOR_OWNER( Rva005871C0, 0x14, GenElem4 )

// ------------------------------------------------ family anchored at 0x001361F0

BFME_VECTOR_OWNER_HEAD( Rva001361F0, GenElem236 )
BFME_VECTOR_OWNER_HEAD( Rva0013F130, GenElem236 )
BFME_VECTOR_OWNER_HEAD( Rva00141AE0, GenElem236 )
BFME_VECTOR_OWNER_HEAD( Rva0039D390, GenElem136 )
BFME_VECTOR_OWNER_HEAD( Rva003A7530, GenElem220 )
BFME_VECTOR_OWNER_HEAD( Rva00608010, GenElem528 )
