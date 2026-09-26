// Two 31-byte scalar deleting destructors, 0x005E5520 and 0x005E56E0:
//
//     test byte ptr [esp+4],1        ; the hidden flags argument
//     push esi / mov esi,ecx
//     mov [esi],<VFTABLE>            ; the destructor body, inlined
//     je skip
//     push esi / call operator delete / add esp,4
//     skip: mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  A __thiscall member taking one dword, testing only its
// LOW BIT, freeing `this` when the bit is set and returning `this` either way,
// is the MSVC scalar deleting destructor `??_G` and nothing else -- no
// hand-written member has that flag protocol.  It exists only for a class with
// a VIRTUAL destructor, because it is the vftable slot the compiler puts there
// so that `delete` through a base pointer reaches the right free.
//
// THE DESTRUCTOR ITSELF IS INLINED INTO IT.  Between the flag test and the
// free there is exactly one instruction, the vptr store, and no call: the
// class's own destructor does nothing but re-stamp the vptr, so it is written
// in the class body rather than out of line, and there are no members or bases
// with destructors of their own to run.  A `~D() {}` written out of line would
// leave a call here instead.
//
// The vftable dwords 0x01111D20 and 0x01111D90 differ, so the two rows are two
// classes; they are DIR32 operands copied from retail and are not evidence
// beyond that.
//
// THE FACTORY BELOW IS SCAFFOLDING, not a recovered function.  MSVC 7.1 emits
// `??_G` only for a class it actually instantiates in the translation unit, so
// something has to `new` both classes; nothing in the image is claimed to
// correspond to it.
//
// IDENTITY IS NOT RECOVERED.  Names are derived from the row addresses.

#define T1_DELETING_DTOR( ROW )                                               \
	class T1Del_##ROW                                                         \
	{                                                                         \
	public:                                                                   \
		virtual ~T1Del_##ROW() {}                                             \
	};

T1_DELETING_DTOR( 005E5520 )
T1_DELETING_DTOR( 005E56E0 )

void *t1MakeDeletingDtorClasses( int which )
{
	if ( which )
	{
		return new T1Del_005E5520();
	}
	return new T1Del_005E56E0();
}
