# RVA 0x0019BF40: bound SidesList chunk parser

Native registration establishes this body's SidesList chunk role and receiver.
It does not recover an original C++ member spelling; no conversion is claimed.
The bank remains nonmatching at 1195 versus 1197 bytes.

The body's ILT is RVA 0x00043C93. Its VA 0x00443C93 is loaded into EBX
at 0x0074AE88, within the map-loading registration sequence. The same sequence
constructs native literal SidesList, VA 0x0109C1E4, at 0x0074AE4F. At
0x0074AE65 it loads the global pointer from VA 0x012EF428, and stores that
receiver value at ESP+0x44 at 0x0074AEA6. The callback record starts at
ESP+0x38, has table VA 0x0109BFD4 written at 0x0074AEAC, entry pointer
at +0x10 written at 0x0074AEB4, receiver at +0x0C, and zero this-adjustment
at +0x14 written at 0x0074AEB8. The registration call at 0x0074AE99 goes
through ILT 0x00015BD1 to matched DataChunkInput::registerParser 0x00103840;
its callback is ILT 0x0001579E to 0x001028D0, with the record as user context.

The native table's slot one, VA 0x0109BFD8, contains ILT VA 0x00438AE1,
which reaches the 11-byte invoker at 0x00192120. That invoker loads the
record's +0x14 adjustment, adds the +0x0C receiver and tail-jumps through
+0x10. The cdecl wrapper 0x001028D0 takes its third stack word as context,
then forwards its two original parser arguments into that virtual slot +4.
This chain proves ECX = the value of global VA 0x012EF428 for the candidate,
and two forwarded stack words. Thus the callback table need not point directly
to the parser body; the indirect binding recovers the missing entry route.

The body clears side-related storage, reads dictionaries, constructs BuildListInfo
records and appends team records. Native RET 8 at 0x0019C3EA and INT3 at
0x0019C3ED delimit 1197 bytes, agreeing with the callback's two forwarded words.
All registration stores, strings, table pointers, invoker instructions and extent
were checked against retail-1.03-unpacked lotrbfme.exe with pefile/Capstone.
No guessed original class/member spelling, new pin, source or ledger identity
is added. The existing address-qualified parser bank is preserved.
