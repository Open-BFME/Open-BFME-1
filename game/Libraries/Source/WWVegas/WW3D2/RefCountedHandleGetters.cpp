// The four byte-identical 29-byte refcounting getters at 0x00912830, 0x00912850,
// 0x0098ECC0 and 0x0098ECE0.  Retail:
//
//     push ecx / mov ecx,[ecx+0x24] / test ecx,ecx / mov eax,[esp+8]
//     mov dword ptr [esp],0 / mov [eax],ecx / je done
//     inc word ptr [ecx+4]
//     done: pop ecx / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx and `ret 4` with one incoming stack dword
// that is never read as a value, only stored through: that dword is the hidden
// return pointer, so this is a __thiscall member returning a class BY VALUE.
// `this` itself is never written and the only member touched is the pointer at
// +0x24, so the function is a const accessor.
//
// The returned class is one pointer wide -- exactly one dword is stored into the
// return buffer -- and the pointer it wraps has its 16-bit counter at +4 bumped
// when it is non-null.  `inc word ptr` is a two-byte counter, not a dword one:
// the member at offset 4 of the pointee is a 16-bit reference count.  A getter
// that hands out a pointer and increments its refcount is a smart-pointer
// return, and that is what the C++ below spells.
//
// THE ZEROED FRAME SLOT IS NOT THE RETURN TEMP.  `push ecx` is MSVC 7.1's
// one-byte `sub esp,4` and `mov dword ptr [esp],0` stores into those four bytes,
// which nothing ever reads -- the return value goes to [esp+8], the caller's
// buffer, not here.  This was checked rather than assumed: written without the
// extra local the same source compiles to 20 bytes (`8b 49 24 ...`, no push/pop
// and no store), so the four bytes and their zeroing are load-bearing and come
// from a local the compiler was forbidden to delete.  In C++ that is a volatile
// one; whatever it was originally, its whole observable effect here is this
// store.
//
// THE STORE ORDER IS EVIDENCE.  The retail body stores the return buffer BEFORE
// testing, then bumps the count.  Writing the obvious `h.m_p = m_obj; if (m_obj)
// ++m_obj->m_ref;` compiles with the store SUNK past the branch -- probed, 29
// bytes, two instructions transposed.  What reproduces the retail order is
// initialising the returned object through a constructor that takes the pointer,
// which is also what a smart-pointer return looks like in source.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses in two unrelated
// gen_asm dumps, in adjacent pairs (0x00912830/0x00912850 and
// 0x0098ECC0/0x0098ECE0); each is written as its own class below.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the owner classes, the pointee, or
// the handle, so the names are derived from each body's own address.

class RefCountedTarget
{
public:
	int m_first;
	unsigned short m_refCount;
	unsigned short m_pad;
};

class RefCountedHandle
{
public:
	RefCountedHandle( RefCountedTarget *target );
	RefCountedTarget *m_target;
};

// The handle's constructor is inlined into all four getters and is referenced
// nowhere else, so the retail linker dead-stripped its own copy: these exact
// nineteen bytes occur nowhere in .text.  It is kept because it is what shapes
// the four matched bodies, and marked accordingly.
// ??0RefCountedHandle@@QAE@PAVRefCountedTarget@@@Z absent-from-retail
inline RefCountedHandle::RefCountedHandle( RefCountedTarget *target ) : m_target( target )
{
	if ( m_target )
	{
		++m_target->m_refCount;
	}
}

#define BFME_HANDLE_GETTER( NAME )                                            	class NAME                                                                 	{                                                                          	public:                                                                    		char m_pad[ 0x24 ];                                                     		RefCountedTarget *m_target;                                             		RefCountedHandle getHandle() const;                                     	};                                                                         	RefCountedHandle NAME::getHandle() const                                   	{                                                                          		volatile int guard = 0;                                                 		return RefCountedHandle( m_target );                                    	}

BFME_HANDLE_GETTER( Rva00912830Owner )
BFME_HANDLE_GETTER( Rva00912850Owner )
BFME_HANDLE_GETTER( Rva0098ECC0Owner )
BFME_HANDLE_GETTER( Rva0098ECE0Owner )
