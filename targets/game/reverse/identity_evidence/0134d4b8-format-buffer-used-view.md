# Bounded native formatter scratch view at VA0134D4B8

2026-10-04; base20da593fd16190f81fd465956f88c9e0256673ac.
This supplies one address-qualified zero-filled data range. It does not claim
the original array's full allocation extent or repair constructor ownership.

## Independently witnessed used range

Retail PE SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
The complete103-byte formatter at RVA009D6220 has these original operations:

-VA00DD6243 pushes the immediate count0x7FF.
-VA00DD6248 pushes the destinationVA0134D4B8.
-VA00DD624D calls the `_vsnprintf` IAT slotVA01359360.
-VA00DD6253 retains the returned length; VA00DD6255 adds1 for a separate
 operator-new[] allocation.
-VA00DD6269 loads the same scratch address into ESI. The following REP MOVSD
 and REP MOVSB copy the returned length to the allocated text.
-VA00DD627E writes the terminator into the allocated text, not into scratch.

The explicitly supplied writable destination capacity therefore witnesses the
2047-byte used view `[0134D4B8,0134DCB7)`. There is no implied scratch+0x7FF
strlen/sentinel read in this source/native path. The change does not alter any
formatting result, negative/truncated return handling, allocation, copy or
termination behavior. It neither repairs nor disguises pre-existing behavior.

The old extern's bound2048 was only a reconstruction declaration. No end symbol
independently proves2048 as the native allocation size. The caller now uses an
unsized extern; the one definition owns only the witnessed2047-byte view.

## Initial bytes, permissions and non-overlap

PE.data has characteristics0xC0000040 (read/write), beginsVA012A5000, has
file-backed endVA012EE000, and virtual endVA01358000. The entire used range is
in its virtual-only loader-zero tail. It is not file-backed data: normal PE
zero-fill semantics supply the initial zeros. A real read-only Ghidra MCP batch
also returned zeros throughout the requested2048-byte neighborhood; this is
corroboration of initialized memory, not proof of allocation extent.

The next independently referenced storage is the byte flagVA0134DCBC. Native
00DDB5D0 reads that byte and writes1 at00DDB5E1; native00DDE740 independently
reads/writes the same flag. This is five bytes after the view's exclusive end.
The following pointerVA0134DCC0 also has its own reader/writer. Neither lies in
the owned view. Current data_rows.csv has no overlapping owner, and authored
source has no other definition of Rva0134D4B8FormatBuffer.

## Supported verification and source ownership

`reloc_ledger.Image.read` explicitly models a section's virtual-only tail as
zero. `data_rows.verify_row` verifies uninitialized/COMMON symbols against those
bytes. `symbol_size` requires compiler sizeof (or a COMMON symbol's recorded
size), treating a COFF allocation extent only as a bound. No verifier exception,
new range interpretation or byte masking is introduced.

The existing data ledger already supports address-derived bounded char-storage
views, for exampleVA0130ACC8/20 with the formatter's supplied capacity. This
row likewise claims the precise compiled symbol's independently witnessed used
range, not an inferred original allocation boundary.

The sole definition remains beside its sole reader/writer in
Common/Gen009D6220.cpp. The existing address-qualified spelling is retained.
An unsized extern precedes the unchanged function and a2047-byte zero-filled
array definition follows it. No new TU or symbol alias is needed. The original
103-byte code and all its relocations must remain unchanged; normal data and
whole-source gates verify the owned range and caller together.

This fixes the scratch datum required by the existing C formatter provider.
It does not introduce the still-missing canonical XferException constructor,
change any throw consumer, or assert that unrelated link debt is resolved.
