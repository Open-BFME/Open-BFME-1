# RVA 0x00462D40 is the DisableComponents Apt callback

The 126-byte cdecl body is registered by BFME as the Apt callback
`DisableComponents`. Its authentic C++ function spelling remains unknown,
so retain the existing address-derived `Rva00462D40(void*)` binding.
The argument is either null/empty or a component-name character string.

All binary addresses below were checked against retail-1.03-unpacked
lotrbfme.exe, base 0x00400000, with pefile and capstone. GhidraMCP searches
`47 9C 44 00` and finds the only absolute pointer at VA 0x008644A7.

## Matched registration names the callback

The clean matched registerAptCallbacks00464080 at RVA 0x00464080, in
GUI/WindowManagerRegisterAptCallbacks00464080.cpp, constructs the literal
DisableComponents and invokes bindShown with ILT 0x00049C47. It separately
registers EnableComponents with ILT 0x0003DCA3. The native immediate at
VA 0x008644A7 is the DisableComponents callback pointer. ILT 0x00049C47
is an E9 to VA 0x00862D40; the other callback reaches sibling 0x00462CB0.
This is matched BFME registration evidence, not a name inferred from an EA
file hint or just the functor's false byte.

## Genuine native functor and string lifetime

The nonempty branch constructs an eight-byte Rva0045F0A0-compatible functor:
byte zero at offset zero, then a four-byte string at offset four returned by
normalizer RVA 0x0046F800 through ILT 0x00041AFB. The normalizer's clean body
in BfmeConv524.cpp uses a non-POD StringBase<char>-compatible return. Its
physical return is hidden storage; the older void/out-buffer cast model is
not a genuine declaration.

The native end iterator is two words, zero and table VA 0x012F19A4.
Hashtable::begin through ILT 0x0001BDC9 supplies the other two-word iterator,
then ILT 0x00035B48 calls the clean matched for_each at RVA 0x00462710 with
both iterators and the functor, returning an eight-byte functor in caller
storage. Its authoritative TU Rva00462710ModeCheckForEach.cpp gives the
address-derived table, record and functor types. The caller releases the
returned string through StringBase<char>::releaseBuffer at RVA 0x00887940.
The old 103-byte bank omitted this cleanup and the end-iterator argument.

The null/empty branch writes byte 1 at VA 0x012F4CA4 and invokes slot 44
of the manager loaded from VA 0x012F1B40 with a null argument. RET at
RVA 0x00462DBD and INT3 at 0x00462DBE prove the 126-byte cdecl extent.

## Measured experiment, not banked or landed

The scratch experiment included canonical Common/AsciiString.h and the existing
GameClient/GameWindowManager.h sweep header, uses the same native
Rva0045F0A0Input/iterator/functor types as the matched callee, invokes native
STLport for_each and correctly destroys the returned string. It contains
no union-punned calls, cast-address dispatch or assembly. The normalizer
is declared as an address-retaining function returning canonical AsciiString;
that typed binding is provisional and not pinned by this proof.

Fresh probe measures 126/126 bytes with seven relocations and only two
non-relocation differences: retail LEA EAX,[ESP+18h]; PUSH EAX versus
candidate LEA ECX,[ESP+18h]; PUSH ECX at offsets 0x49/0x4D. Normalized shape
1.000 is not a fully resolved byte match. Explicit template specialization
declarations triggered VC7.1 C1001; ordinary explicit instantiation compiles.
Separately named input/iterators produces 256 bytes, while bool-versus-char
flag type gives the same two differences. Header adoption preserves this
126-byte result and calls the existing slot-44 winSetFocus declaration. The
established _OPERATOR_NEW_DEFINED_ switch prevents GameMemory.h from
redeclaring STLport placement new. Probe and shape_levers were checked.

The name-regression guard rejects replacing the old bank: it pairs the old
GameWindowManager declaration with the new Rva0045F0A0 functor declaration,
even after the experiment adopts the canonical GameWindowManager header.
No exemption or guard change was made. The old tracked bank is preserved;
the protected preferred bank is not replaced or promoted. Reviewer-requested
follow-up archives the complete experiment in tracked attempt_history at
`0x00462d40/c3d388b6ffa0a7e9ba3c94d3142bd91b0b6e63ea8b5ee9e7bf04f6e27ebc3ff5.json`.
Its source SHA256 equals its filename. Fresh finish_measure reports
ours=126, retail=126, diffs=2, first=74, quality=0.9841. Companion
`00462d40-disablecomponents-probe.json` records the measurement and source
hash. The blocked outcome retains the guard refusal; a future worker can
recover the source from this alternative without changing the preferred bank.

The masked probe does not verify new normalizer, begin or data bindings.
The old g_bfmeTwoSJA pin at VA 0x00EF19A4 is not the native VA 0x012F19A4;
do not reuse it just to get a link. The existing TheWindowManager and g_bfmeDoneSJA bindings reproduce the
native manager/flag addresses. The table ownership, normalizer and typed
begin bindings must be independently established before landing. No pins, data rows, game source or ledger
function claims are changed here. The authoritative existing for_each source
remains its owner; the experiment's emitted template is not another progress row.
