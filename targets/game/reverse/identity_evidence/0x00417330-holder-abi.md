# 0x00417330: Drawable custom-audio name, by-value holder ABI

Retail is 205 bytes: `ret 4` at +0xCA and INT3 at +0xCD. The current
`Drawable::mangleCustomAudioName(DynamicAudioEventInfo *) const` lift has the
right operation but the wrong argument lifetime. It initializes EH state zero
at entry, and at +0x99 checks the incoming pointer, calls InterlockedDecrement
on pointee+4, and invokes deleting-destructor slot zero when the result is <=0.
This is a by-value intrusive holder destructor, not an ordinary raw pointer.

The independent caller in Drawable::xfer proves the copy ownership:

- VA 0x0081DDF6 reserves a four-byte outgoing argument.
- 0x0081DDFD stores EDI into that argument.
- 0x0081DE01 takes pointee+4 and 0x0081DE05 calls InterlockedIncrement.
- 0x0081DE10 calls ILT 0x000257F2, which jumps to body 0x00417330.
- The caller continues using the pointee after the call, at 0x0081DE18.

The receiver's +0x100 field is the witnessed Drawable::m_id (`name_oracle`).
The literal at VA 0x010F1520 is ` CUSTOM %d `. GeneralsMD Drawable.cpp:4398
supplies the `mangleCustomAudioName` twin: format the Drawable ID, concatenate
the existing audio name, then override it. BFME reads the name at pointee+8.
Its string allocation header has a 16-bit length at +4 and data at +8.

The last non-CRT call goes through ILT 0x0001D002 to 0x000B5610 (50 bytes).
That helper preserves the initial +8 string at +0x9C once, sets bit zero at
+0x98, then forwards the supplied string reference through ILT 0x00012D82.
The bank uses the existing address thunk, not a newly asserted callee name.

The new clean bank uses the existing stringbaseascii and StringBase headers,
an inline StringBase destructor/concat forwarding definition, and an
address-qualified holder and receiver. The initial direct m_id read produced
205 bytes with ten scratch-register differences. A class-body getID accessor
(or a named local ID before format) produces EXACT 205/205 modulo all twelve
relocation slots. This is a probe result, not a claimed strict-gate conversion.

Integration uses the established BFME class home DrawableVisualState.cpp.
The target brief explicitly prefers an already-matched BFME class home when
the readable-body comment names a Zero Hour-layout TU that cannot hold the
body. This file only forward-declared AsciiString, so it can include the
canonical BFME stringbaseascii/StringBase headers without changing any shared
header. Splitting its padding exposes the independently witnessed m_id at
+0x100; all later offsets remain unchanged.

The new method keeps the Zero Hour-witnessed mangleCustomAudioName name and
const receiver, with the address-qualified Rva00417330Holder parameter whose
lifetime retail proves. add_match --correct-identity tombstones the raw-pointer
claim. The old naked lift is removed. The strict scoped build passes all
12 functions in DrawableVisualState.cpp, the string/constant checks and all
12 DIR32 references. No new symbol pin is required.
