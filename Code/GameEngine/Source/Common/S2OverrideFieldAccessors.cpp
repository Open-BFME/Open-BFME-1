// Five __thiscall const accessors that read one field through an OVERRIDE<T>
// smart pointer held at +4 of the owner:
//
//     mov eax,[ecx+4] / test eax,eax / jne walk
//     mov eax,[eax+<FIELD>] / ret
//     walk: mov ecx,[eax+4] / test ecx,ecx / je load / call <REL32>
//     load: mov eax,[eax+<FIELD>] / ret
//
// WHAT THE BYTES SHOW, AND WHY THE NULL ARM STILL DEREFERENCES.  The null arm
// is not dead code the compiler forgot: it loads the field through a register
// it has just proved to be zero, and it does so with the register form
// (`mov eax,[eax+74h]`), not the absolute form a folded null would produce.
// Writing the same control flow by hand -- `if (!p) return p->field;` -- makes
// MSVC 7.1 fold the null and emit `mov eax,[74h]`, which does NOT match.  What
// does match is the vendored ZH `OVERRIDE<T>::operator->`, which RETURNS NULL
// on the empty case:
//
//     if (!m_overridable) return NULL;
//     return (T *)m_overridable->getFinalOverride();
//
// inlined into `return m_thing->m_field;`.  The null comes back as a return
// value, the two arms merge, and the field load is duplicated into both.
// `Overridable::getFinalOverride` is inline in the ZH header and recursive, so
// one level inlines -- giving the `mov ecx,[eax+4]` / `test` / `je` -- and the
// recursion becomes the REL32 call to the out-of-line copy at 0x000022BB.
// m_nextOverride sitting at +4 of Overridable is what a leading vptr predicts.
//
// FIVE OWNERS, FIVE FIELD OFFSETS: 0x0C, 0x6C, 0x70, 0x74 and 0x444.  All five
// call the same override walker.
//
// IDENTITY IS NOT RECOVERED.  The IDIOM is recovered; the classes are not.
// Names are address-derived, the field is typed `int` because the load is a
// plain dword, and the four bytes ahead of the OVERRIDE member are unattributed.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}
	void *m_head;
	Overridable *m_nextOverride;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if( !m_overridable )
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
private:
	const T *m_overridable;
};

#define BFME_OVERRIDE_FIELD_ACCESSOR( NAME, FIELD )                       \
	class NAME##Thing : public Overridable                                \
	{                                                                     \
	public:                                                               \
		char m_gap[ ( FIELD ) - 8 ];                                      \
		int m_value;                                                      \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int value() const;                                                \
		char m_head[ 4 ];                                                 \
		OVERRIDE< NAME##Thing > m_thing;                                  \
	};                                                                    \
	int NAME::value() const                                               \
	{                                                                     \
		return m_thing->m_value;                                          \
	}

// @?value@Rva0060E7C0@@QBEHXZ 0x0060E7C0
BFME_OVERRIDE_FIELD_ACCESSOR( Rva0060E7C0, 0x0C )
// @?value@Rva00233D20@@QBEHXZ 0x00233D20
BFME_OVERRIDE_FIELD_ACCESSOR( Rva00233D20, 0x6C )
// @?value@Rva00270040@@QBEHXZ 0x00270040
BFME_OVERRIDE_FIELD_ACCESSOR( Rva00270040, 0x70 )
// @?value@Rva00150660@@QBEHXZ 0x00150660
BFME_OVERRIDE_FIELD_ACCESSOR( Rva00150660, 0x74 )
// @?value@Rva003DB4F0@@QBEHXZ 0x003DB4F0
BFME_OVERRIDE_FIELD_ACCESSOR( Rva003DB4F0, 0x444 )
