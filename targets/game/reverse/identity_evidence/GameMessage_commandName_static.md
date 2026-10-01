# GameMessage static command name provider

The official EA GeneralsMD `Common/MessageStream.h:633` declares
`static AsciiString getCommandTypeAsAsciiString(GameMessage::Type t)`.
The matched native BFME caller at RVA `0008DDE0` (34 bytes) loads type from
`ECX+0x10`, pushes type and the hidden AsciiString result pointer, calls ILT
`00040A1B`, cleans eight stack bytes, and returns the result pointer with
`RET 4`. No GameMessage receiver is passed to the callee. Type is a four-byte
enum; AsciiString uses the existing native WWLib value type and hidden result ABI.

Retail ILT `00040A1B` is `E9 E0 AB 04 00` and routes to RVA `0008B600`.
The old authored naked definition copies that displacement without a COFF
relocation. Selected at VA `00429240` it instead jumps to VA `00473E25`.
Its five bytes are a compiler incremental-link artifact, not another
GameMessage method identity. Retire that row and definition; retain the real
provider at RVA `0008B600` under the official static SA decoration.

The existing provider has 7,143 executable bytes, one alignment NOP, and two
internal switch tables: offsets `1BE8..1DB0` (114 DWORD slots) and
`1DB0..1F90` (120 slots), for 8,080 bytes total. Retail instructions at
RVA `0008B696` and `0008C01B` index those tables. All 234 table DIR32 relocations
independently agree with the native COFF local labels inside this body.
The existing object has 549 DIR32 and 313 REL32 relocations; no nonrelocation
bytes differ from retail. These facts do not substitute for the required
fresh source and full relocation gates.

The previous QAE decoration claims a nonstatic receiver ABI contradicted by
that matched caller and native declaration. Its object-symbol note already
identifies the actual SA compiler symbol. Correct that ledger identity at
the same 8,080-byte extent; do not reorder ledger rows or invent an alias.

Source adopts existing `Common/System/message_stream.h`. Its method declaration
becomes static; this changes no instance field, virtual method, or layout.
The two existing direct dependents are `System/message_stream.cpp` and
`BannerMovieCallback00582A10.cpp`; neither calls this method. A shared header
full gate remains required.

Queued 8,054 authored bytes are potential source linkage only, not recovered
bytes or measured graph/PE runtime closure.
