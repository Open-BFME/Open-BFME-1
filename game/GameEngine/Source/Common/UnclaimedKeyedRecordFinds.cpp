// Three unclaimed __thiscall finders with one shape:
//
//     mov eax,[ecx] / mov ecx,[ecx+4] / <scale ecx by the record size> /
//     add ecx,eax / cmp eax,ecx / jae miss / mov edx,[esp+4] /
//     loop: cmp [eax+8],edx / je hit / add eax,<record size> / cmp eax,ecx /
//     jb loop / miss: xor eax,eax / hit: ret 4
//
// `this` holds a record array pointer and a record count; the member walks
// the records and returns the first whose dword at +8 equals the one stack
// argument, or null.  The three differ only in the record size (0x40, 0x30,
// 0x80 bytes), so each gets its own record type of that size.  Every body
// sat in a .text gap no ledger row covered: 16-byte-aligned start after an
// int3 pad run, ret 4 followed by int3 padding, and no call, ILT stub, table
// slot or code immediate reaches it.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_KEYED_RECORD_FIND( NAME, RECORD, SIZE )                         \
	struct RECORD                                                            \
	{                                                                        \
		int  m_lead[ 2 ];                                                    \
		int  m_key;                                                          \
		char m_rest[ SIZE - 12 ];                                            \
	};                                                                       \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		RECORD *find( int key ) const;                                       \
                                                                             \
		RECORD *m_records;                                                   \
		int     m_count;                                                     \
	};                                                                       \
	RECORD *NAME::find( int key ) const                                      \
	{                                                                        \
		RECORD *end = m_records + m_count;                                   \
		for ( RECORD *record = m_records; record < end; ++record )           \
		{                                                                    \
			if ( record->m_key == key )                                      \
				return record;                                               \
		}                                                                    \
		return 0;                                                            \
	}

BFME_KEYED_RECORD_FIND( Rva007F6BF0Table, Rva007F6BF0Record, 0x40 )
BFME_KEYED_RECORD_FIND( Rva00801500Table, Rva00801500Record, 0x30 )
BFME_KEYED_RECORD_FIND( Rva008029A0Table, Rva008029A0Record, 0x80 )
