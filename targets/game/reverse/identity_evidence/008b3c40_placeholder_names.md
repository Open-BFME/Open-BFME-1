# 0x008B3C40 bank -> NativeProperties008B3C40.cpp: placeholder type spellings

The banked attempt used `BfmeA1029` and `Rva8CD130Value` for two local types.
Both are opaque placeholders, not recovered identities. The exact landing
(gpt-6-astra) spells them the way the code it calls already does:
`Rva00899560Value` is the value type in the landed callee pin
`?lookup@PropertyLookup008B2F50@@QAEPAURva00899560Value@@...` (0x008B2F50,
see 008b3aa0-boundaries-and-008b3c40-callee.md), and `Rva00899FC0` is the
class the landed 0x00899FC0 code models. No descriptive name is lost.
