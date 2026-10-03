# NetAckStage2 owner and C45160 cleanup

The complete retail191B body at RVA674E10 ends with RET4 at674ECC,
then INT3 at674ECF. It formats a base NetCommandMsg string and payload fields.

Owner proof does not rely on formatting intuition: the pointer to ILT47528
(VA447528) occurs in vtableVA111A4B0 at slot+0x0C (VA111A4BC).
Ghidra get_xrefs_to(00447528) reports that exact data reference and raw table
bytes agree. The ILT jumps to674E10. Matched NetAckStage2CommandMsg constructors
673950 and6739B0 write VA111A4B0 at673972/6739CB, set command type2 at+14,
and initialize the same fields this body reads: ushort+1C, byte+1E, uint+20.
The existing constructor TU and ZH NetCommandMsg.h establish the owner and
m_commandID/m_originalPlayerID. The BFME-only m_originalExecutionFrame at+20
is already established by constructor673950 copying base execution frame+8.
The address-named entry does not claim a new full semantic method identity;
no vtable is emitted in its local source view.

At674E4E the actual call through ILT2D204 reaches matched base
NetCommandMsg::getContentsAsAsciiString at6747C0. Thus the old
BfmeOrderZJ::bfmeNameZJ alias has the wrong owner, method and return type.
Its only source use was this parent; the recovered source calls the canonical base directly.
The direct string constructor888BC0, format888FF0, copy887B60 and release887940
prove canonical AsciiString instead of the synthetic StringBaseNarrowZJ /
AsciiStringZJ pair. The native canonical trial reproduced all191 instruction
bytes before the strict production verifier checked relocations.

Parent prologue674E12 -> handlerC45179 -> FuncInfoE349E4 -> mapE349CC
state0 predecessor-1 independently proves ownership of cleanupC45160.
The action tests EBP-14 mask1, clears it, loads the hidden result atEBP+4,
and tail-jumps through ILTD828 to canonical destructor5EE90. Its conditional
RET atC45178 proves25B; Ghidra raw bytes agree with the unpacked PE.
