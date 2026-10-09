# Reset blocks and dirty byte

The matched 29-byte reset at RVA 00421DE0 loads ECX=9, ESI=012B4FF8,
and EDI=012B501C, then executes REP MOVSD. This independently proves
both complete 36-byte block extents. Source and destination are exactly
36 bytes apart. The distinct following table begins at VA 012B5040,
where matched bfmeCopyTable at RVA 00421E20 starts its next copy.
The existing BfmeBlockCU view holds nine DWORDs and has sizeof 36.

Retail loader-mapped .data holds the same nine DWORDs in both blocks:
00000000, 00000011, 3F800000, 00000100, then five zero DWORDs.
The declaration view remains unchanged and the meanings of these
fields are not asserted.

The reset then stores byte 1 to VA 012F13FC. Matched filter preRender
at RVA 007D74D0 tests this byte and clears it after taking a snapshot.
The loader-mapped initial byte is zero. The existing bool definition
has sizeof 1, matching these independently witnessed byte accesses.
Its record already names the bool symbol and also the unsigned-char
view at the same address. Define only the existing reset TU's symbol;
there is no alias, new data pin, address global, or DIR32 record edit.
