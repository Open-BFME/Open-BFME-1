# ModelConditionInfo constructor at RVA 0x00776330

Identity is retained from the Zero Hour twin, not inferred from byte matching.
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h:241`
defines `ModelConditionInfo()` inline and calls `clear()`.
BFME's matched `W3DModelDrawModuleData::parseConditionState` at RVA 0x0077C860
constructs its local ModelConditionInfo at VA 0x00B7C882 through ILT RVA
0x00047F28, whose E9 target is 0x00776330. This parser's identity is independently
anchored by the in-exe field table at VA 0x01124F90 and its Zero Hour twin.
The parser later destroys the local through ILT 0x0002306F, targeting the
matched 306-byte ModelConditionInfo destructor at RVA 0x0013C3F0.

Retail bytes were read from the current unpacked baseline with pefile/capstone.
The constructor begins at the ILT target, installs its EH frame, and ends with
RET at RVA 0x00776482 followed by INT3 at 0x00776483: 339 bytes.
It zeroes ten words at +0x00, constructs vector/string fields, five arrays of
four AsciiStrings at +0x4C/+0x5C/+0x6C/+0x7C/+0x8C, then allocates a 44-byte
self-linked node for +0x9C. The last call enters ILT 0x0003AB11 -> 0x00774B60
with this in ECX and no stack arguments, matching the upstream clear call.
The adapter retains the existing opaque callee identity and inferred ABI.

The implementation extends the existing BFME class home
`ModelConditionInfoDestructorThunk.cpp`, whose clean C++ destructor proves the
0x128-byte layout. The Zero Hour layout is different; in particular, its
older layout witness at +0x28 conflicts with the matched BFME parser's vector
there. Existing address-based fields are retained. No new field meaning is
claimed. The native bitset default constructor supplies the ten-word clear;
the vector end-pointer's nested construction follows STLport's allocator
proxy and reproduces the EH receiver-save scheduling.

The allocator is directly called at RVA 0x0082E540, cdecl with one 44-byte
size argument and the result in EAX. The callee tool's historical
`__new_alloc::allocate` alias is not the vendored inline implementation (which
calls global operator new at 0x00881F30). The existing opaque
`Rva0082E540NodeAllocate(unsigned)` binding targets the exact observed body;
no pin or alias is added. The strict gate checks this call and both AsciiString
constructor/destructor DIR32 array callback addresses, not merely masked bytes.

The name-regression scanner pairs the removed local AsciiString definition
with the newly inserted Rva00776330Pointer declaration. AsciiString is not
renamed: it now comes from canonical ascii_string.h and every existing
AsciiString field retains its type. The pointer is an independent nested
vector storage field; the exact source-hash correction records this false pair.
