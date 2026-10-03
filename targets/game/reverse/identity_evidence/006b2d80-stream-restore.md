# RVA 006B2D80: stream reference processing

The old generated ledger length of 448 stops immediately after POP EDI at
006B2F3F. Decoding continuously from006B2D80 reaches POP ESI/EBP/EBX,
ADD ESP,8 and RET at006B2F46, followed by INT3. Full extent is455 bytes.
The final JNE at006B2F39 loops to006B2DA0. There is no second entry here.
Ghidra's inherited448-byte function boundary was incomplete.

The MilesAudioManager constructor/destructor family identifies the receiver,
but no method spelling is established. Rva006B2D80::method remains opaque.
It processes three reference handles at+AD0, searches the native list at+9D0,
updates a previously absent stream's event/reverb/pan/fade state and inserts
its reference, then clears the saved handle. Audio settings are at+C with
fade-frame count at+3C; the reverb byte is+633. The ref pointee uses an atomic
count at+4 and virtual deleting destructor at slot0. This differs from the
non-atomic WWLib RefCountClass; the view is address-qualified and uses the
canonical vendor RefCountPtr<T> interface (Add_Ref/Release_Ref/Clear).

The info vector begin/end at+8C/+90 has the two-dword payload representation
used by the existing indexed-entry helper family; this caller only tests
empty(), so it does not claim meaning for the element fields. Native STLport
list and vector accessors preserve iterator lifetimes. The specialized
placement _Construct calls existing gen_00698020: independent31-byte body
copies one pointer and conditionally InterlockedIncrement(count+4).

All direct calls retain established bindings: indexed dispatch6A8210 via
B43D; volume compute6AE150 via2918B; placement copy698020 via1870F; native
__new_alloc::allocate at82E540. Imports were read from the PE IAT:
AIL_set_stream_reverb_levels@12, AIL_stream_volume_pan@12,
AIL_set_stream_volume_pan@12, AIL_pause_stream@8 and InterlockedDecrement@4.
The three-argument getters/setters and pause integer follow their existing
MSS declarations. The clamp constants are literal0.0f and1.0f.

Measured shape levers: native vector empty() restores the two pointer loads
and address calculation; canonical RefCountPtr::Clear() preserves conditional
zeroing; copying the volume-event argument to a local restores EDX/EAX order.
The complete455-byte draft probes exact modulo relocations. Promotion also
requires scoped add_match's strict constant/import/call checks.

Validation: strict add_match passed455/455 bytes, all five float operands
and seven DIR32 references. No callee/import pins or shared headers changed.
The indexed helper6A8120 independently reads the source range at(*value)+8C
and increments a two-dword record pointer, establishing its8-byte stride.
