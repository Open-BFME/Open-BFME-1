// cl: /EHs-c-
// Seven 29-byte virtual destructors that release one heap block held at this+8
// and hand the object back to a base whose destructor is inline:
//
//   push esi / mov esi,ecx
//   mov eax,[esi+8] / push eax
//   mov [esi],<DERIVED VFTABLE>
//   call ??_V@YAXPAX@Z / add esp,4
//   mov [esi],<BASE VFTABLE>
//   pop esi / ret
//
// WHAT THE BYTES SHOW.  Two vptr stores to the SAME slot, offset 0, in one
// body: that is a derived destructor writing its own vftable on entry and the
// base destructor -- inlined, because there is no call to it -- writing the
// base's on the way out.  So the base has a virtual destructor with an
// in-class body and nothing else to run.  The `ret` takes no argument, so this
// is the plain destructor and not the scalar-deleting one, which would end
// `ret 4`.  The single `push`/`call`/`add esp,4` is a __cdecl one-argument
// deallocation of the dword at this+8; MSVC emits no null test in front of it,
// which is what `delete p` does (operator delete handles null itself) and not
// what a hand-written guarded free would look like.
//
// The BASE vftable is the same address in all seven rows, so there is one base
// class.  The DERIVED vftable is the only axis.
//
// WHICH DEALLOCATOR.  The call goes to 0x00881EF0, `operator delete[]`, and
// not to 0x00881EB0, `operator delete` -- two distinct retail bodies -- so the
// member is an ARRAY and the expression is `delete [] p`.  The freed member is
// typed `char *` because nothing here says what it points at.  The dword at
// this+4 is never touched and is unidentified.  17 of the 29 bytes are
// concrete; the call displacement and the two vftable dwords are resolved from
// the target.
//
// TWO ROWS SHARE A DERIVED VFTABLE: 0x006D7B00 and 0x006D87C0 both store
// 0x0111E09C, so by every byte here they destroy the same class -- but one
// class cannot have two destructor bodies, so they are spelled as two classes
// and the shared vftable address is recorded here rather than hidden.  That is
// the same duplicate-translation-unit pattern the range-loop family shows.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

// Declared so MSVC 7.1 lowers `delete []` to ??_V@YAXPAX@Z; without a visible
// array-form declaration it folds the array delete onto the scalar ??3.
void operator delete[]( void *block );

class Q2ArrayOwnerBase
{
public:
	virtual ~Q2ArrayOwnerBase() {}
};

#define Q2_ARRAY_OWNER_DESTRUCTOR( NAME )                                 \
	class NAME : public Q2ArrayOwnerBase                                  \
	{                                                                     \
	public:                                                               \
		virtual ~NAME();                                                  \
	private:                                                              \
		int m_unreconstructed_04;                                         \
		char *m_block;					/**< retail this+0x08 */          \
	};                                                                    \
	NAME::~NAME()                                                         \
	{                                                                     \
		delete [] m_block;                                                   \
	}

Q2_ARRAY_OWNER_DESTRUCTOR( Rva005F3B50 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva005F3BB0 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva005F3D30 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva005F3EB0 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva006D7B00 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva006D87C0 )
Q2_ARRAY_OWNER_DESTRUCTOR( Rva006DB200 )
