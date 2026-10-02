// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Use the class headers: <fstream> also emits an unrelated locale initializer.
#include <ios>
#include <stl/_fstream.h>

// Six __thiscall members that ask a sub-object a question, and if the answer is
// zero go on to OR two bits into a flag word belonging to a second object whose
// position is read out of a third, then tail-jump when the new flags intersect
// a mask.
//
//     push esi / mov esi,ecx
//     lea  ecx,[esi+SUBOFF] / call <CHECK>     ; __thiscall on a sub-object
//     test eax,eax / jne  ret                  ; non-zero answer: done
//     mov  eax,[esi] / mov ecx,[eax+4]         ; a BYTE DISPLACEMENT, not a ptr
//     mov  eax,[ecx+esi+8] / mov edx,[ecx+esi+0x58]
//     add  ecx,esi                             ; ecx = the node
//     or   eax,4
//     test edx,edx / jne + / or eax,1
//     test [ecx+0x14],eax                      ; flags tested BEFORE the store
//     mov  [ecx+8],eax                         ; ...which does not touch flags
//     je   ret
//     pop  esi / jmp <NOTIFY>                  ; __thiscall on the node
//
// WHAT THE BYTES SHOW.
//
//  * `[ecx+esi+8]` is base-plus-index addressing, so the value fetched from
//    `[[esi]+4]` is an OFFSET IN BYTES added to `this`, not a pointer.  A
//    stored pointer would need no `add ecx,esi` at all.  That is what fixes the
//    source as a cast of `(char *)this + <offset>` rather than a member load.
//  * `lea ecx,[esi+SUBOFF]` with no null guard is a SUB-OBJECT at that offset,
//    not a stored pointer and not a second base needing an adjust.
//  * The `test` reads the mask BEFORE the store writes the flag word, and the
//    store does not disturb the flags, so the source order is store-then-test;
//    the schedule is the compiler's.
//  * `pop esi / jmp` gives the callee our return address and our stack pop, so
//    NOTIFY is __thiscall with no stack arguments -- the same reasoning that
//    types the tail thunks in IndirectMemberTailThunks.cpp.
//
// TWO AXES, AND THE CROSS-CHECK PASSES.  Three sub-object offsets (4, 8, 0xC)
// times two CHECK callees (0x00842870, 0x00842A00) is exactly the six members,
// each combination appearing once and no callee appearing at more than one
// offset for a given owner.  The NOTIFY target (0x0083E8F0) and the node
// layout are constant across all six.
//
// The close callees identify the narrow and wide STLport file buffers.
// The locator reaches basic_ios, whose inline setstate supplies the same
// failbit/badbit update and ios_base::_M_throw_failure tail call.

// [this+0] points at this; +4 of it is the node's byte offset from `this`.
struct Gen0084ACC0Locator
{
	int m_00;
	int m_04;
};

typedef _STL::basic_filebuf<char, _STL::char_traits<char> > Gen00842870;
typedef _STL::basic_filebuf<unsigned short, _STL::char_traits<unsigned short> > Gen00842A00;

// The matched explicit instantiations in FilebufInstantiations.cpp own these
// bodies; this TU only calls them.
template <> Gen00842870 *Gen00842870::close();
template <> Gen00842A00 *Gen00842A00::close();

#define BFME_NODE_FLAG_UPDATE_BODY                                      \
	{                                                                   \
		if ( m_sub.close() )                                            \
			return;                                                     \
		_STL::basic_ios<char, _STL::char_traits<char> > *node =           \
			reinterpret_cast<_STL::basic_ios<char, _STL::char_traits<char> > *>( \
				(char *)this + m_locator->m_04 );                        \
		node->setstate(_STL::ios_base::failbit);                          \
	}

#define BFME_NODE_FLAG_UPDATER_AT4( NAME, CHECK )                         \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void update();                                                    \
		Gen0084ACC0Locator *m_locator;                                    \
		CHECK m_sub;                                                      \
	};                                                                    \
	void NAME::update() BFME_NODE_FLAG_UPDATE_BODY

#define BFME_NODE_FLAG_UPDATER( NAME, CHECK, SUBOFF )                     \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void update();                                                    \
		Gen0084ACC0Locator *m_locator;                                    \
		char m_lead[ SUBOFF - 4 ];                                        \
		CHECK m_sub;                                                      \
	};                                                                    \
	void NAME::update() BFME_NODE_FLAG_UPDATE_BODY

BFME_NODE_FLAG_UPDATER   ( Rva0084ACC0, Gen00842870, 0x08 )
BFME_NODE_FLAG_UPDATER_AT4( Rva0084AD60, Gen00842870 )
BFME_NODE_FLAG_UPDATER   ( Rva0084AE00, Gen00842870, 0x0C )
BFME_NODE_FLAG_UPDATER   ( Rva0084AEA0, Gen00842A00, 0x08 )
BFME_NODE_FLAG_UPDATER_AT4( Rva0084AF40, Gen00842A00 )
BFME_NODE_FLAG_UPDATER   ( Rva0084AFE0, Gen00842A00, 0x0C )
