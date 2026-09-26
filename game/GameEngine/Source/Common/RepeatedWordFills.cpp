// The three byte-identical 29-byte loops at 0x00499ED0, 0x00499FF0 and
// 0x0049A190.
//
//     mov ecx,[esp+8] / test ecx,ecx / mov eax,[esp+4] / jle done
//     mov edx,[esp+0xC] / push esi
//     loop: mov esi,[edx] / mov [eax],esi / add eax,4 / dec ecx / jne loop
//     pop esi / done: ret
//
// WHAT THE BYTES SHOW.  Three dword arguments, no `this`, no stack cleanup:
// __cdecl.  The count is tested with a SIGNED branch (`jle`), so it is an `int`,
// and a non-positive count stores nothing at all.  The destination advances four
// bytes per iteration and the stored value is four bytes wide, so the element
// type is a dword.
//
// The third argument is loaded ONCE into edx and then dereferenced afresh on
// every iteration -- `mov esi,[edx]` inside the loop, with edx never advancing.
// That is the whole point of the function: it is not a copy, it is a FILL, and
// the value being written is read through a pointer rather than passed by value.
// A by-value dword argument would have been hoisted into a register before the
// loop; re-loading it each time is what the compiler must do when the pointer
// could alias the destination it is writing.  So the source dereferences the
// pointer inside the loop, which is exactly `*out = *value` written in the body.
//
// The destination is loaded into eax BEFORE the emptiness test, on a path that
// then does nothing but return.  A void function would have had no reason to
// materialise it there; it is there because it is the RETURN VALUE, and on the
// zero-count path the unadvanced destination is what has to come back.  So the
// function returns the cursor it advanced to -- the append-style signature --
// and the loop variable and the return value are the same object.  Spelling it
// `void` compiles to the same loop with that load moved after the branch, which
// is how the return type was pinned down.
//
// The destination is loaded into eax BEFORE the emptiness test, on a path that
// then does nothing but return.  A void function would have had no reason to
// materialise it there; it is there because it is the RETURN VALUE, and on the
// zero-count path the unadvanced destination is what has to come back.  So this
// is an append-style writer that hands back the cursor it advanced to, and the
// loop variable and the returned value are the same object.  Spelled `void` the
// same loop compiles with that load moved after the branch, which is how the
// return type was pinned down rather than assumed.
//
// `push esi` sits after the emptiness test and `pop esi` before the shared
// return, so the zero-count path never saves it: /O2 shrink wrapping, which
// needs no help from the source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three distinct addresses within one stretch
// of .text; nothing here defeats inlining, so there is no per-translation-unit
// COMDAT reading to justify asserting they are one function.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the fill or what it
// fills, so the names are address-derived.

#define BFME_REPEATED_WORD_FILL( NAME )                                       \
	int *NAME( int *out, int count, int const *value )                        \
	{                                                                         \
		while ( count > 0 )                                                   \
		{                                                                     \
			*out = *value;                                                    \
			++out;                                                            \
			--count;                                                          \
		}                                                                     \
                                                                              \
		return out;                                                           \
	}

BFME_REPEATED_WORD_FILL( rva499ed0 )
BFME_REPEATED_WORD_FILL( rva499ff0 )
BFME_REPEATED_WORD_FILL( rva49a190 )
