# Audio worker694130: reference-parameter ABI fixes the epilogues

## Extents and owner
Retail694130 spans203 bytes through RET12 at6941F8 (INT3 from6941FB).
Matched MilesAudioManager::rva006ABDA0 in MilesAudioManagerStopChain.cpp calls
ILT3AA6C ->694130 on m_worker at this+B00. Its typed call passes
AudioEventRef const& and int and receives Rva006910F0Handle by hidden result.
The worker member is Rva00694710AudioWorker, constructed by matched694710.
The address-named method claims no extra semantic identity.
The existing caller's AudioEventInfo+84/m_soundType and AudioEventRTS+8/
m_eventInfo views establish the fields. name_oracle's ZH+84 lowPassFreq is
not BFME evidence; the already matched BFME caller and literal retail tests
are the witnesses here. An AudioEventRef is the one-pointer wrapper used by
that same matched caller. No shared header defines these local views.

## Independent ABI proof for helper693B90
At6941AC the caller takes the address of its filename temporary slot and
passes it to ILTFA1F -> matched filename getterB3BF0. EAX is the address of
the returned AsciiString. At6941BE/BF/C0 it pushes priority, EAX, and hidden
handle result, then calls ILT3214B ->693B90 with the original worker inECX.
This passes an AsciiString REFERENCE, not its one-word buffer value.
After the call6941E1 destroys that filename in the caller via887940.

Independently inside693B90, after its prologue and four register pushes,
693BF1 loads filename argument [ESP+3C] intoEBP;693BF5 loads [EBP] as the
string buffer, then693C04 reads the buffer length at+4. Empty-name handling
loads hidden result [ESP+38] intoESI and calls ctor6910E0 on it. Other return
paths construct through6910F0 or copy691110; RET12 at693D9A is followed byINT3.
It receives ECX worker (savedESI) and uses worker+48 for the same context/mutex
stored by constructor694710. The signed final parameter is clamped0..2.
Its FuncInfoE36CDC has four unwind states: return-handle guard, mutex guard,
allocation cleanup, and local handle691130. There is NO owned string argument
cleanup. Ghidra decompilation independently shows the pointer dereference,
but its guessed stack parameter labels are not used as proof.
Thus one honest pin names Rva00694710AudioWorker::rva00693B90(
const AsciiString&,int), returning the canonical Rva006910F0Handle.

## Why previous banks missed
The old0.64 bank declared the helper filename BY VALUE and created an extra
local/copy. Replacing that with a direct temporary bound to const-reference
reproduces203/203 instruction bytes, all11 relocation sites, and all three
retail epilogues. The repeated fs-chain ordering difference was an ABI/lifetime
model error, not an unavoidable compiler epilogue blocker. A by-value direct
trial emits only96B because the callee owns the string and the caller EH
state vanishes. The corrected caller-signature trial remains203B exact.

## Constructor and cleanup
Canonical default handle constructor6910E0 is9B: MOV EAX,ECX; MOV[EAX],0;
RET, then INT3. Its native constructor reproduces all9B without relocations.
Its class is proven by caller's hidden return and the cleanup target matching
existing Rva006910F0Handle destructor691130; helper693B90 uses the same zero
constructor and pointer constructor6910F0 on its output. Keep the default
constructor in a separateTU. Even noinline visible definition lets MSVC infer
clobbers and changes parent register allocation to196B.

Parent prologue694132 ->handlerC47291 ->FuncInfoE36D68/mapE36D58:
state0/-1 is C47270 (EBP-10 mask1; hidden resultEBP+4; ILT298E8 ->691130;
conditional RETC47288 proves25B). State1/0 is C47289, destroying the filename
atEBP+8 viaD828 ->5EE90. Ghidra raw bytes agree with both actions. No semantic
cleanup name is needed. Parent/constructor/action require strict final gates;
no masked probe alone is claimed as a completed conversion.

The old bank called its methods `build` and `dispatch`; neither name came from
a retail identity witness. Its build verdict was later explicitly retracted
in re_attempts.log because the guessed owner/OpenHandle alias and argument
model were not established. The matched caller and independently decoded
callee now establish the worker receiver and reference ABI, but not full
semantic method names. The new names rva00694130/rva00693B90 preserve those
actual body addresses instead of carrying forward the invented generic names.

The separate constructor identity probe is archived in
[20261003-audio-handle-default-ctor.md](20261003-audio-handle-default-ctor.md).
