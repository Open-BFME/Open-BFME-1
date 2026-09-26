// Five predicates that compare one int against a fixed sentinel and return the
// INEQUALITY:
//
//     mov edx,[ecx+<OFF>] / xor eax,eax / cmp edx,<K> / setne al / ret
//
// WHAT THE BYTES SHOW.  Four read the int out of the object at a proven offset;
// the fifth (00510BF0) reads a module-level int through a DIR32 site, which
// build.py fills from retail -- those four bytes are NOT evidence, but the
// eleven around them are, and they are the whole shape.
//
//   * `xor eax,eax` placed BEFORE the compare, with `setne al` after, is the
//     `return m_v != K;` form.  Writing it as `if (m_v == K) return false;
//     return true;` puts a branch here instead, and `return (m_v != K)` widened
//     through an explicit cast adds a movzx -- neither matches.
//   * The sentinels are read straight out of the immediates: 8, 0x7FFFFFFF, -1,
//     -1 and -2.  The two that fit a signed byte use the 83 /7 ib encoding and
//     the 0x7FFFFFFF one needs 81 /7 id, which is why this family's members are
//     15 and 12 bytes long from ONE source shape.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The bytes do not say
// whether the member is `int` or an enum of int width, nor what the sentinel
// means; -1 and 0x7FFFFFFF read like "unset" markers but that is a reading, not
// a proof.

#define BFME_SENTINEL_PREDICATE( NAME, OFFSET, SENTINEL )                 \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool isSet() const;                                               \
		char m_lead[ OFFSET ];                                            \
		int m_value;                                                      \
	};                                                                    \
	bool NAME::isSet() const                                              \
	{                                                                     \
		return m_value != ( SENTINEL );                                   \
	}

BFME_SENTINEL_PREDICATE( Rva003BC850, 0x10C, 8 )
BFME_SENTINEL_PREDICATE( Rva003FCF20, 0x20, 0x7FFFFFFF )
BFME_SENTINEL_PREDICATE( Rva00681BD0, 0x38, -1 )
BFME_SENTINEL_PREDICATE( Rva008028A0, 0x8, -2 )

// The same predicate over a module-level int instead of a member.  The DIR32
// operand is copied from retail, so the NAME below is address-derived from the
// datum's RVA and asserts nothing beyond "a four-byte object lives there".
extern int Data00EB7430;

bool Rva00510BF0();
bool Rva00510BF0()
{
	return Data00EB7430 != -1;
}
