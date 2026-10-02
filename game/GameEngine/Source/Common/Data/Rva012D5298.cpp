// cl: /DNDEBUG /MD
//
// The shared, statically allocated empty EA string block at VA 0x012D5298.
//
// Evidence: build/report_0x01336E50.md, section "0x012D5298 -- shared empty EA
// Apt string block".  The field offsets are proven from matched bodies, not
// inferred: 0x0089F730 (`?rva0089F730@EAStringC@@QAE_NPBD@Z`) reads
// `word [esi+2]` as the length and computes the buffer at `+8`; 0x0089E570
// (`?ChangeBuffer@EAStringC@@AAEXIIIW4CBPushZero@1@I@Z`) writes
// `word [ecx+2]=size`, `word [ecx+4]=cap`, `word [ecx+6]=0`; 0x00891B80
// (`?release@Rva00891B80@@QAEXXZ`) does `dec word [eax]; cmp word [eax],0`.
// 0x0089F010 `?Left@EAStringC@@QBE?AV1@H@Z`, 0x0089F1B0
// `?Mid@EAStringC@@QBE?AV1@H@Z` and 0x00891B40 all store 0x12d5298 and
// `inc word [0x12d5298]`, so it is one shared sentinel block, never pool
// memory.  Two sibling four-byte cells (0x012D5140, 0x012D5978) hold pointers
// to it, and 0x00C6DC50/0x00C6DC70 bump it once each at startup.
//
// Retail bytes at the VA are 01 01 00 00 00 00 00 00 then eight zeros.  Note
// that the first word is 0x0101, not 1: the report's per-field table read the
// byte pair 01 01 as two little-endian shorts.  That matters, because
// 0x0089E570's sole-owner test is `cmp word [ebx],1` -- with 0x0101 the shared
// sentinel can never take ChangeBuffer's in-place path, which is exactly why no
// matched body writes through its buffer.  The length word is 0, the empty
// string.
//
// The name is address-derived on purpose: the report found no export, RTTI,
// string literal or EA path for it, so `TheEmptyStringData` cannot ship
// (docs/naming_evidence.md).  The class spelling is the proven
// `EAStringC::StringDataC` that already claims this VA in
// targets/game/reverse/dir32_addresses.csv, so referencing files need only the
// variable renamed, not the type.
//
// clang-format off
class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
		char m_text[8];
	};
};
// clang-format on

EAStringC::StringDataC g_rva012D5298Empty = { 0x0101, 0, 0, 0, "" };