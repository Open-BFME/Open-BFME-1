// Five bodies whose only arithmetic is one AND.  Grouping by mnemonic sequence
// puts them together; the OPERANDS say they are THREE unrelated sources, and
// all five are fully concrete, so the split is proven rather than argued.
//
//   1. 000B55A0 / 000F20E0  __thiscall, reads a member and masks it:
//          mov eax,[ecx+<OFF>] / and eax,1 / ret
//      The result is returned as-is.  `return (m_flags & 1) != 0;` would have to
//      normalise to 0/1 and adds a test/setne, so this returns the masked INT,
//      not a bool -- the accessor's return type is int-width.
//
//   2. 000B5EA0 / 000B5EB0  free functions of two stack arguments:
//          mov eax,[esp+4] / and eax,[esp+8] / ret
//      ecx is never read, so there is no `this`; the bare `ret` with arguments
//      left on the stack makes it __cdecl.  The two are byte-identical and the
//      bytes cannot say whether that is one function reached two ways.
//
//   3. 001C0760  a free function that masks IN PLACE through a pointer:
//          mov eax,[esp+4] / and dword ptr [eax],0x3FFFFF / ret
//      The destination is memory, not the return register, and nothing is left
//      in eax on purpose -- a void function taking a pointer.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; signedness of the
// masked values is invisible to these encodings and int is the spelling that
// asserts the least.

#define BFME_MEMBER_LOW_BIT( NAME, OFFSET )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int lowBit() const;                                               \
		char m_lead[ OFFSET ];                                            \
		int m_flags;                                                      \
	};                                                                    \
	int NAME::lowBit() const                                              \
	{                                                                     \
		return m_flags & 1;                                               \
	}

BFME_MEMBER_LOW_BIT( Rva000B55A0, 0x98 )
BFME_MEMBER_LOW_BIT( Rva000F20E0, 0x90 )

int Rva000B5EA0( int a, int b );
int Rva000B5EA0( int a, int b )
{
	return a & b;
}

int Rva000B5EB0( int a, int b );
int Rva000B5EB0( int a, int b )
{
	return a & b;
}

void Rva001C0760( unsigned int *slot );
void Rva001C0760( unsigned int *slot )
{
	*slot &= 0x3FFFFFu;
}
