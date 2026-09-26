// Five void functions that test a stored pointer and, only when it is non-null,
// perform one store:
//
//     mov eax,[<PTR>] / test eax,eax / jz L / mov <dst>,<K> / ret   (L: ret)
//
// WHAT THE BYTES SHOW.  Nothing follows the guarded store, so the jz distance
// cannot be used to argue about scope -- the store IS the body of the `if`.
// What the bytes do decide, sharply, is the store's DESTINATION, and it splits
// this shape into two unrelated sources:
//
//   * 00681A20, 00681A40 and 004C7470 write THROUGH the loaded pointer
//     (`mov byte ptr [eax+K],imm8`), so the guard protects a dereference.
//   * 006BC730 and 009D8AA0 write back to the SAME slot they just read
//     (`mov dword ptr [ecx+K],0`, with ecx still `this`), so the guard protects
//     nothing but a redundant store: the source is `if (m_p) m_p = 0;`.
//     Reading these as a dereference would put the wrong base register in the
//     store, so the two readings are separable by bytes alone.
//
// Falling straight to `ret` on the null arm -- no `xor eax,eax` before it --
// proves these are void, not a predicate that returns 0 when null.
//
// 004C7470 loads its pointer from a module-level slot through a DIR32 site that
// build.py copies from retail; those four bytes are not evidence, and the name
// below is derived from the datum's RVA.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The bytes cannot say
// whether the stored 1/0 is a bool, a byte-wide enum or a flag byte; the byte
// width is all they fix.

// The pointee shared by 00681A20 and 00681A40: one byte at 0x12114, written
// true by one and false by the other.
class Gen00681A20
{
public:
	char m_lead[ 0x12114 ];
	bool m_flag;
};

#define BFME_GUARDED_FLAG_STORE( NAME, PTROFF, VALUE )                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void apply();                                                     \
		char m_lead[ PTROFF ];                                            \
		Gen00681A20 *m_target;                                            \
	};                                                                    \
	void NAME::apply()                                                    \
	{                                                                     \
		if ( m_target )                                                   \
		{                                                                 \
			m_target->m_flag = VALUE;                                     \
		}                                                                 \
	}

BFME_GUARDED_FLAG_STORE( Rva00681A20, 8, true )
BFME_GUARDED_FLAG_STORE( Rva00681A40, 8, false )

// The self-clearing pair: read the slot, and when it is non-null store null
// back into it.
#define BFME_GUARDED_SELF_CLEAR( NAME, PTROFF )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void apply();                                                     \
		char m_lead[ PTROFF ];                                            \
		void *m_target;                                                   \
	};                                                                    \
	void NAME::apply()                                                    \
	{                                                                     \
		if ( m_target )                                                   \
		{                                                                 \
			m_target = 0;                                                 \
		}                                                                 \
	}

BFME_GUARDED_SELF_CLEAR( Rva006BC730, 8 )
BFME_GUARDED_SELF_CLEAR( Rva009D8AA0, 0x14 )

// The same guarded dereference, but the pointer lives in a module-level slot.
class Gen004C7470
{
public:
	char m_lead[ 0x259 ];
	bool m_flag;
};

extern Gen004C7470 *Data00EF49B4;

void Rva004C7470();
void Rva004C7470()
{
	if ( Data00EF49B4 )
	{
		Data00EF49B4->m_flag = false;
	}
}
