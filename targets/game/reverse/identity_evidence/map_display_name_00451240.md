# Canonical MapMetaData display-name return contract at 0x00451240

## Independent identity and ABI evidence

At baseline 526bbe81, matched native callers at 0x00451E90 (calls at 0x00451EBF and 0x00451ED5), 0x00520920 (0x0052096B), 0x00455F60 (0x004562C4), and 0x00527930 (0x005279FC) already name `?bfme_getDisplayName@MapMetaData@@QAE?AVUnicodeString@@XZ`. The generated caller at 0x0052A2E0 also calls it but is not relied on for identity. Its existing canonical pin at 0x0000A6FA follows the native ILT to 0x00451240. The only authored consumer of the old BfmeEntryAP / UnicodeStringAP identity is LANAPI::OnHasMap at 0x00688CD0.

The native body starts at 0x00451240 and is 212 bytes through its RET 4. ECX is MapMetaData; the sole stack argument is the caller-owned UnicodeString result buffer, returned in EAX. Native player count is read at receiver +0x20; existing BFME map metadata consumers and the upstream MapMetaData layout independently agree with m_numPlayers.

Native call offsets relative to 0x00451240 establish these exact contracts:

- +0x28: ILT 0x00042807 -> 0x00450FC0, the matched MapMetaData::bfme_getBaseDisplayName body, returning UnicodeString.
- +0x57: 0x00888DE0, private StringBase<unsigned short> text constructor.
- +0x61: 0x00889190, UnicodeString::format with a by-value UnicodeString format.
- +0x87: 0x00888600, public StringBase<unsigned short>::concat(const unsigned short *, int).
- +0x95 and +0xBB: 0x008881D0, private StringBase<unsigned short>::releaseBuffer.
- +0xA5: 0x00888400, private StringBase<unsigned short> copy constructor.

The suffix literal at VA 0x010F5E9C is exactly `L" (%d)"`, parentheses rather than the old source's bracket description. Suffix reads are a 16-bit length at header +4 and characters at header +8, with the native zero-character fallback at VA 0x0107388C. The canonical WWLib string headers own that representation and these APIs.

## Bounded correction

Replace the false `?bfmeDisplayNameAP@BfmeEntryAP@@QAE?AVUnicodeStringAP@@XZ` row with the canonical MapMetaData identity at the same 212-byte extent using add_match --correct-identity and a tombstone. Keep the legacy source/object key so the paired preview refreshes the same historical object position. Migrate the sole LAN consumer's call and return temporary to the same UnicodeString contract. Use its existing native text-view helper and inline cleanup. No fake class or cast between different string stand-ins remains in either TU.

The normal TU-local UnicodeString constructor/destructor definitions forward to the existing private StringBase implementations. No shared header, selected string provider body, string ledger row, string pin, alias, verifier or baseline is changed. Obsolete unrelated fake pins are deliberately left untouched because string-family ownership is separate.

## Verification

Fresh before and after scoped gates pass for the 212-byte provider and 709-byte LAN consumer. All four unchanged authored canonical callers, the three-body base-display-name TU, and the generated caller's eleven-body TU also pass fresh gates. check_csv and pin_consistency pass; no pin rows change.

Complete emitted COFF inventories retain every section payload, relocation, defined/undefined symbol, primary metadata and auxiliary record. Both main bodies preserve exact non-relocation bytes and relocation offsets, with only the documented ownership changes. EH code, FuncInfo/unwind states, SafeSEH handler identities and linker directives are preserved. The local UnicodeString destructor emission is explicitly corrected from the private StringBase destructor name to its native releaseBuffer target; those are distinct native symbols, not a general equivalence. All unchanged canonical selected string-provider holders and digests remain identical in the paired preview. Retired AP helpers have no remaining authored consumer.

Independent native EH verification establishes provider .text$x at RVA 0x00C23BC0 (51 bytes), FuncInfo at RVA 0x00E13D54 with three unwind states, and LAN .text$x at RVA 0x00C466E0 (66 bytes), FuncInfo at RVA 0x00E36178 with seven states. Their wide cleanup calls route via ILT 0x0003B304 to canonical UnicodeString::~UnicodeString at 0x0005EEA0; the LAN narrow cleanup uses ILT 0x0000D828. Ordinary wide cleanup goes directly to releaseBuffer at 0x008881D0.

The paired preview uses the unchanged historical index SHA256 034ebdbd7f13546b5fd7f5f79240e5d75e973fabcc4bad425a0f4ee9dd0d9573 with supported in-memory refresh only. It is not a fresh native/global link verdict. Detailed receipts are in build/map-display-audit, with an independent review packet maintained separately by the reviewer.
