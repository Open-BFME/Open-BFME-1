# ScriptEngine string/ObjectID list cleanup chain

All addresses are RVAs in the BFME1 1.03 unpacked baseline. Raw PE and Ghidra
memory agree. No generated source or symbol pin is edited.

The native ScriptEngine constructor at 00347E60 pushes handler C18615 at
00347E62. FuncInfo E086DC/map E0861C state 21 -> 20 selects C185CD. This action
destroys 32 four-byte list objects at saved receiver EBP-10 plus 17374, using
callback VA4183BD. RET C185E4 ends the full 24-byte action before C185E5.

The already matched parent supplies `list<pair<AsciiString,ObjectID>>` for
the four consecutive arrays at 17274, 172F4, 17374 and 173F4, followed by
science vectors. The Zero Hour ScriptEngine.h twin independently names this
same four-array group using ListAsciiStringObjectID (triggered, midway and
finished special powers, then completed upgrades) followed by ScienceVec.
Its typedef at lines 106-108 establishes pair<AsciiString,ObjectID>. Retail
instructions independently establish BFME's 32-element count; the source's
offset-qualified field names are retained, without asserting field names from
the reference offsets.

The complete native dependency chain is:

* 000183BD -> 00343CA0, a 27-byte list destructor. It calls clear through
  000029AA -> 0033F3A0, then frees the 16-byte sentinel through node allocator
  0082E5F0. RET 00343CBA is followed by INT3 at 00343CBB.
* 0033F3A0, a 58-byte list-base clear loop. Each 16-byte node contains its
  eight-byte pair at +8. The pair callback is 000039C7 -> 0033AB90, followed
  by canonical node deallocation. The loop restores both sentinel links;
  RET 0033F3D9 is followed by INT3 at 0033F3DA.
* 0033AB90, a five-byte pair destructor that tail-jumps to canonical narrow
  StringBase releaseBuffer at 00887940. INT3 begins at 0033AB95. 000039C7 is
  the separate ILT stub, so the old body-as-thunk label is not its identity.

All three providers are already emitted by the parent's ordinary STLport
instantiations. Adopt the real ascii_string.h header in place of its local
string declaration so the pair destructor names releaseBuffer directly,
rather than relying on an out-of-line AsciiString destructor's tail route.
The 1164-byte parent remains exact after this change. Replace the generated
list-base/list-clear placeholders and body-as-thunk row with the corresponding
canonical native template emissions, then strictly verify the actual action
and its callback pointer. No fabricated lifetime wrapper is introduced.
