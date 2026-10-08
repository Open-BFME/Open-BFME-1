# SequentialScript destructor at RVA 0x0033B2A0 (80 bytes)
Old: `??1Rva0033B2A0@@QAE@XZ`
New: `??1SequentialScript@@UAE@XZ`

The matched scalar deleting destructor ??_GSequentialScript
(SequentialScriptDeletingDestructor.cpp, RVA 0x0033B270; slot zero of vtable
0x00CE7660 whose slots name SequentialScript) calls this body through ILT
0x00033429, which symbols.csv pins as ??1SequentialScript@@UAE@XZ.
tools/ilt_oracle.py check ??1SequentialScript@@UAE@XZ 0x0033B2A0: CONFIRMED exact.
The body destroys two string members (calls to 0x00887940,
StringBase<char>::releaseBuffer) and ends with the offset-0 base's inlined
vptr store; tools/probe.py reproduces it EXACT as a novtable class.
